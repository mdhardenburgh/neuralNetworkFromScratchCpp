#ifndef MNIST_DATA_READER_H
#define MNIST_DATA_READER_H

#include "matrix.h"

#include <string>
#include <vector>

//Use to read in 
class mnistDataReader
{
    public:
    
        mnistDataReader();
        mnistDataReader(std::string dataFilePath, std::string labelsFilePath, uint32_t numImagesToRead);
        ~mnistDataReader();

        void printImage(uint32_t imageIndex);

    private:

        uint32_t m_mnistImageChecksum = 2051;
        uint32_t m_mnistLabelChecksum = 2049;
        const uint32_t m_sizeOfUint32 = 4; //usually a uint32 is 4 bytes, but not always
        uint32_t m_rows = 0; // number of pixels in each row
        uint32_t m_columns = 0; //number of pixels in each column;
        std::vector<matrix<uint8_t>> m_images;
        std::vector<uint32_t> m_labels;

        uint32_t changeEndian(uint32_t input);
        uint32_t normalize(uint32_t input);
};

#endif //MNIST_DATA_READER_H