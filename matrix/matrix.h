#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>


// I suppose you could have a matrix of strings, but it would make no sense
template <class T> class matrix
{
    public:
        
        matrix();
        matrix(const uint32_t& rows, const uint32_t& columns);
        matrix(T* data, const uint32_t& rows, const uint32_t& columns);
        matrix(const matrix& other); //Deep copy constructor
        ~matrix();

        // Get position value at row, column
        T at(const uint32_t& row, const uint32_t& column) const;
        T at(const uint32_t& index) const;
        // Set position value at row, column 
        void assign(T value, const uint32_t& index);
        void assign(T value, const uint32_t& row, const uint32_t& column);

        /**
          * @brief set the matrix to a new set of data
          * 
          * @param data pointer to set the matrix to. Must be same size as Matrix  
          */
        void set(T* data);
        // fill matrix with 0s
        void fillZeros();
        //fill the matrix with specified number
        void fillNumber(T value);
        // fill with a random value
        void fillRandom(T lowerEnd, T upperEnd);
        uint32_t getNumRows() const;
        uint32_t getNumColumns() const;
        static matrix<T> add(const matrix& A, const matrix& B);
        static matrix<T> subtract(const matrix& A, const matrix& B);
        static matrix<T> scalarMultiply(const T& scalar, const matrix& A);
        //vector-vector product
        static matrix<T> matrixMultiplication(const matrix& A, const matrix& B);
        //component-wise product
        static matrix<T> hadamardProduct(const matrix& A, const matrix& B);
        static matrix<T> transpose(const matrix& A);
        void print();
        matrix<T>& operator=(const matrix& other)
        {
            if (this != &other) // self-assignment guard
            {
                // Deallocate existing memory
                if (m_data != nullptr)
                {
                    delete[] m_data;
                    m_data = nullptr;
                }

                // Copy new data
                m_rows = other.m_rows;
                m_columns = other.m_columns;
                m_data = new T[m_rows * m_columns];
                
                for (uint32_t i = 0; i < m_rows * m_columns; i++)
                {
                    m_data[i] = other.m_data[i];
                }
            }
            else
            {
                printf("assigning to self");
            }
            return *this;
        }
        //void dotProduct(matrix B);
        //void crossProduct(matrix B);
        //int32_t determinant();

    private:

        //pointer to an array
        T* m_data = nullptr;
        uint32_t m_rows = 0;
        uint32_t m_columns = 0;
};

template <class T> matrix<T>::matrix()
{
    m_data = new T[m_rows*m_columns];
}

//copy constructor
template <class T> matrix<T>::matrix(const matrix& other)
{
    m_rows = other.m_rows;
    m_columns = other.m_columns;
    m_data = new T[m_rows * m_columns];

    for (uint32_t i = 0; i < m_rows * m_columns; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}

template <class T> matrix<T>::matrix(const uint32_t& rows, const uint32_t& columns)
{
    if(rows < 1)
    {
        std::cout<<__PRETTY_FUNCTION__<<": rows is less than 1!!!!"<<std::endl;
        assert(false);
    }
    if(columns < 1)
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns is less than 1!!!!"<<std::endl;
        assert(false);
    }

    m_rows = rows;
    m_columns = columns;

    m_data = new T[m_rows*m_columns];
}

template <class T> matrix<T>::matrix(T* data, const uint32_t& rows, const uint32_t& columns)
{
    if(rows < 1)
    {
        std::cout<<__PRETTY_FUNCTION__<<": rows is less than 1!!!!"<<std::endl;
        assert(false);
    }
    if(columns < 1)
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns is less than 1!!!!"<<std::endl;
        assert(false);
    }
    if(data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": data is nullptr!!!!"<<std::endl;
        assert(false);
    }

    m_rows = rows;
    m_columns = columns;


    m_data = new T[m_rows*m_columns];

    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        m_data[iIter] = data[iIter];
    }

}

template <class T> matrix<T>::~matrix()
{
    if(m_data != nullptr)
    {
        delete[] m_data;
        m_data = nullptr;
    }
}

template <class T> void matrix<T>::set(T* data)
{
    if(data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": data is nullptr!!!!"<<std::endl;
        assert(false);
    }

    if(m_data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_data is nullptr!!!!"<<std::endl;
        assert(false);
    }
        
    if(sizeof(data)/sizeof(T) == (m_rows*m_columns))
    {
        std::cout<<__PRETTY_FUNCTION__<<": data is is not the right size!!!!"<<std::endl;
        assert(false);
    }

    if(m_data != nullptr)
    {
        delete[] m_data;
    }

    m_data = new T[m_rows * m_columns];

    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        m_data[iIter] = data[iIter];
    }
}

