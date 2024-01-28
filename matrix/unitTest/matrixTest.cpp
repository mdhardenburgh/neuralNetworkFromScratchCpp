#include <iostream>
#include <gtest/gtest.h>

#include "matrix.h"

TEST(matrixTest, test_transpose_function_square_matrix)
{
    const uint32_t rows = 5;
    const uint32_t columns = 5;
    
    uint32_t testMatrix[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };
    
    uint32_t expected[rows * columns] 
    {
        1, 1, 1, 1, 1,
        2, 2, 2, 2, 2,
        3, 3, 3, 3, 3,
        4, 4, 4, 4, 4,
        5, 5, 5, 5, 5                    
    };
    
    matrix<uint32_t> myMatrix(testMatrix, rows, columns);

    //print out matrix before transpose
    for(uint32_t iIter = 0; iIter < (rows * columns); iIter++)
    {
        if(iIter%columns == 0)
        {
            std::cout<<std::endl;
        }
        
        std::cout<<myMatrix.at(iIter)<<" ";
    }
    std::cout<<std::endl;

    myMatrix.transpose();

    //print out matrix after transpose
    for(uint32_t iIter = 0; iIter < (rows * columns); iIter++)
    {
        if(iIter%columns == 0)
        {
            std::cout<<std::endl;
        }
        
        std::cout<<myMatrix.at(iIter)<<" ";
    }
    std::cout<<std::endl;

    for(uint32_t iIter = 0; iIter < (rows * columns); iIter++)
    {
        EXPECT_EQ(expected[iIter], myMatrix.at(iIter));
    }
}

TEST(matrixTest, test_transpose_function_not_square_matrix)
{
    const uint32_t rows = 2;
    const uint32_t columns = 5;
    
    uint32_t testMatrix[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };
    
    uint32_t expected[rows * columns] 
    {
        1, 1,
        2, 2,
        3, 3,
        4, 4,
        5, 5                    
    };
    
    matrix<uint32_t> myMatrix(testMatrix, rows, columns);

    //print out matrix before transpose
    for(uint32_t iIter = 0; iIter < (rows * columns); iIter++)
    {
        if(iIter%columns == 0)
        {
            std::cout<<std::endl;
        }
        
        std::cout<<myMatrix.at(iIter)<<" ";
    }
    std::cout<<std::endl;

    myMatrix.transpose();

    //print out matrix after transpose
    for(uint32_t iIter = 0; iIter < (rows * columns); iIter++)
    {
        if(iIter%columns == 0)
        {
            std::cout<<std::endl;
        }
        
        std::cout<<myMatrix.at(iIter)<<" ";
    }
    std::cout<<std::endl;

    for(uint32_t iIter = 0; iIter < (rows * columns); iIter++)
    {
        EXPECT_EQ(expected[iIter], myMatrix.at(iIter));
    }
}

