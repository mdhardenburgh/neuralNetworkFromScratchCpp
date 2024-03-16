# TLDR
Implementation of a basic neural network (perceptron) in C++. Classifies the 
MNIST database of handwritten images

# Goals
I set out to achieve two goals with this project: 
1. Design a neural network that could classify the MNIST database of human 
   labeled 28x28 images of handwritten digits (0 through 9), with an accuracy 
   of 80% or greater. 
2. Implement this neural network using C++, and without pre-built machine 
   learning or linear algebra libraries such as TensorFlow.

I chose to implement this project in C++, without neural network or machine 
learning libraries because C++ is the programming language I am most familiar 
with and I wanted to implement the concepts that we discussed in class and not 
have a library handle it for me.

# Design
The design of my neural network based on a “perceptron” style neural network. 
This is a very old concept and is considered the “hello world” of neural 
networks. The first layer is the input layer. It has 784 nodes, one for each 
pixel of image. The first and second hidden layers have 16 nodes each. The 
first hidden layer has a 16x784 weight matrix and 16 biases. The second hidden 
layer has a 16x16 weight matrix, and 16 biases. The output layer is 10 nodes, 
for the network to output what it thinks each digit is, 0 through 9. The output 
layer has a 10x16 weight matrix and 10 biases. The activation function I chose 
was the sigmoid function and for backpropagation I chose to use stochastic 
gradient descent, both of which were taught in class. The number of nodes for 
the hidden layers was chosen somewhat arbitrarily, but influenced by the [3blue, brown videos on neural networks][4].

# Applications of topics from class
In class this quarter I learned many linear algebra topics that apply to neural 
networks, and I applied a several to create my own matrix library. For my 
matrix library, I implemented scalar multiplication, matrix multiplication, 
component wise multiplication, addition, subtraction, and transpose. The matrix 
multiplication algorithm was the most difficult to implement. I chose to 
implement the vector-vector product, which makes use of a triple loop and has 
the runtime complexity, O(n^3), which is awful. The other algorithms have 
runtime complexity between O(n) and O(n^2) which isn’t great either.

# Performance
The first time I achieved an accuracy greater than 80%, I trained my network 
for 900,000 iterations on the 60,000 training images. Training the network took 
about an hour and resulted in an average cost of 8.85. For this run and the 
next run I set learning rate to 0.0015. My network had accuracy of 83.12% on 
the set of 10,000 validation images. An interesting result occurred when 
increased the number of iterations was increased to 1.2 million iterations. 
Training the network this time took about 15 minutes with and resulted in an 
average cost of 10.447 and a marginally better accuracy of 84.84%. I can only 
speculate as to this discrepancy of training time. It would seem logical to me 
that increasing the number of iterations would increase the training time, but 
this result challenges that line of thinking. I propose that it is possible the
compiler and CPU in combination could be optimizing and caching respectively, 
but that is only a supposition and requires more debugging and study. 

# Future Improvements
Several improvements can certainly be made to my project. Better algorithms for 
the neural network can be used such as mini-batching, or convolutional neural 
networks. Additionally, better algorithms for the matrix operations can be used 
as well, especially for the matrix multiply in which the runtime complexity for 
my algorithm is O(n^3). A search revealed a matrix multiplication algorithm 
called the [Refined Laser Method discussed in a 2020 paper][1] by Josh Alman and 
Virginia Williams where they achieved a runtime complexity of O(n^2.37). There 
are probably also several compiler optimizations that I did not take advantage 
of such as loop-unrolling and better use of instruction level parallelism. 

The main improvements that I want to discuss are the use of CPU multithreading 
and GPU parallel programing. Most CPUs can multithread and the matrix 
operations that I implemented do not need to be sequential, in that the current 
computation does not require the output of the previous computation. [A search][2] 
reveals that a multithreaded version of matrix multiply can certainly be 
implemented, thus resulting in multiple algorithms with a runtime complexity of 
O(n2) running at the same time. Potentially faster than any improvements 
discussed above. Most high-performance computers and computing labs have GPUs in 
their systems. These devices enable a Single Instruction Multiple Data (SIMD) 
paradigm of programing where thousands of simpler processors called cores work 
together on a shared chunk of data (Think piranhas eating a large animal). This 
can result in turning loops into a single line of code and reducing runtime 
complexity of algorithms. [A quick search again][3] reveals that matrix 
multiplication can certainly be implemented using a GPU and a single loop in the 
kernel (the program that is run on a single core) resulting in a runtime 
complexity of O(n). Dynamic parallelism could potentially bring the runtime 
complexity down to O(1), which would be the proverbial holy grail. 

Google, Apple and other companies are working on ASICs to specifically 
accelerate neural network applications. Google invented tensor cores and Apple 
has their neural engine. Algorithms implemented with these devices in mind could 
potentially run faster.

[1]: https://arxiv.org/abs/2010.05846 
[2]: https://www.geeksforgeeks.org/multiplication-of-matrix-using-threads/
[3]: https://docs.nvidia.com/cuda/pdf/CUDA_C_Best_Practices_Guide.pdf 
[4]: https://youtu.be/aircAruvnKk?si=FSAfqP9RxGoLfuzc&t=255 


# Build and Run

## Prerequisites
To build this project you need cmake and GCC:
1. Cmake can be installed via `$ sudo apt-get install cmake`, or by downloading 
   cmake from the [website](https://cmake.org/download/). 
   My project requires cmake version 3.23.1 or later.
2. GCC can be installed via `$ sudo apt install build-essential`

## Running cmake
To run cmake:

`$ <cmake_location>/bin/cmake .`

Where <cmake_location> is the location of your cmake folder. For example, my
cmake folder is in the home directory so my command will look like:

`$ ~/cmake-3.23.1-linux-x86_64/bin/cmake .`

This command will create the makefiles to build the project

## Building 
To build, in the root directory run:

`$ make`

## Running
After the project is built run `$ ./nerualNetFromScratch` to run the project

# Unit Tests
The matrix class includes unit test for validating functionality. If you wish to
build and run the unit test go to the unit test folder and run cmake from there.
1. `$ cd matrix/unitTest`
2. `$ <cmake_location>/bin/cmake .`
3. `$ make`
4. `$ ./matrixTest`
