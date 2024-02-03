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
    std::cout<<"matrix before transpose"<<std::endl;
    dutMatrix.print();

    dutMatrix.transpose();

    //print out matrix after transpose
    std::cout<<"matrix after transpose"<<std::endl;
    dutMatrix.print();

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
    std::cout<<"matrix before transpose"<<std::endl;
    dut.print();

    dut.transpose();

    //print out matrix after transpose
    std::cout<<"matrix after transpose"<<std::endl;
    dut.print();

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
    std::cout<<"matrix before transpose"<<std::endl;
    dut.print();

    dut.transpose();

    //print out matrix after transpose
    std::cout<<"matrix after transpose"<<std::endl;
    dut.print();

    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter++)
        {
            EXPECT_EQ(expectedResult.at(iIter, jIter), dut.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_add_square_matrices)
{
    const uint32_t rows = 5;
    const uint32_t columns = 5;
    
    uint32_t matrixA[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };
    
    uint32_t matrixB[rows * columns] 
    {
        1, 1, 1, 1, 1,
        2, 2, 2, 2, 2,
        3, 3, 3, 3, 3,
        4, 4, 4, 4, 4,
        5, 5, 5, 5, 5                  
    };

    uint32_t expectedResult[rows * columns] 
    {
        2, 3, 4, 5, 6,
        3, 4, 5, 6, 7,
        4, 5, 6, 7, 8,
        5, 6, 7, 8, 9,
        6, 7, 8, 9, 10                  
    };
    
    matrix<uint32_t> dutA(matrixA, rows, columns);
    matrix<uint32_t> dutB(matrixB, rows, columns);
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"dut matrix B"<<std::endl;
    dutB.print();

    //Add Matrix B to A, A + B
    dutA.add(dutB);

    std::cout<<"dut matrix A + B"<<std::endl;
    dutA.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), dutA.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_add_wide_matrices)
{
    const uint32_t rows = 2;
    const uint32_t columns = 5;
    
    uint32_t matrixA[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5 
    };
    
    uint32_t matrixB[rows * columns] 
    {
        1, 1, 1, 1, 1,
        2, 2, 2, 2, 2                
    };

    uint32_t expectedResult[rows * columns] 
    {
        2, 3, 4, 5, 6,
        3, 4, 5, 6, 7                 
    };
    
    matrix<uint32_t> dutA(matrixA, rows, columns);
    matrix<uint32_t> dutB(matrixB, rows, columns);
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"dut matrix B"<<std::endl;
    dutB.print();

    //Add Matrix B to A, A + B
    dutA.add(dutB);

    std::cout<<"dut matrix A + B"<<std::endl;
    dutA.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), dutA.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_add_tall_matrices)
{
    const uint32_t rows = 5;
    const uint32_t columns = 2;
    
    uint32_t matrixA[rows * columns] 
    {
        1, 2,
        1, 2,
        1, 2,
        1, 2,
        1, 2
    };
    
    uint32_t matrixB[rows * columns] 
    {
        1, 1,
        2, 2,
        3, 3,
        4, 4,
        5, 5               
    };

    uint32_t expectedResult[rows * columns] 
    {
        2, 3,
        3, 4,
        4, 5,
        5, 6,
        6, 7           
    };
    
    matrix<uint32_t> dutA(matrixA, rows, columns);
    matrix<uint32_t> dutB(matrixB, rows, columns);
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"dut matrix B"<<std::endl;
    dutB.print();

    //Add Matrix B to A, A + B
    dutA.add(dutB);

    std::cout<<"dut matrix A + B"<<std::endl;
    dutA.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), dutA.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_scalar_multiply)
{
    const uint32_t rows = 5;
    const uint32_t columns = 5;
    const uint32_t scalar = 10;
    
    uint32_t matrixA[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };

    uint32_t expectedResult[rows * columns] 
    {
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50               
    };
    
    matrix<uint32_t> dutA(matrixA, rows, columns);
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"scalar value: "<<scalar<<std::endl;

    //Add Matrix B to A, A + B
    dutA.scalarMultiply(scalar);

    std::cout<<"dut matrix scalar * A"<<std::endl;
    dutA.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), dutA.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_multiply_tall_with_wide_matrix)
{
    const uint32_t rowsA = 5;
    const uint32_t columnsA = 2;

    const uint32_t rowsB = 2;
    const uint32_t columnsB = 5;
    
    //5X2
    uint32_t dutA[rowsA * columnsA] 
    {
        1, 1,
        2, 2,
        3, 3,
        4, 4,
        5, 5                    
    };

    //2X5
    uint32_t dutB[rowsB * columnsB] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };
    
    uint32_t result[5 * 5] 
    {
        2,   4,  6,  8, 10, 
        4,   8, 12, 16, 20,
        6,  12, 18, 24, 30,
        8,  16, 24, 32, 40,
        10, 20, 30, 40, 50
    };
    
    matrix<uint32_t> dutMatrixA(dutA, rowsA, columnsA);
    matrix<uint32_t> dutMatrixB(dutB, rowsB, columnsB);
    matrix<uint32_t> resultMatrix(result, 5, 5);

    //print out matrix before multiplication
    std::cout<<"matrixA before multiplication"<<std::endl;
    dutMatrixA.print();
    std::cout<<"matrixB before multiplication"<<std::endl;
    dutMatrixB.print();
    std::cout<<"expected results"<<std::endl;
    resultMatrix.print();

    dutMatrixA.matrixMultiplication(dutMatrixB);

    //print out matrix after multiplication
    std::cout<<"matrixA after multiplication"<<std::endl;
    dutMatrixA.print();

    for(uint32_t iIter = 0; iIter < 5; iIter++)
    {
        for(uint32_t jIter = 0; jIter < 5; jIter++)
        {
            EXPECT_EQ(resultMatrix.at(iIter, jIter), dutMatrixA.at(iIter, jIter));
        }
    }
}