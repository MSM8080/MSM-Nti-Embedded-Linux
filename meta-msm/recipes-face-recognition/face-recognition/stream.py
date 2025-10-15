import cv2
import os
import numpy as np
import time
import tkinter as tk
from PIL import Image, ImageTk

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

# === Camera Stream ===
def open_camera():
    for index in range(50):
        cap = cv2.VideoCapture(index)
        if cap.isOpened():
            ret, _ = cap.read()
            if ret:
                print(f"✅ Camera found at index {index}")
                return cap
            else:
                cap.release()
    return None

# === Tkinter Display ===
def main():
    cap = open_camera()
    if cap is None:
        print("❌ No working camera found!")
        return

    root = tk.Tk()
    root.attributes('-fullscreen', True)
    root.configure(bg="black")

    # === Fullscreen camera label ===
    label = tk.Label(root, bg="black")
    label.pack(fill="both", expand=True)

    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()

    face_detected = False
    person_id = None

    def update_frame():
        nonlocal face_detected, person_id

        ret, frame = cap.read()
        if not ret:
            root.after(10, update_frame)
            return

        # Resize the frame to fill the full screen
        frame_resized = cv2.resize(frame, (screen_width, screen_height))

        # Convert OpenCV BGR to RGB for Tkinter
        rgb = cv2.cvtColor(frame_resized, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(rgb)
        imgtk = ImageTk.PhotoImage(image=img)
        label.imgtk = imgtk
        label.configure(image=imgtk)

        if not face_detected:
            embedding = get_face_embedding(frame)
            if embedding is not None:
                face_detected = True
                known_encodings, ids = load_gallery()
                match_index, similarity = compare_faces(known_encodings, embedding)
                if match_index is not None:
                    person_id = ids[match_index]
                    print(f"✅ Known face detected, ID = {person_id}")
                else:
                    person_id = str(len(ids) + 1)
                    cv2.imwrite(os.path.join(GALLERY_PATH, f"{person_id}.jpg"), frame)
                    print(f"🆕 New face added, ID = {person_id}")

                # Save ID
                with open(LOGIN_FILE, "w", encoding="utf-8") as f:
                    f.write(person_id + "\n")
                print(f"💾 ID saved successfully to {LOGIN_FILE}")

                # Hold the camera stream for 2 seconds before showing black screen
                root.after(2000, lambda: show_black_screen(person_id))
                return

        root.after(10, update_frame)

    def show_black_screen(user_id):
        # Stop camera
        cap.release()
        # Clear the camera label
        label.configure(image="", bg="black")

        # === Fullscreen black screen with hello message ===
        hello_label = tk.Label(
            root,
            text=f"Hello user {user_id}",
            font=("Arial", 80, "bold"),
            fg="white",
            bg="black"
        )
        hello_label.pack(fill="both", expand=True)

        # Close after 2 seconds
        root.after(2000, root.destroy)

    update_frame()
    root.mainloop()

if __name__ == "__main__":
    main()
