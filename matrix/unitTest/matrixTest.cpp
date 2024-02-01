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
    
    matrix<uint32_t> dutMatrix(testMatrix, rows, columns);
    matrix<uint32_t> expectedMatrix(expected, rows, columns);

    //print out matrix before transpose
     for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter ++)
        {
            std::cout<<dutMatrix.at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    dutMatrix.transpose();

    //print out matrix after transpose
     for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter ++)
        {
            std::cout<<dutMatrix.at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedMatrix.at(iIter,jIter), dutMatrix.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_transpose_function_not_square_matrix_wide_to_tall)
{
    const uint32_t rows = 2;
    const uint32_t columns = 5;
    const uint32_t rowsTransposed = columns;
    const uint32_t columnsTransposed = rows;
    
    uint32_t testMatrix[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };
    
    uint32_t expected[rowsTransposed * columnsTransposed] 
    {
        1, 1,
        2, 2,
        3, 3,
        4, 4,
        5, 5                    
    };
    
    matrix<uint32_t> dut(testMatrix, rows, columns);
    matrix<uint32_t> expectedResult(expected, rowsTransposed, columnsTransposed);

    //print out matrix before transpose
    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter ++)
        {
            std::cout<<dut.at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    dut.transpose();

    //print out matrix after transpose
    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter ++)
        {
            std::cout<<dut.at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter++)
        {
            EXPECT_EQ(expectedResult.at(iIter, jIter), dut.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_transpose_function_not_square_matrix_tall_to_wide)
{
    const uint32_t rows = 5;
    const uint32_t columns = 2;
    const uint32_t rowsTransposed = columns;
    const uint32_t columnsTransposed = rows;
    
    uint32_t dutMatrix[rowsTransposed * columnsTransposed] 
    {
        1, 1,
        2, 2,
        3, 3,
        4, 4,
        5, 5                    
    };

    uint32_t expected[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };
    
    
    matrix<uint32_t> dut(dutMatrix, rows, columns);
    matrix<uint32_t> expectedResult(expected, rowsTransposed, columnsTransposed);

    //print out matrix before transpose
    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter ++)
        {
            std::cout<<dut.at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    dut.transpose();

    //print out matrix after transpose
    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter ++)
        {
            std::cout<<dut.at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter++)
        {
            EXPECT_EQ(expectedResult.at(iIter, jIter), dut.at(iIter, jIter));
        }
    }
}

