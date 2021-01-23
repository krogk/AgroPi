#Boilerplate.
#Requires tensorflow, numpy, matplotlib
import tensorflow as tf
from tensorflow import keras

import numpy as np
import matplotlib.pyplot as plt

#Identify dataset in library
fashion_mnist = keras.datasets.fashion_mnist

#Load datasets
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

#Check lengths
print('Number of training images:', len(train_images), 'and labels:', len(train_labels))
print('Number of testing images:', len(test_images), 'and labels:', len(test_labels))
print('Training images shape:', train_images.shape, 'and testing images shape:', test_images.shape)

#Create class names
class_names = ['T-Shirt / Top', 'Trousers', 'Jumper', 'Dress', 'Coat', 'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle Boot']

#Show an image
plt.figure()
plt.imshow(train_images[0])
plt.colorbar()
plt.grid(False)
plt.show()

#Normalize images
train_images = train_images / 255.0
test_images = test_images / 255.0

#Show first 25 images with labels
plt.figure(figsize =  (10,10))
for i in range(25):
    plt.subplot(5,5,i+1)
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.imshow(train_images[i], cmap = plt.cm.binary)
    plt.xlabel(class_names[train_labels[i]])
plt.show()

#NN model
model = keras.Sequential([
    keras.layers.Flatten(input_shape=(28,28)),
    keras.layers.Dense(128, activation = tf.nn.relu),
    keras.layers.Dense(10, activation = tf.nn.softmax)
])

#Compile model
model.compile(optimizer = 'adam',
              loss = 'sparse_categorical_crossentropy', #For multi class problem
              metrics = 'accuracy'
              )

#Fit model on training set
model.fit(train_images, train_labels, epochs = 10)

#Pull loss and accuracy on testing set
test_loss, test_acc = model.evaluate(test_images, test_labels)

#Print accuracy of model after 10 epochs of training
print('Test accuracy:',test_acc)

#Make vector of predictions for each test image
predictions = model.predict(test_images)

#Check first item
predictions[0] #Returns the array of probabilities for each class

np.argmax(predictions[0]) #Returns the most likely option

test_labels[0] #Returns true class

#A function to plot images with labels and % confidence in value
def plot_image(i, predictions_array, true_label, img):
    predictions_array, true_label, img = predictions_array[i], true_label[i], img[i]
    plt.grid(False)
    plt.xticks([])
    plt.yticks([])

    plt.imshow(img, cmap = plt.cm.binary)

    predicted_label = np.argmax(predictions_array)
    if predicted_label == true_label:
        color = 'blue'
    else:
        color = 'red'

    plt.xlabel("{} {:2.0f}% ({})".format(class_names[predicted_label],
                                        100*np.max(predictions_array),
                                        class_names[true_label]),
                                        color = color)

def plot_value_array(i, predictions_array, true_label):
    predictions_array, true_label = predictions_array[i], true_label[i]
    plt.grid(False)
    plt.xticks([])
    plt.yticks([])
    thisplot = plt.bar(range(10), predictions_array, color = '#777777')
    plt.ylim([0, 1])
    predicted_label = np.argmax(predictions_array)

    thisplot[predicted_label].set_color('red')
    thisplot[true_label].set_color('green')

#plot image
i = 0
plt.figure(figsize=(6,3))
plt.subplot(1,2,1)
plot_image(i, predictions,test_labels, test_images)
plt.subplot(1,2,2)
plot_value_array(i, predictions, test_labels)

#Plot multiple images
num_rows = 5
num_cols = 5
num_images = num_rows * num_cols
plt.figure(figsize=(2*2*num_cols, 2*num_rows))
for i in range(num_images):
    plt.subplot(num_rows, 2*num_cols, 2*i+1)
    plot_image(i, predictions, test_labels, test_images)
    plt.subplot(num_rows, 2*num_cols, 2*i+2)
    plot_value_array(i, predictions, test_labels)
plt.show()