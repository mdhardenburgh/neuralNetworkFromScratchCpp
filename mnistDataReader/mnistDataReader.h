/**
 * MNIST data reader class. 
 * Reads in the MNIST data stored in byte format 
 * Copyright (C) 2024  Matthew Hardenburgh, matthew@hardenburgh.io
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef MNIST_DATA_READER_H
#define MNIST_DATA_READER_H

#include "matrix.h"
#include <string>
#include <vector>

/**
 * We need to be able to read in the MNIST data. We know that each image is 784 
 * pixels and that there are a set number of images
 */
class mnistDataReader
{
    public:
    
        /**
         * @brief empty constructor
        */
        mnistDataReader();
        /**
         * @brief given params, reads in the image data and label data files and stores them in vectors
         * @param dataFilePath path to where the MNIST image data is stored
         * @param labelsFilePath path to where the MNIST label data is stored
         * @param numImagesToRead number of images with labels to read
        */
        mnistDataReader(std::string dataFilePath, std::string labelsFilePath, uint32_t numImagesToRead);
        /**
         * @brief deconstructor
        */
        ~mnistDataReader();

        /**
         * @brief fetches image at given index
         * @param index index of image to fetch
         * @return matrix of image data at given index
        */
        matrix<uint8_t> getImage(uint32_t index);
        /**
         * @brief fetches label of an image at a given index
         * @param index index of image label to fetch
         * @return label as a one-hot encoded 10x1 matrix
        */
        matrix<_Float64> getImageLabel(uint32_t index);
        /**
         * @brief fetches label of an image at a given index
         * @param index index of image label to fetch
         * @return label as a uint32
        */
        uint32_t getUintLabel(uint32_t index);
        /**
         * @brief prints the image with label to std out. Image is represented in
         *        a 28x28 grid of chars, where the greyscale is normalized from
         *        0-255 to 0-9.
         * @param index index of image to print
        */
        void printImage(uint32_t imageIndex);

    private:

        uint32_t m_mnistImageChecksum = 2051;
        uint32_t m_mnistLabelChecksum = 2049;
        const uint32_t m_sizeOfUint32 = 4; //usually a uint32 is 4 bytes, but not always
        uint32_t m_rows = 0; // number of pixels in each row
        uint32_t m_columns = 0; //number of pixels in each column;
        std::vector<matrix<uint8_t>> m_images;
        std::vector<matrix<_Float64>> m_imagesFloats;
        std::vector<uint32_t> m_labels;
        std::vector<matrix<_Float64>> m_labelsOneHot;

        /**
         * @brief change the endianness of the byte that was read out
         * @details Used with the first few bytes that are metadata about the 
         * dataset, such as num rows, columns or checksum
         * @param input byte to change the endianness
         * @return byte with the correct endianness
        */
        uint32_t changeEndian(uint32_t input);
        /**
         * @brief normalize a pixel value from 0 through 255, to 0 through 9
         * @param input a MNIST image data pixel with a value between 0 and 255
         * @return a MINST image data pixel that has been normalized between 0 and 9
        */
        uint32_t normalize(uint32_t input);
        /**
         * @brief convert MNIST label from a uint32 to a one-hot encoded matrix
         * @param labelAsNumber MNIST image label as a uint32
         * @return MNIST image label as a one-hot encoded matrix
        */
        matrix<_Float64> convertToOneHot(uint32_t labelAsNumber);
};

#endif //MNIST_DATA_READER_H