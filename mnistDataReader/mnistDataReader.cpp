#include "mnistDataReader.h"
#include "matrix.h"

#include <iostream>
#include <fstream>
#include <cassert>

mnistDataReader::mnistDataReader()
{
    
}

//can I multi thread this? one thread for reading labels and one thread for reading data?
mnistDataReader::mnistDataReader(std::string dataFilePath, std::string labelsFilePath, uint32_t numImagesToRead)
{
    // can I use a shared pointer?
    char* dataOutOfFile = new char[m_sizeOfUint32];
    char* labelsOutOfFile = new char[m_sizeOfUint32];

    //Open pixel data file stream 
    std::ifstream inputDataFileStream(dataFilePath.c_str(), std::ios::in | std::ios::binary);
    //Open label data file stream
    std::ifstream inputLabelFileStream(labelsFilePath.c_str(), std::ios::in | std::ios::binary);

    uint32_t sizeOfDataFile = 0;
    uint32_t sizeOfLabelFile = 0;

    if(!inputDataFileStream.is_open() || !inputLabelFileStream.is_open())
    {
        std::cout<<__PRETTY_FUNCTION__<<": could not open files"<<std::endl;
        assert(false);
    }

    if(numImagesToRead == 0)
    {
        std::cout<<__PRETTY_FUNCTION__<<": hey dummy you're reading 0 images from the file, why???"<<std::endl;
        assert(false);
    }

    if(dataFilePath.empty())
    {
        std::cout<<__PRETTY_FUNCTION__<<": dataFilePath is empty"<<std::endl;
        assert(false);
    }
    if(labelsFilePath.empty())
    {
        std::cout<<__PRETTY_FUNCTION__<<": labelsFilePath is empty"<<std::endl;
        assert(false);
    }

    // First 4 bytes of both files are a checksum 
    inputDataFileStream.read(dataOutOfFile, m_sizeOfUint32);
    inputLabelFileStream.read(labelsOutOfFile, m_sizeOfUint32);
    std::cout<<__PRETTY_FUNCTION__<<": raw mnist image checksum is "<<*reinterpret_cast<uint32_t*>(dataOutOfFile)<<std::endl;
    std::cout<<__PRETTY_FUNCTION__<<": mnist image checksum after changeEndian is "<<changeEndian(*reinterpret_cast<uint32_t*>(dataOutOfFile))<<std::endl;
    if(m_mnistImageChecksum != changeEndian(*reinterpret_cast<uint32_t*>(dataOutOfFile)))
    {
        std::cout<<__PRETTY_FUNCTION__<<": mnist image checksum failed!"<<std::endl;
        assert(false);
    }
    if(m_mnistLabelChecksum != changeEndian(*reinterpret_cast<uint32_t*>(labelsOutOfFile)))
    {
        std::cout<<__PRETTY_FUNCTION__<<": mnist labels checksum failed!"<<std::endl;
        assert(false);
    }

    // second 4 bytes of both files are the total number of images or labels
    inputDataFileStream.read(dataOutOfFile, m_sizeOfUint32);
    inputLabelFileStream.read(labelsOutOfFile, m_sizeOfUint32);
    sizeOfDataFile = changeEndian(*reinterpret_cast<uint32_t*>(dataOutOfFile));
    sizeOfLabelFile = changeEndian(*reinterpret_cast<uint32_t*>(labelsOutOfFile));
    delete labelsOutOfFile;

    std::cout<<__PRETTY_FUNCTION__<<": number of images is "<<sizeOfDataFile<<std::endl;
    std::cout<<__PRETTY_FUNCTION__<<": number of labels is "<<sizeOfLabelFile<<std::endl;

    if(numImagesToRead > sizeOfDataFile)
    {
        std::cout<<__PRETTY_FUNCTION__<<": number of images you want to read, which is" << numImagesToRead << "exceeds the number of images in the file which is "<< sizeOfDataFile <<std::endl;
        assert(false);
    }

    if(sizeOfDataFile != sizeOfLabelFile)
    {
        std::cout<<__PRETTY_FUNCTION__<<"number of images, " << sizeOfDataFile << ", doesn't match number of labels, "<<sizeOfLabelFile<<std::endl;
    }

    //get number of rows
    inputDataFileStream.read(dataOutOfFile, m_sizeOfUint32);
    m_rows = changeEndian(*reinterpret_cast<uint32_t*>(dataOutOfFile));
    std::cout<<__PRETTY_FUNCTION__<<": number of pixels in each row is "<<m_rows<<std::endl;

    //get number of columns
    inputDataFileStream.read(dataOutOfFile, m_sizeOfUint32);
    m_columns = changeEndian(*reinterpret_cast<uint32_t*>(dataOutOfFile));
    std::cout<<__PRETTY_FUNCTION__<<": number of pixels in each column is "<<m_columns<<std::endl;
    delete dataOutOfFile;

    //copy image pixel data from the MNIST dataset to 784x1 Matrix and stuff into vector
    dataOutOfFile = new char[m_rows*m_columns];
    for(uint32_t iter = 0; iter < numImagesToRead; iter++)
    {
        inputDataFileStream.read(dataOutOfFile, m_rows*m_columns);
        matrix<uint8_t> temp(reinterpret_cast<uint8_t*>(dataOutOfFile), m_rows * m_columns, 1);
        m_images.push_back(temp);
    }

    delete dataOutOfFile;
    inputDataFileStream.close();

    // copy label data from the MNIST dataset to a vector
    labelsOutOfFile = new char[sizeOfLabelFile];
    inputLabelFileStream.read(labelsOutOfFile, sizeOfLabelFile);
    for(uint32_t iIter = 0; iIter < sizeOfLabelFile; iIter++)
    {
        m_labels.push_back(static_cast<uint32_t>(labelsOutOfFile[iIter]));
        m_labelsOneHot.push_back(convertToOneHot(m_labels[iIter]));
    }
    inputLabelFileStream.close();
    delete labelsOutOfFile;
}

