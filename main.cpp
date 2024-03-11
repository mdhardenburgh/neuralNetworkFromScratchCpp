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
    //std::cout<<"multiply and add during activation"<<std::endl;
    //outputOfActivation.print();

    // The resultant matrix should be a Nx1
    if(outputOfActivation.getNumColumns() != 1)
    {
        std::cout<<"matrix<_Float64> activate(), not an Nx1 matrix, has "<< outputOfActivation.getNumColumns()<<" columns"<<std::endl;
        assert(false);
    }

    for(uint32_t iIter = 0; iIter < outputOfActivation.getNumRows(); iIter++)
    {
        _Float64 temp = 1.0f /(1.0f + exp(-1.0f * outputOfActivation.at(iIter)));
        //std::cout<<"ouput of _Float64 temp "<<exp(-1.0f * outputOfActivation.at(iIter))<<std::endl;
        outputOfActivation.assign(temp, iIter);
    }

    //std::cout<<"output of activation"<<std::endl;
    //outputOfActivation.print();

    return outputOfActivation;
}

int main()
{
    srand(time(0));
    
    uint32_t numTestSamples = 10000;
    uint32_t numTrainingSamples = 60000;
    uint32_t totalWrong = 0;
    mnistDataReader training("mnistDataset/train-images.idx3-ubyte", "mnistDataset/train-labels.idx1-ubyte", numTrainingSamples);
    mnistDataReader testSamples("mnistDataset/t10k-images.idx3-ubyte", "mnistDataset/t10k-labels.idx1-ubyte", numTestSamples);

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
    _Float64 learningRate = 0.015f;
    uint32_t stochasticIterations = 2;
    //sum of the cost over all the iterations
    _Float64 totalCost = 0.0f;

    //initialize to all zeros or random value
    inputLayer.fillZeros();
    hiddenLayer1_weights.fillRandom(-0.5f, 0.5f);
    hiddenLayer2_weights.fillRandom(-0.5f, 0.5f);
    outputLayerWeights.fillRandom(-0.5f, 0.5f);
    std::cout<<"outputLayerWeights BEFORE training"<<std::endl;
    outputLayerWeights.print();

    hiddenLayer1_biases.fillRandom(-0.5f, 0.5f);
    hiddenLayer2_biases.fillRandom(-0.5f, 0.5f);
    outputLayerBiases.fillRandom(-0.5f, 0.5f);


    for(uint32_t iIter = 0; iIter < stochasticIterations; iIter++)
    {
        //select random image from training set
        uint32_t randomIndex = rand()%(numTrainingSamples);
        //std::cout<<"random image index "<<randomIndex<<std::endl;
        _Float64 cost = 0;
        matrix<uint8_t> randomImage = training.getImage(randomIndex);
        //std::cout<<"random image contents"<<std::endl;
        //training.getImage(randomIndex).print();
        //training.printImage(randomIndex);
        matrix<_Float64> randomImageLabel = training.getImageLabel(randomIndex);
        //convert image from uint8 matrix to float32 matrix
        for(uint32_t jIter = 0; jIter < (randomImage.getNumRows() * randomImage.getNumColumns()); jIter++)
        {
            inputLayer.assign(static_cast<_Float64>(randomImage.at(jIter)), jIter);
        }
        //std::cout<<"input layer contents"<<std::endl;
        //inputLayer.print();
        // forward pass through the network
        matrix<_Float64>outputOfLayer1 = activate(hiddenLayer1_weights, inputLayer, hiddenLayer1_biases);
        //std::cout<<"output of layer 1"<<std::endl;
        //outputOfLayer1.print();
        matrix<_Float64>outputOfLayer2 = activate(hiddenLayer2_weights, outputOfLayer1, hiddenLayer2_biases);
        //std::cout<<"output of layer 2"<<std::endl;
        //outputOfLayer2.print();
        matrix<_Float64>outputLayer = activate(outputLayerWeights, outputOfLayer2, outputLayerBiases);
        //std::cout<<"output of the output layer "<<std::endl;
        //outputLayer.print();
        /** 
         * 
         * Cost function takes in all the weights and biases and spits out a 
         * single number, a measure of the network performance over all the
         * training examples.
         */

        /**
         * Calculate the cost (AKA error) for the iteration. 
         * A measure of how bad the network does
         * 
         * Add up the squares of the differences of the outputs of the network vs the actual value.
         * cost = (outputLayer[0] - expectedOutput[0])^2 + (outputLayer[1] - expectedOutput[1])^2 + ... (outputLayer[9] - expectedOutput[9])^2
         */
        for(uint32_t jIter = 0; jIter < randomImageLabel.getNumRows(); jIter++)
        {
            cost += pow(outputLayer.at(jIter) - randomImageLabel.at(jIter), 2.0f);
        }
        std::cout<< "cost/error for iteration "<< iIter << " is "<<cost<<std::endl;
        totalCost = totalCost + cost;

        /**
         * Backward Pass through the network
         * 
         * The gradient tells us which nudges to the weights and biases, causes
         * the fastest change to the cost function. Which changes to which weights
         * matter the most.
        */
        // errorOutputLayer = sigmoid'(x) hadamard (outputLayer - expected_result) = (outputLayer hadamard (1-outputLayer)) hadamard (outputLayer - expected_result)
        //matrix<_Float64> errorLayerOutput = matrix<_Float64>::subtract(outputLayer, randomImageLabel);
        matrix<_Float64> errorLayerOutput = matrix<_Float64>::hadamardProduct(matrix<_Float64>::hadamardProduct(outputLayer, (matrix<_Float64>::subtract(onesMatrixOutput,outputLayer))),(matrix<_Float64>::subtract(outputLayer, randomImageLabel)));
        // errorLayer2 = sigmoid'(x) hadamard (outputLayerWeights * errorOutputLayer) = (outputOfLayer2 hadamard (1-outputOfLayer2)) hadamard (outputLayerWeights * errorOutputLayer)
        matrix<_Float64> errorLayer2 = matrix<_Float64>::hadamardProduct(matrix<_Float64>::hadamardProduct(outputOfLayer2, (matrix<_Float64>::subtract(onesMatrixLayer2,outputOfLayer2))), matrix<_Float64>::matrixMultiplication(matrix<_Float64>::transpose(outputLayerWeights), errorLayerOutput));
        // errorLayer1 = sigmoid'(x) hadamard (hiddenLayer2_weights * errorLayer2) = (outputOfLayer1 hadamard (1-outputOfLayer1)) hadamard (hiddenLayer2_weights * errorLayer2)
        matrix<_Float64> errorLayer1 = matrix<_Float64>::hadamardProduct(matrix<_Float64>::hadamardProduct(outputOfLayer1, (matrix<_Float64>::subtract(onesMatrixLayer1,outputOfLayer1))), matrix<_Float64>::matrixMultiplication(matrix<_Float64>::transpose(outputLayerWeights), errorLayerOutput));

        std::cout<<"outputLayerWeights calc"<<std::endl;
        matrix<_Float64>::subtract(outputLayerWeights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayerOutput), matrix<_Float64>::transpose(outputOfLayer2)))).print();
        std::cout<<"errorLayerOutput"<<std::endl;
        errorLayerOutput.print();
        std::cout<<"scalarMultiply(learningRate, errorLayerOutput)"<<std::endl;
        matrix<_Float64> temp1 = matrix<_Float64>::scalarMultiply(learningRate, errorLayerOutput);
        temp1.print();
        matrix<_Float64> temp2 = matrix<_Float64>::transpose(outputOfLayer2);
        std::cout<<"outputOfLayer2"<<std::endl;
        outputOfLayer2.print();
        std::cout<<"transpose of outputOfLayer2"<<std::endl;
        temp2.print();
        std::cout<<"learningRate * errorLayerOutput matrixMultiply outputOfLayer2`"<<std::endl;
        matrix<_Float64> temp3 = matrix<_Float64>::matrixMultiplication(temp1, temp2);
        temp3.print();
        outputLayerWeights = matrix<_Float64>::subtract(outputLayerWeights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayerOutput), matrix<_Float64>::transpose(outputOfLayer2))));
        // outputLayerBiases = outputLayerBiases - (learningRate * errorLayerOutput)
        outputLayerBiases = matrix<_Float64>::subtract(outputLayerBiases, matrix<_Float64>::scalarMultiply(learningRate, errorLayerOutput));
        // hiddenLayer2_weights = hiddenLayer2_weights - (learningRate * errorLayer2 * transpose(outputOfLayer1))
        hiddenLayer2_weights = matrix<_Float64>::subtract(hiddenLayer2_weights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayer2), matrix<_Float64>::transpose(outputOfLayer1))));
        // hiddenLayer2_biases = hiddenLayer2_biases - (learningRate * errorLayer2)
        hiddenLayer2_biases = matrix<_Float64>::subtract(hiddenLayer2_biases, matrix<_Float64>::scalarMultiply(learningRate, errorLayer2));
        // hiddenLayer1_weights = hiddenLayer1_weights - (learningRate * errorLayer1 * transpose(inputLayer))
        hiddenLayer1_weights = matrix<_Float64>::subtract(hiddenLayer1_weights, (matrix<_Float64>::matrixMultiplication(matrix<_Float64>::scalarMultiply(learningRate, errorLayer1), matrix<_Float64>::transpose(inputLayer))));
        // hiddenLayer1_biases = hiddenLayer1_biases - (learningRate * errorLayer1)
        hiddenLayer1_biases = matrix<_Float64>::subtract(hiddenLayer1_biases, matrix<_Float64>::scalarMultiply(learningRate, errorLayer1));

        //std::cout<<"output layer error"<<std::endl;
        //errorLayerOutput.print();

        //std::cout<<"output Layer weights after backprop"<<std::endl;
        //outputLayerWeights.print();

        //std::cout<<"Layer2 weights after backprop"<<std::endl;
        //hiddenLayer2_weights.print();

        //std::cout<<"Layer1 weights after backprop"<<std::endl;
        //hiddenLayer1_weights.print();
        return 0;
    }
