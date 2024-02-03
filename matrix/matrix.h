#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <memory>


// I suppose you could have a matrix of strings, but it would make no sense
template <class T> class matrix
{
    public:
        
        matrix();
        matrix(T* data, const uint32_t& rows, const uint32_t& columns);
        ~matrix();

        T at(const uint32_t& row, const uint32_t& column) const;
        T at(const uint32_t& index) const;
        void transpose();
        uint32_t getNumRows() const;
        uint32_t getNumColumns() const;
        void add(const matrix& B);
        void print();
        void scalarMultiply(const T& scalar);
        void matrixMultiplication(const matrix& B);
        //void dotProduct(matrix B);
        //void crossProduct(matrix B);
        //int32_t determinant();

    private:

        //pointer to an array
        T* m_data = nullptr;
        uint32_t m_rows;
        uint32_t m_columns;
};

template <class T> matrix<T>::matrix()
{

}

template <class T> matrix<T>::matrix(T* data, const uint32_t& rows, const uint32_t& columns)
{
    m_rows = rows;
    m_columns = columns;

    m_data = new T[m_rows*m_columns];

    if(m_rows < 1)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_rows is less than 1!!!!"<<std::endl;
        assert(false);
    }
    if(m_columns < 1)
    {
        std::cout<<__PRETTY_FUNCTION__<<": m_columns is less than 1!!!!"<<std::endl;
        assert(false);
    }
    if(data == nullptr)
    {
        std::cout<<__PRETTY_FUNCTION__<<": data is nullptr!!!!"<<std::endl;
        assert(false);
    }

    for(uint32_t iIter = 0; iIter < m_rows * m_columns; iIter++)
    {
        m_data[iIter] = data[iIter];
    }

}

template <class T> matrix<T>::~matrix()
{
    //delete m_data;
}

template <class T> T matrix<T>::at(const uint32_t& row, const uint32_t& column) const
{
    
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
    /**
     * generally its pretty hard to visualize a 2D matrix flattened in memory,
     * which is why the at(row, column) version of this function exists. Buuuut
     * sometimes its better to access the 2D matrix in a flattened version. 
    */
    return m_data[index];
}

template <class T> void matrix<T>::transpose()
{
    T* temp = m_data;
    m_data = new T[m_rows * m_columns];
    uint32_t newRows = m_columns;
    uint32_t newColumns = m_rows;

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
    for(uint32_t iIter = 0; iIter < m_rows; iIter++)
    {
        //jIter is columns
        for(uint32_t jIter = 0; jIter < m_columns; jIter++)
        {
            m_data[(jIter * newColumns) + iIter] = temp[(iIter * m_columns) + jIter];
        }       
    }

    m_rows = newRows;
    m_columns = newColumns;
    delete temp;
}

template <class T> uint32_t matrix<T>::getNumRows() const
{
    return m_rows;
}
template <class T> uint32_t matrix<T>::getNumColumns() const
{
    return m_columns;
}

template <class T> void matrix<T>::add(const matrix& B)
{
    if(m_rows != B.getNumRows())
    {
        std::cout<<__PRETTY_FUNCTION__<<": rows of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    if(m_columns != B.getNumColumns())
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns of the matrices must be equal!!!!"<<std::endl;
        assert(false);
    }

    for(uint32_t iIter = 0; iIter < (m_rows * m_columns); iIter ++)
    {
        m_data[iIter] = m_data[iIter] + B.at(iIter);
    }

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

template <class T> void matrix<T>::scalarMultiply(const T& scalar)
{
    for(uint32_t iIter = 0; iIter < (m_rows * m_columns); iIter ++)
    {
        m_data[iIter] = scalar * m_data[iIter];
    }    
}

template <class T> void matrix<T>::matrixMultiplication(const matrix& B)
{
    if(m_columns != B.getNumRows())
    {
        std::cout<<__PRETTY_FUNCTION__<<": columns of A and rows of B must be equal!!!!"<<std::endl;
        std::cout<<__PRETTY_FUNCTION__<<": columns of A are"<<m_columns<<std::endl;
        std::cout<<__PRETTY_FUNCTION__<<": rows of B are"<<B.getNumRows()<<std::endl;

        assert(false);
    }

    T* result = new T[m_rows * B.getNumColumns()];

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

    for(uint32_t iIter = 0; iIter < m_rows; iIter++)
    {
        //rows of B
        for(uint32_t jIter = 0; jIter < B.getNumColumns(); jIter++)
        {
            //columns of B
            for(uint32_t kIter = 0; kIter < m_columns; kIter++)
            {
                result[(iIter * B.getNumColumns()) + jIter] += at(iIter, kIter) * B.at(kIter, jIter);
            }
        }
    }
    //m_data[(row * m_columns) + column]

    m_columns = B.getNumColumns();
    T* temp = m_data;
    m_data = result;
    delete temp;

}

#endif //MATRIX_H