template <class T> void matrix<T>::fillZeros()
{
    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        m_data[iIter] = 0;
    }
}

template <class T> void matrix<T>::fillNumber(T value)
{
    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        m_data[iIter] = value;
    }
}

template <class T> void matrix<T>::fillRandom(T lowerBound, T upperBound)
{
    srand (static_cast <unsigned> (time(0)));
    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        m_data[iIter] = lowerBound + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX/(upperBound-lowerBound)));
    }
}

template <class T> T matrix<T>::at(const uint32_t& row, const uint32_t& column) const
{
    
    if(m_data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_data is nullptr!!!!"<<std::endl;
        assert(false);
    }
    if(row > m_rows)
    {
        std::cout<<__PRETTY_FUNCTION__<<": row "<<row<<" is greater than number of rows "<<m_rows<<" in matrix!!!!"<<std::endl;
        assert(false);
    }
    if(column > m_columns)
    {
        std::cout<<__PRETTY_FUNCTION__<<": column "<<column<<" is greater than number of columns "<<m_columns<<" in matrix!!!!"<<std::endl;
        assert(false);
    }

    /*
     * 1 2 3 4 5
     * 1 2 3 4 5
     * 1 2 3 4 5
     * matrix in memory looks like
     * 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5
     * 
     * so if we want the value at row 1 (zero index) and column 2 (zero index)
     * 
     * That is position 7 in the matrix when it is flattened in memory.
     * To get there, row + column doesn't work that results in 3. Row * column
     * doesn't work, that results in 2. 
     * 
     * Row * m_columns + column = 1(5) + 2 = 7. The correct position
     */
    
    return m_data[(row * m_columns) + column];
}

template <class T> T matrix<T>::at(const uint32_t& index) const
{
    if(m_data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_data is nullptr!!!!"<<std::endl;
        assert(false);
    }
    if(index > (m_rows*m_columns))
    {
        std::cout<<__PRETTY_FUNCTION__<<": index requested is greater than size of matrix!!!!"<<std::endl;
        assert(false);
    }
    
    /**
     * generally its pretty hard to visualize a 2D matrix flattened in memory,
     * which is why the at(row, column) version of this function exists. Buuuut
     * sometimes its better to access the 2D matrix in a flattened version. 
    */
    return m_data[index];
}

template <class T> void matrix<T>::assign(T value, const uint32_t& index)
{
    if(m_data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_data is nullptr!!!!"<<std::endl;
        assert(false);
    }
        if(index > (m_rows*m_columns))
    {
        std::cout<<__PRETTY_FUNCTION__<<": index requested is greater than size of matrix!!!!"<<std::endl;
        assert(false);
    }

    /**
     * generally its pretty hard to visualize a 2D matrix flattened in memory,
     * which is why the at(row, column) version of this function exists. Buuuut
     * sometimes its better to access the 2D matrix in a flattened version. 
    */
    m_data[index] = value;
}

template <class T> void matrix<T>::assign(T value, const uint32_t& row, const uint32_t& column)
{
    if(m_data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_data is nullptr!!!!"<<std::endl;
        assert(false);
    }
    if(row > m_rows)
    {
        std::cout<<__PRETTY_FUNCTION__<<": row "<<row<<" is greater than number of rows "<<m_rows<<" in matrix!!!!"<<std::endl;
        assert(false);
    }
    if(column > m_columns)
    {
        std::cout<<__PRETTY_FUNCTION__<<": column "<<column<<" is greater than number of columns "<<m_columns<<" in matrix!!!!"<<std::endl;
        assert(false);
    }
    
    m_data[(row * m_columns) + column] = value;
}

template <class T> uint32_t matrix<T>::getNumRows() const
{
    return m_rows;
}
template <class T> uint32_t matrix<T>::getNumColumns() const
{
    return m_columns;
}

