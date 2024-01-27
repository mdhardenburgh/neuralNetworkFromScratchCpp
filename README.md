# TLDR
Implementation of a basic neural network (perceptatron) in C++. Classifies the MNIST database of handwritten images

# Building

To run cmake:

`$ <cmake_location>/bin/cmake .`

Where <cmake_location> is the location of your cmake folder. For example, my
cmake folder is in the home directory so my command will look like:

`$ ~/cmake-3.23.1-linux-x86_64/bin/cmake .`

This command will create the makefiles for all of the examples.

To build, in the root directory run:

`$ make all`


# MNIST data reader
We need to be able to read in the MNIST data. We know that each image is 784 
pixels and that there are a set number of images

# Layers
Input layer has 784 neurons corresponding to the 784 pixels of the image. First 
hidden layer has 10 neurons and the output layer has 10 neurons (for numbers 
0-9).

# Forward Propagation
This is the easy part

# Notes

* Each image in MNIST is 28x28. Each pixel in those images has a greyscale value 
  between 0 (black) and 255 (white) (0x0 and 0xFFF).
* Matrix of the entire dataset, each row is an image, and each column in that 
  row is a pixel. Transposed each column is an image and each row in that column
  is a pixel. M column corresponding to M training samples
* Input layer has 784 neurons corresponding to the 784 pixels of the image. First
  layer has 10 neurons and second layer, which is also our output layer has 10 
  neurons corresponding to 1 digit that the classifier has decided
* Array holding training data is going to look something like `uint8_t input[50000][784]`

* building neural net in python from scratch https://www.youtube.com/watch?v=w8yWXqWQYmU&t=1096s