mnistDataReader::~mnistDataReader()
{

}

matrix<uint8_t> mnistDataReader::getImage(uint32_t index)
{
    return m_images.at(index);
}

matrix<_Float32> mnistDataReader::getImageLabel(uint32_t index)
{
    return m_labelsOneHot.at(index);
}

//Convert to onehot binary format
matrix<_Float32> mnistDataReader::convertToOneHot(uint32_t labelAsNumber)
{
    _Float32* oneHotArray;
    
    switch(labelAsNumber)
    {
        case 0:
        {
            _Float32 tempArr[10] = 
            {
                1, // 0
                0, // 1
                0, // 2
                0, // 3
                0, // 4
                0, // 5
                0, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }  
        case 1:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0
                1, // 1
                0, // 2
                0, // 3
                0, // 4
                0, // 5
                0, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 2:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                1, // 2
                0, // 3
                0, // 4
                0, // 5
                0, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 3:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                1, // 3
                0, // 4
                0, // 5
                0, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 4:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                0, // 3
                1, // 4
                0, // 5
                0, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 5:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                0, // 3
                0, // 4
                1, // 5
                0, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 6:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                0, // 3
                0, // 4
                0, // 5
                1, // 6
                0, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 7:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                0, // 3
                0, // 4
                0, // 5
                0, // 6
                1, // 7
                0, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 8:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                0, // 3
                0, // 4
                0, // 5
                0, // 6
                0, // 7
                1, // 8
                0  // 9
            };
            oneHotArray = tempArr;
            break;
        }
        case 9:
        {
            _Float32 tempArr[10] = 
            {
                0, // 0 
                0, // 1
                0, // 2
                0, // 3
                0, // 4
                0, // 5
                0, // 6
                0, // 7
                0, // 8
                1  // 9
            };
            oneHotArray = tempArr;
            break;
        }
    }

    matrix<_Float32> tempOneHotEncode(oneHotArray, 10, 1);

    return tempOneHotEncode;
}

// if you want to know it worked or not
void mnistDataReader::printImage(uint32_t imageIndex)
{
    matrix<uint8_t> temp = m_images.at(imageIndex);

    std::cout<<"Labels is: " << m_labels[imageIndex]<<std::endl;

    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        if((iIter%28) == 0)
        {
            std::cout<<std::endl;
        }

        std::cout<<normalize(temp.at(iIter, 0));
    
    }
    std::cout<<std::endl;
}

uint32_t mnistDataReader::changeEndian(uint32_t input)
{
    uint32_t retVal = 0;
    for(uint32_t iter = 0; iter < m_sizeOfUint32; iter++)
    {
        retVal |= (((input>>(iter*8)) & 0xFF) << ((m_sizeOfUint32 - (iter + 1)) * 8));
    }

    return retVal;
}

uint32_t mnistDataReader::normalize(uint32_t input)
{
    _Float32 maxOfInput = 255.0; //max pixel value
    _Float32 minOfInput = 0.0;
    _Float32 maxOfOutput = 9.0;
    _Float32 minOfOutput = 0.0;

    int retval = (((_Float32)input - minOfInput)/(maxOfInput - minOfInput)) * ((maxOfOutput - minOfOutput)+ minOfOutput);

    return static_cast<int>(retval);

}