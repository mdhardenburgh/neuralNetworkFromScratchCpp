#include "mnistDataReader.h"

#include <iostream>

int main()
{
    mnistDataReader reader("mnistDataset/train-images.idx3-ubyte", "mnistDataset/train-labels.idx1-ubyte", 10);

    reader.printImage(5);
    reader.printImage(8);
    reader.printImage(3);
    reader.printImage(6);
    reader.printImage(9);

    return 0;
}