template <class T> matrix<T> matrix<T>::add(const matrix& A, const matrix& B)
{
    if(A.getNumRows() != B.getNumRows())
    {
        std::cout<<__PRETTY_FUNCTION__<<": rows of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    if(A.getNumColumns() != B.getNumColumns())
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    matrix<T> C(A.getNumRows(), A.getNumColumns());

    for(uint32_t iIter = 0; iIter < (A.getNumRows()*A.getNumColumns()); iIter ++)
    {
        
        C.assign(A.at(iIter) + B.at(iIter), iIter);
    }
    return C;
}

template <class T> matrix<T> matrix<T>::subtract(const matrix& A, const matrix& B)
{
    if(A.getNumRows() != B.getNumRows())
    {
        std::cout<<__PRETTY_FUNCTION__<<": rows of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    if(A.getNumColumns() != B.getNumColumns())
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    matrix<T> C(A.getNumRows(), A.getNumColumns());

    for(uint32_t iIter = 0; iIter < (A.getNumRows()*A.getNumColumns()); iIter ++)
    {
        
        C.assign(A.at(iIter) - B.at(iIter), iIter);
    }
    return C;
}

template <class T> void matrix<T>::print()
{
    for(uint32_t iIter = 0; iIter < m_rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < m_columns; jIter ++)
        {
            std::cout<<at(iIter, jIter)<<" ";
        }        
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}


template <class T> matrix<T> matrix<T>::scalarMultiply(const T& scalar, const matrix& A)
{
    matrix<T> C(A.getNumRows(), A.getNumColumns());
    
    for(uint32_t iIter = 0; iIter < (A.getNumRows() * A.getNumColumns()); iIter ++)
    {
        C.assign(scalar * A.at(iIter), iIter);
    }

    return C;
}


template <class T> matrix<T> matrix<T>::matrixMultiplication(const matrix& A, const matrix& B)
{
    if(A.getNumColumns() != B.getNumRows())
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns of A and rows of B must be equal!!!!"<<std::endl;
        std::cout<<__PRETTY_FUNCTION__<<": columns of A are "<<A.getNumColumns()<<std::endl;
        std::cout<<__PRETTY_FUNCTION__<<": rows of B are "<<B.getNumRows()<<std::endl;

        assert(false);
    }

    matrix<T> C(A.getNumRows(), B.getNumColumns());

    /* 
     * matrix multiplication is always the sum of the rows of A times the columns of B
     * 
     * Matrix A 3 X 5
     * 3 rows, 5 columns
     * 1 2 3 4 5
     * 1 2 3 4 5
     * 1 2 3 4 5
     * matrix in memory looks like
     * 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5
     * 
     * Matrix B 5 X 4
     * 5 rows, 4 columns
     * 1 1 1 1
     * 2 2 2 2
     * 3 3 3 3
     * 4 4 4 4
     * 5 5 5 5
     * matrix in memory looks like
     * 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 5 5 5 5
     */

    for(uint32_t iIter = 0; iIter < A.getNumRows(); iIter++)
    {
        for(uint32_t jIter = 0; jIter < B.getNumColumns(); jIter++)
        {
            T value = 0.0f;
            for(uint32_t kIter = 0; kIter < A.getNumColumns(); kIter++)
            {
                //result[(iIter * B.getNumColumns()) + jIter] += A.at(iIter, kIter) * B.at(kIter, jIter);
                //C.assign(C.at((iIter * B.getNumColumns()) + jIter) + A.at(iIter, kIter) * B.at(kIter, jIter), (iIter * B.getNumColumns()) + jIter);
                value += A.at(iIter,kIter) * B.at(kIter, jIter);
            }
            C.assign(value, iIter, jIter);
        }
    }
    return C;
}

template <class T> matrix<T> matrix<T>::hadamardProduct(const matrix& A, const matrix& B)
{
    if(A.getNumRows() != B.getNumRows())
    {
        std::cout<<__PRETTY_FUNCTION__<<": rows of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    if(A.getNumColumns() != B.getNumColumns())
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    T* tempArr = new T[A.getNumRows()*A.getNumColumns()];
    matrix<T> C(tempArr, A.getNumRows(), A.getNumColumns());

    for(uint32_t iIter = 0; iIter < (A.getNumRows()*A.getNumColumns()); iIter ++)
    {
        
        C.assign(A.at(iIter) * B.at(iIter), iIter);
    }

    delete[] tempArr;

    return C;
}

template <class T> matrix<T> matrix<T>::transpose(const matrix& A)
{
    matrix<T> C(A.getNumColumns(), A.getNumRows());

    /* 3 X 5
     * 3 rows, 5 columns
     * 1 2 3 4 5
     * 1 2 3 4 5
     * 1 2 3 4 5
     * matrix in memory looks like
     * 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5
     * 
     * 5 X 3
     * 5 rows, 3 columns
     * 1 1 1
     * 2 2 2
     * 3 3 3
     * 4 4 4
     * 5 5 5
     * matrix in memory looks like
     * 1 1 1 2 2 2 3 3 3 4 4 4 5 5 5
     */

    //iIter is rows
    for(uint32_t iIter = 0; iIter < A.getNumRows(); iIter++)
    {
        //jIter is columns
        for(uint32_t jIter = 0; jIter < A.getNumColumns(); jIter++)
        {
            C.assign(A.at(iIter, jIter), jIter, iIter);
        }       
    }

    return C;
}

#endif //MATRIX_H