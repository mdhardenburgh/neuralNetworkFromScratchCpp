#include "mnistDataReader.h"
#include "matrix.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>

matrix<_Float64> activate(matrix<_Float64> weights, matrix<_Float64> inputFromPrevLayer, matrix<_Float64> biases)
{
    matrix<_Float64> outputOfActivation = matrix<_Float64>::add(matrix<_Float64>::matrixMultiplication(weights, inputFromPrevLayer), biases);

    // The resultant matrix should be a Nx1
    if(outputOfActivation.getNumColumns() != 1)
    {
        std::cout<<"matrix<_Float64> activate(), not an Nx1 matrix, has "<< outputOfActivation.getNumColumns()<<" columns"<<std::endl;
        assert(false);
    }

    for(uint32_t iIter = 0; iIter < outputOfActivation.getNumRows(); iIter++)
    {
        _Float64 temp = 1.0f /(1.0f + exp(-1.0f * outputOfActivation.at(iIter)));
        outputOfActivation.assign(temp, iIter);
    }

    return outputOfActivation;
}

int main()
{
    srand (static_cast <unsigned> (time(0)));
    
    mnistDataReader reader("mnistDataset/train-images.idx3-ubyte", "mnistDataset/train-labels.idx1-ubyte", 60000);

    // 784 nodes
    matrix<_Float64> inputLayer(784, 1); // 16x16 pixels = 784 nodes
    // 16 nodes, 16 rows is number nodes in current layer, 784 columns is number nodes in previous layer
    // Each node is connect to every other node in the previous layer
    matrix<_Float64> hiddenLayer1_weights(16, 784); 
    // 16 nodes, rows is number of nodes in current layer
    matrix<_Float64> hiddenLayer1_biases(16, 1); 
    // 16 nodes, 16 in rows in current layer, 16 columns because there are 16 nodes in previous layer
    matrix<_Float64> hiddenLayer2_weights(16, 16); // 16 nodes
    matrix<_Float64> hiddenLayer2_biases(16, 1); // 16 nodes
    matrix<_Float64> outputLayerWeights(10, 16); // 10 nodes, each corresponding to 0-9
    matrix<_Float64> outputLayerBiases(10, 1); // 16 nodes, so 16 biases

    matrix<_Float64> onesMatrixOutput(10, 1);
    matrix<_Float64> onesMatrixLayer2(16, 1);
    matrix<_Float64> onesMatrixLayer1(16, 1);
    onesMatrixOutput.fillNumber(1.0f);
    onesMatrixLayer2.fillNumber(1.0f);
    onesMatrixLayer1.fillNumber(1.0f);

    //learning rate, AKA eta
    _Float64 learningRate = 0.05f;
    //number of stochastic gradient iterations
    uint32_t stochasticGradientIters = 60000;
    _Float64 totalCost = 0.0f;

    //initialize to all zeros or random value
    inputLayer.fillZeros();
    hiddenLayer1_weights.fillRandom(-0.5f, 0.5f);
    hiddenLayer1_biases.fillRandom(-0.5f, 0.5f);
    hiddenLayer2_weights.fillRandom(-0.5f, 0.5f);
    hiddenLayer2_biases.fillRandom(-0.5f, 0.5f);
    outputLayerWeights.fillRandom(-0.5f, 0.5f);
    outputLayerBiases.fillRandom(-0.5f, 0.5f);

    for(uint32_t iIter = 0; iIter < stochasticGradientIters; iIter++)
    {
        //select random image from training set
        uint32_t randomIndex = 0 + static_cast<uint32_t>(rand()) / (static_cast<uint32_t>(RAND_MAX/(0-60000)));
        _Float64 cost = 0;
        matrix<uint8_t> randomImage = reader.getImage(randomIndex);
        matrix<_Float64> randomImageLabel = reader.getImageLabel(randomIndex);
        //convert image from uint8 matrix to float32 matrix
        for(uint32_t iIter = 0; iIter < (randomImage.getNumRows() * randomImage.getNumColumns()); iIter++)
        {
            inputLayer.assign(static_cast<_Float64>(randomImage.at(iIter)), iIter);
        }
        //forward pass
        matrix<_Float64>outputOfLayer1 = activate(hiddenLayer1_weights, inputLayer, hiddenLayer1_biases);
        matrix<_Float64>outputOfLayer2 = activate(hiddenLayer2_weights, outputOfLayer1, hiddenLayer2_biases);
        matrix<_Float64>outputLayer = activate(outputLayerWeights, outputOfLayer2, outputLayerBiases);
        //backward pass
        /** 
         * add up the squares of the differences of the outputs of the network
         * vs the actual value.
         * cost = pow((outputLayer[0] - reader[0]), 2) + pow((outputLayer[1] - reader[1]), 2) + ... + pow(outputLayer[9] - reader[9], 2)
         * avgCost = totalCost/trainingData
         * 
         * cost = outputLayer - reader.getImageLabel
         * 
         * Then consider the average cost over the training examples, measure
         * of how bad the network does.
         * 
         * Cost function takes in all the weights and biases and spits out a 
         * single number, a measure of the network performance over all the
         * training examples.
         * 
         * The gradient tells us which nudges to the weights and biases, causes
         * the fastest change to the cost function. Which changes to which weights
         * matter the most.
         * 
         * errorLayerOutput = matrix<_Float64>::hadamardProduct(outputLayer(1-outputLayer),(outputLayer - reader.getImageLabel) 
         * errorLayer2 = matrix<_Float64>::hadamardProduct(outPutOfLayer2(1-outPutOfLayer2),(matrix<_Float64>::matrixMultiply(outputLayerWeights, errorLayerOutput))
         * errorLayer1 = matrix<_Float64>::hadamardProduct(outPutOfLayer1(1-outPutOfLayer1),(matrix<_Float64>::matrixMultiply(hiddenLayer2_weights, errorLayer2))
         * 
         * outputLayerWeights = outputLayerWeights - (learningRate * errorLayerOutput * outPutOfLayer2)
         * outputLayerBiases = outputLayerBiases - (learningRate * errorLayerOutput)
         * hiddenLayer2_weights = hiddenLayer2_weights - (learningRate * errorLayer2 * outPutOfLayer1)
         * hiddenLayer2_biases = hiddenLayer2_biases - (learningRate * errorLayer2)
         * hiddenLayer1_weights = hiddenLayer1_weights - (learningRate * errorLayer1 * inputLayer)
         * hiddenLayer1_biases = hiddenLayer1_biases - (learningRate * errorLayer1)
         */

        /**
         * Calculate the cost (AKA error) for the iteration
         * 
         * cost = (outputLayer[0] - expectedOutput[0])^2 + (outputLayer[1] - expectedOutput[1])^2 + ... (outputLayer[9] - expectedOutput[9])^2
         */
        for(uint32_t jIter = 0; jIter < randomImageLabel.getNumRows(); jIter++)
        {
            cost += pow(outputLayer.at(jIter) - randomImageLabel.at(jIter), 2.0f);
        }
        std::cout<< "cost/error for iteration "<< iIter << " is "<<cost<<std::endl;
        totalCost = totalCost + cost;

        // errorOutputLayer = sigmoid'(x) hadamard (outputLayer - expected_result) = (outputLayer hadamard (1-outputLayer)) hadamard (outputLayer - expected_result)
        matrix<_Float64> errorLayerOutput = matrix<_Float64>::hadamardProduct(matrix<_Float64>::hadamardProduct(outputLayer, (matrix<_Float64>::subtract(onesMatrixOutput,outputLayer))),(matrix<_Float64>::subtract(outputLayer, randomImageLabel)));

        // errorLayer2 = sigmoid'(x) hadamard (outputLayerWeights * errorOutputLayer) = (outputOfLayer2 hadamard (1-outputOfLayer2)) hadamard (outputLayerWeights * errorOutputLayer)
        matrix<_Float64> errorLayer2 = matrix<_Float64>::hadamardProduct(matrix<_Float64>::hadamardProduct(outputOfLayer2, (matrix<_Float64>::subtract(onesMatrixLayer2,outputOfLayer2))), matrix<_Float64>::matrixMultiplication(matrix<_Float64>::transpose(outputLayerWeights), errorLayerOutput));
        // errorLayer1 = sigmoid'(x) hadamard (hiddenLayer2_weights * errorLayer2) = (outputOfLayer1 hadamard (1-outputOfLayer1)) hadamard (hiddenLayer2_weights * errorLayer2)
        matrix<_Float64> errorLayer1 = matrix<_Float64>::hadamardProduct(matrix<_Float64>::hadamardProduct(outputOfLayer1, (matrix<_Float64>::subtract(onesMatrixLayer1,outputOfLayer1))), matrix<_Float64>::matrixMultiplication(matrix<_Float64>::transpose(outputLayerWeights), errorLayerOutput));

        // outputLayerWeights = outputLayerWeights - (learningRate * errorLayerOutput * transpose(outputOfLayer2))
        outputLayerWeights = matrix<_Float64>::subtract(outputLayerWeights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayerOutput), matrix<_Float64>::transpose(outputOfLayer2))));
        // outputLayerBiases = outputLayerBiases - (learningRate * errorLayerOutput)
        outputLayerBiases = matrix<_Float64>::subtract(outputLayerBiases, matrix<_Float64>::scalarMultiply(learningRate, errorLayerOutput));
        // hiddenLayer2_weights = hiddenLayer2_weights - (learningRate * errorLayer2 * outputOfLayer1)
        hiddenLayer2_weights = matrix<_Float64>::subtract(hiddenLayer2_weights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayer2), matrix<_Float64>::transpose(outputOfLayer1))));
        // hiddenLayer2_biases = hiddenLayer2_biases - (learningRate * errorLayer2)
        hiddenLayer2_biases = matrix<_Float64>::subtract(hiddenLayer2_biases, matrix<_Float64>::scalarMultiply(learningRate, errorLayer2));
        // hiddenLayer1_weights = hiddenLayer1_weights - (learningRate * errorLayer1 * inputLayer)
        hiddenLayer1_weights = matrix<_Float64>::subtract(hiddenLayer1_weights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayer1), matrix<_Float64>::transpose(inputLayer))));
        // hiddenLayer1_biases = hiddenLayer1_biases - (learningRate * errorLayer1)
        hiddenLayer1_biases = matrix<_Float64>::subtract(hiddenLayer1_biases, matrix<_Float64>::scalarMultiply(learningRate, errorLayer1));
    }


    std::cout<<"average cost is: " << totalCost/stochasticGradientIters<<std::endl;

    return 0;
}