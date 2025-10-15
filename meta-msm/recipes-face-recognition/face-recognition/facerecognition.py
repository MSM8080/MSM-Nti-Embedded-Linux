import os
import cv2
import numpy as np

# === Paths ===
GALLERY_PATH = "/usr/bin/facerecognition/gallery"
os.makedirs(GALLERY_PATH, exist_ok=True)
LOGIN_FILE = "/home/weston/login.txt"

# === Load Models ===
recognizer = cv2.FaceRecognizerSF.create(
    "/usr/bin/facerecognition/models/face_recognition_sface_2021dec.onnx", ""
)
detector = cv2.FaceDetectorYN.create(
    "/usr/bin/facerecognition/models/face_detection_yunet_2023mar.onnx",
    "",
    (320, 320)
)

# === Function to get face embedding ===
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

# === Load gallery ===
def load_gallery():
    encodings, ids = [], []
    for filename in os.listdir(GALLERY_PATH):
        if filename.endswith(".jpg"):
            img = cv2.imread(os.path.join(GALLERY_PATH, filename))
            enc = get_face_embedding(img)
            if enc is not None:
                encodings.append(enc)
                ids.append(filename.split(".")[0])
    return encodings, ids

# === Compare faces ===
def compare_faces(known_encodings, unknown_encoding, threshold=0.363):
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

# === Detect working camera ===
cap = None
for index in range(50):
    test_cap = cv2.VideoCapture(index)
    if test_cap.isOpened():
        ret, frame = test_cap.read()
        if ret:
            cap = test_cap
            print(f"Camera found at index {index}")
            break
        else:
            test_cap.release()
    else:
        test_cap.release()

if cap is None:
    print("No working camera found in range 0–49.")
    exit()

# === MAIN ===
user_id = None
while True:
    input("Press Enter to capture a photo... ")
    ret, frame = cap.read()

    if not ret:
        print("Failed to capture image, try again.")
        continue

    embedding = get_face_embedding(frame)
    if embedding is None:
        print("No clear face detected, please adjust camera and try again.")
        continue

    print("Face detected, checking gallery...")
    known_encodings, ids = load_gallery()
    match_index, similarity = compare_faces(known_encodings, embedding)

    if match_index is not None:
        user_id = ids[match_index]
        print(f"Existing face found. ID = {user_id} (similarity={similarity:.3f})")
    else:
        user_id = f"{len(ids)+1}"
        cv2.imwrite(os.path.join(GALLERY_PATH, f"{user_id}.jpg"), frame)
        print(f"New face added with ID = {user_id}")
    break



# === Save user ID ===
if user_id is not None:
    with open(LOGIN_FILE, "w") as f:
        f.write(user_id)

cap.release()
print("Done. Camera closed.")