return 0;
    // Then consider the average cost over the training examples.
    std::cout<<"average cost is: " << totalCost/((_Float64)numTrainingSamples)<<std::endl;

    /**
     * Run test images that the network has never seen before, through the network
     */
    for(uint32_t iIter = 0; iIter < 10000; iIter++)
    {
        matrix<uint8_t> testImage = testSamples.getImage(iIter);
        matrix<_Float64> testImageLabel = testSamples.getImageLabel(iIter);

        for(uint32_t jIter = 0; jIter < (testImage.getNumRows() * testImage.getNumColumns()); jIter++)
        {
            inputLayer.assign(static_cast<_Float64>(testImage.at(jIter)), jIter);
        }

        // forward pass through the network
        matrix<_Float64>outputOfLayer1 = activate(hiddenLayer1_weights, inputLayer, hiddenLayer1_biases);
        matrix<_Float64>outputOfLayer2 = activate(hiddenLayer2_weights, outputOfLayer1, hiddenLayer2_biases);
        matrix<_Float64>outputLayer = activate(outputLayerWeights, outputOfLayer2, outputLayerBiases);
        std::cout<<"output of network"<<std::endl;
        outputLayer.print();

        uint32_t outputIndex = 0;
        for(uint32_t jIter = 0; jIter < outputLayer.getNumRows(); jIter++)
        {
            if(outputLayer.at(jIter) > outputLayer.at(outputIndex))
            {
                outputIndex = jIter;
            }
        }
        if(outputIndex != testSamples.getUintLabel(iIter))
        {
            totalWrong++;
        }
        std::cout<<"Network classified image as "<<outputIndex<<std::endl;
        std::cout<<"Image is "<<testSamples.getUintLabel(iIter)<<std::endl;
    }

    std::cout<<"After training, the network has classified "<<totalWrong<<" images wrong out of "<<numTestSamples<<", with an accuracy of "<<((_Float64)(numTestSamples-totalWrong))/((_Float64)numTestSamples)<<"%"<<std::endl;

    return 0;
}