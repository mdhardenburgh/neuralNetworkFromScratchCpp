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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedMatrix(expected, rows, columns);

    //print out matrix before transpose
    std::cout<<"matrix before transpose"<<std::endl;
    dutMatrix.print();

    result = matrix<uint32_t>::transpose(dutMatrix);

    //print out matrix after transpose
    std::cout<<"matrix after transpose"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedMatrix.at(iIter,jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedResult(expected, rowsTransposed, columnsTransposed);

    //print out matrix before transpose
    std::cout<<"matrix before transpose"<<std::endl;
    dut.print();

    result = matrix<uint32_t>::transpose(dut);

    //print out matrix after transpose
    std::cout<<"matrix after transpose"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter++)
        {
            EXPECT_EQ(expectedResult.at(iIter, jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedResult(expected, rowsTransposed, columnsTransposed);

    //print out matrix before transpose
    std::cout<<"matrix before transpose"<<std::endl;
    dut.print();

    result = matrix<uint32_t>::transpose(dut);

    //print out matrix after transpose
    std::cout<<"matrix after transpose"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rowsTransposed; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columnsTransposed; jIter++)
        {
            EXPECT_EQ(expectedResult.at(iIter, jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"dut matrix B"<<std::endl;
    dutB.print();

    //Add A + B
    result = matrix<uint32_t>::add(dutA, dutB);

    std::cout<<"result = A + B"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"dut matrix B"<<std::endl;
    dutB.print();

    // result = A + B
    result = matrix<uint32_t>::add(dutA, dutB);

    std::cout<<"result = A + B"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"dut matrix B"<<std::endl;
    dutB.print();

    // Result = A + B
    result = matrix<uint32_t>::add(dutA, dutB);

    std::cout<<"result = A + B"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> result;
    matrix<uint32_t> expectedDut(expectedResult, rows, columns);

    std::cout<<"dut matrix A"<<std::endl;
    dutA.print();

    std::cout<<"scalar value: "<<scalar<<std::endl;

    // Result = scalar*A
    result = matrix<uint32_t>::scalarMultiply(scalar, dutA);

    std::cout<<"dut matrix scalar * A"<<std::endl;
    result.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), result.at(iIter, jIter));
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
    matrix<uint32_t> resultMatrix;
    matrix<uint32_t> expectedDut(result, 5, 5);

    //print out matrix before multiplication
    std::cout<<"matrixA before multiplication"<<std::endl;
    dutMatrixA.print();
    std::cout<<"matrixB before multiplication"<<std::endl;
    dutMatrixB.print();
    std::cout<<"expected results"<<std::endl;
    expectedDut.print();

    resultMatrix = matrix<uint32_t>::matrixMultiplication(dutMatrixA, dutMatrixB);

    //print out matrix after multiplication
    std::cout<<"result after multiplication"<<std::endl;
    resultMatrix.print();

    for(uint32_t iIter = 0; iIter < 5; iIter++)
    {
        for(uint32_t jIter = 0; jIter < 5; jIter++)
        {
            EXPECT_EQ(expectedDut.at(iIter, jIter), resultMatrix.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_equals_operator_override)
{
    const uint32_t rowsA = 4;
    const uint32_t columnsA = 5;
    const uint32_t rowsB = 5;
    const uint32_t columnsB = 3;
    const uint32_t rowsC = 5;
    const uint32_t columnsC = 2;
    
    uint32_t dataA[rowsA * columnsA] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
    };

    uint32_t dataB[rowsB * columnsB] 
    {
        10, 20, 30, 
        10, 20, 30, 
        10, 20, 30, 
        10, 20, 30,
        10, 20, 30,             
    };
    uint32_t dataC[rowsA * columnsA] 
    {
        1, 1,
        2, 2,
        3, 3,
        4, 4,
        5, 5                    
    };

    matrix<uint32_t> matrixA(dataA, rowsA, columnsA);
    matrix<uint32_t> matrixB(dataB, rowsB, columnsB);
    matrix<uint32_t> matrixC(dataC, rowsC, columnsC);

    std::cout<<"matrixA before assignment"<<std::endl;
    matrixA.print();
    std::cout<<"matrixB before assignment"<<std::endl;
    matrixB.print();
    
    matrixB = matrixA;

    std::cout<<"matrixB after assignment"<<std::endl;
    matrixB.print();

    matrixB = matrixC;

    std::cout<<"matrixB after assignment"<<std::endl;
    matrixB.print();
}

TEST(matrixTest, test_hadamard_product)
{
    const uint32_t rows = 5;
    const uint32_t columns = 5;
    
    
    uint32_t dataA[rows * columns] 
    {
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5, 
        1, 2, 3, 4, 5
    };

    uint32_t dataB[rows * columns] 
    {
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50, 
        10, 20, 30, 40, 50               
    };

    uint32_t dataExpected[rows * columns] 
    {
        10, 40, 90, 160, 250, 
        10, 40, 90, 160, 250, 
        10, 40, 90, 160, 250, 
        10, 40, 90, 160, 250, 
        10, 40, 90, 160, 250               
    };

    matrix<uint32_t> dutMatrixA(dataA, rows, columns);
    matrix<uint32_t> dutMatrixB(dataB, rows, columns);
    matrix<uint32_t> expectedResult(dataExpected, rows, columns);
    matrix<uint32_t> resultMatrix;
    resultMatrix.fillZeros();

    //print out matrix before hadamard product
    std::cout<<"matrixA before multiplication"<<std::endl;
    dutMatrixA.print();
    std::cout<<"matrixB before multiplication"<<std::endl;
    dutMatrixB.print();
    std::cout<<"expected results"<<std::endl;
    expectedResult.print();

    resultMatrix = matrix<uint32_t>::hadamardProduct(dutMatrixA, dutMatrixB);

    std::cout<<"resultMatrix"<<std::endl;
    resultMatrix.print();

    for(uint32_t iIter = 0; iIter < rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < columns; jIter++)
        {
            EXPECT_EQ(expectedResult.at(iIter, jIter), resultMatrix.at(iIter, jIter));
        }
    }
}

TEST(matrixTest, test_multiply_tall_with_wide_matrix_float)
{
    const uint32_t rowsA = 5;
    const uint32_t columnsA = 2;

    const uint32_t rowsB = 2;
    const uint32_t columnsB = 5;

    std::cout<<"4.52 * 66.92 = "<<4.52 * 66.92<<std::endl;
    
    //5X2
    _Float64 dutA[rowsA * columnsA] 
    {
        1.5,   4.6,
        3.8,   2.22,
        6.76,  3.01,
        5.881, 4.0013,
        10.41, 15.2                    
    };

    //2X5
    _Float64 dutB[rowsB * columnsB] 
    {
        4.6001, 45.35,    3.89,  99.3,      55.24, 
        0.0056, 0.125438, 14.66, 7.8002302, 4.56
    };
    
    _Float64 result[5 * 5] 
    {
        6.92591, 68.602,  73.271,  184.831, 103.836, 
        17.4928, 172.608, 47.3272, 394.657, 220.035, 
        31.1135, 306.944, 70.423,  694.747, 387.148, 
        27.0756, 267.205, 81.5361, 615.194, 343.112, 
        47.9722, 474.0,   263.327, 1152.28, 644.36
    };
    
    matrix<_Float64> dutMatrixA(dutA, rowsA, columnsA);
    matrix<_Float64> dutMatrixB(dutB, rowsB, columnsB);
    matrix<_Float64> resultMatrix;
    matrix<_Float64> expectedDut(result, 5, 5);

    //print out matrix before multiplication
    std::cout<<"matrixA before multiplication"<<std::endl;
    dutMatrixA.print();
    std::cout<<"matrixB before multiplication"<<std::endl;
    dutMatrixB.print();
    std::cout<<"expected results"<<std::endl;
    expectedDut.print();

    resultMatrix = matrix<_Float64>::matrixMultiplication(dutMatrixA, dutMatrixB);

    //print out matrix after multiplication
    std::cout<<"result after multiplication"<<std::endl;
    resultMatrix.print();
    
    for(uint32_t iIter = 0; iIter < 5; iIter++)
    {
        for(uint32_t jIter = 0; jIter < 5; jIter++)
        {
            EXPECT_NEAR(expectedDut.at(iIter, jIter), resultMatrix.at(iIter, jIter), 0.01);
        }
    }
}