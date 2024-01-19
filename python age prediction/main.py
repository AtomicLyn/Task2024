import os
import cv2
import tensorflow as tf
import numpy as np
from mtcnn import MTCNN

print(cv2.cuda.getCudaEnabledDeviceCount())
print(tf.config.list_logical_devices('GPU'))

load_path = 'test_data'
save_path = 'test_result'
age_labels = ["0-10", "10-20", "20-30", "30-40", "40-50", "50-60", "60-70", "70-80", "80-90", "90+"]
# face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
face_detector = MTCNN()
age_classifier = tf.keras.models.load_model('age_model.h5')

for filename in os.listdir(load_path):
    image_path = os.path.join(load_path, filename)
    image = cv2.imread(image_path)

    # gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # faces = face_cascade.detectMultiScale(gray, scaleFactor=1.2, minNeighbors=5, minSize=(50, 50))
    faces = face_detector.detect_faces(image)
    if len(faces) > 0:
        (x, y, w, h) = faces[0]["box"]
        cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 255), 2)

        image_to_nn = image[y:y + h, x:x + h]
        image_to_nn = cv2.resize(image_to_nn, (224, 224), interpolation=cv2.INTER_LINEAR)
        image_to_nn = np.expand_dims(image_to_nn, axis=0)
        with tf.device('/device:GPU:0'):
            probs = age_classifier.predict(image_to_nn)[0]
        pred_class = np.argmax(probs)
        pred_label = age_labels[pred_class]
        cv2.putText(image, f"{pred_label} ({100*probs[pred_class]:.2f}%)", (x+5, y-5), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)

        save_image_path = os.path.join(save_path, filename)
        cv2.imwrite(save_image_path, image)

        print(f'checked: {filename}')