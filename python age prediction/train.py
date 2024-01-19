import tensorflow as tf
from tensorflow.keras import layers, models, utils, losses, optimizers
from matplotlib import pyplot as plt

age_labels = ["0-10", "10-20", "20-30", "30-40", "40-50", "50-60", "60-70", "70-80", "80-90", "90+"]

train_datagen = tf.keras.preprocessing.image.ImageDataGenerator(
    horizontal_flip=True,
    rotation_range=15,
    zoom_range=0.15,
    height_shift_range=0.05,
    width_shift_range=0.05,
    brightness_range=[0.8, 1.2],
    fill_mode='nearest'
)

train_gen = train_datagen.flow_from_directory(
    'train',
    class_mode='categorical',
    target_size=(224, 224),
    color_mode='rgb',
    batch_size=16,
)

val_datagen = tf.keras.preprocessing.image.ImageDataGenerator(
    horizontal_flip=True,
    zoom_range=0.1,
    height_shift_range=0.05,
    width_shift_range=0.05,
    fill_mode='nearest'
)

val_gen = val_datagen.flow_from_directory(
    'val',
    class_mode='categorical',
    target_size=(224, 224),
    color_mode='rgb',
    batch_size=16,
)

for i in range(16):
    image, _ = train_gen.next()
    ax = plt.subplot(4, 4, i + 1)
    plt.imshow(image[0]/255.)
    plt.axis("off")
plt.show()

model = models.Sequential()
model.add(layers.Rescaling(1./255, input_shape=(224, 224, 3)))
model.add(layers.Conv2D(32, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(64, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(128, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(256, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(256, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Flatten())
model.add(layers.Dense(256, activation='relu'))
model.add(layers.Dense(256, activation='relu'))
model.add(layers.Dense(10, activation='softmax'))

model.compile(
    loss=losses.CategoricalCrossentropy(),
    optimizer=optimizers.Adam(learning_rate=0.001),
    metrics=["accuracy"]
)
model.summary()

# model = tf.keras.models.load_model('age_model.h5')

with tf.device('/device:GPU:0'):
    history = model.fit(train_gen, validation_data=val_gen, epochs=30)

model.save("age_model.h5")

plt.subplot(1, 2, 1)
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Loss')
plt.xlabel('Эпохи')
plt.ylabel('Потери')
plt.legend(['train', 'val'])

plt.subplot(1, 2, 2)
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('Accuracy')
plt.xlabel('Эпохи')
plt.ylabel('Точность')
plt.legend(['train', 'val'])

plt.savefig('train_metrics.png')
plt.show()

