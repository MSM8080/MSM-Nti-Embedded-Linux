import cv2
import os
import numpy as np
import time

# === Paths ===
GALLERY_PATH = "/usr/bin/facerecognition/gallery"
os.makedirs(GALLERY_PATH, exist_ok=True)
LOGIN_FILE = "/home/weston/login.txt"

# === Load Models ===
recognizer = cv2.FaceRecognizerSF.create(
    "/usr/bin/facerecognition/models/face_recognition_sface_2021dec.onnx", ""
)
detector = cv2.FaceDetectorYN.create(
    "/usr/bin/facerecognition/models/face_detection_yunet_2023mar.onnx", "", (320, 320)
)

# === Helper functions ===
def get_face_embedding(image):
    h, w, _ = image.shape
    detector.setInputSize((w, h))
    faces = detector.detect(image)
    if faces[1] is None or len(faces[1]) != 1:
        return None
    face = faces[1][0]
    aligned_face = recognizer.alignCrop(image, face)
    feature = recognizer.feature(aligned_face)
    return feature

def load_gallery():
    encodings = []
    ids = []
    for filename in os.listdir(GALLERY_PATH):
        if filename.endswith(".jpg"):
            img = cv2.imread(os.path.join(GALLERY_PATH, filename))
            enc = get_face_embedding(img)
            if enc is not None:
                encodings.append(enc)
                ids.append(filename.split(".")[0])
    return encodings, ids

def compare_faces(known_encodings, unknown_encoding, threshold=0.300):
    if not known_encodings:
        return None, None
    similarities = [
        recognizer.match(unknown_encoding, known_enc, cv2.FaceRecognizerSF_FR_COSINE)
        for known_enc in known_encodings
    ]
    max_similarity = max(similarities)
    if max_similarity > threshold:
        index = np.argmax(similarities)
        return index, max_similarity
    return None, None

def open_camera():
    for index in range(50):
        cap = cv2.VideoCapture(index)
        if cap.isOpened():
            ret, frame = cap.read()
            if ret:
                return cap
            else:
                cap.release()
    return None

def main():
    cap = open_camera()
    if cap is None:
        return

    embedding = None
    frame = None

    # Keep trying silently until a valid face is found
    while embedding is None:
        ret, frame = cap.read()
        if not ret:
            continue
        embedding = get_face_embedding(frame)

    # Once a valid face is found, process it
    known_encodings, ids = load_gallery()
    match_index, similarity = compare_faces(known_encodings, embedding)

    if match_index is not None:
        person_id = ids[match_index]
        print(f"Known face detected. ID = {person_id}")
    else:
        person_id = str(len(ids) + 1)
        cv2.imwrite(os.path.join(GALLERY_PATH, f"{person_id}.jpg"), frame)
        print(f"New face added. ID = {person_id}")

    # Save ID to file
    with open(LOGIN_FILE, "w", encoding="utf-8") as f:
        f.write(person_id + "\n")
    print(f"ID saved successfully to {LOGIN_FILE}")

    # Release camera
    cap.release()

if __name__ == "__main__":
    main()

