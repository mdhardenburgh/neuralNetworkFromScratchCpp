#include <gtest/gtest.h>
#include "matrix.h"

TEST(matrixTest, test_transpose_function)
{
    uint32_t testMatrix[5][5] 
    {
        {1, 2, 3, 4, 5}, 
        {1, 2, 3, 4, 5}, 
        {1, 2, 3, 4, 5}, 
        {1, 2, 3, 4, 5}, 
        {1, 2, 3, 4, 5}
    };
    uint32_t expected[5][5] 
    {
        {1, 1, 1, 1, 1},
        {2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3},
        {4, 4, 4, 4, 4},
        {5, 5, 5, 5, 5}                    
    };
    matrix<uint32_t> myMatrix(reinterpret_cast<uint32_t*>(testMatrix), 5, 5);
    myMatrix.transpose();
    for(uint32_t iIter = 0; iIter < 5; iIter++)
    {
        for(uint32_t jIter = 0; jIter < 5; jIter++)
        {
            EXPECT_EQ(expected[iIter][jIter], myMatrix.at(iIter, jIter));
        }
    }
}

