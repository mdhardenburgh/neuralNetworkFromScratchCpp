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

        T at(const uint32_t& row, const uint32_t& column);
        void transpose();
        matrix add(matrix B);
        //void scalarMultiply(matrix B);
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
    delete m_data;
}

template <class T> T matrix<T>::at(const uint32_t& row, const uint32_t& column)
{
    
    if(row > m_rows)
    {
        std::cout<<__PRETTY_FUNCTION__<<": row is greater than number of rows in matrix!!!!"<<std::endl;
        assert(false);
    }
    if(column > m_columns)
    {
        std::cout<<__PRETTY_FUNCTION__<<": column is greater than number of columns in matrix!!!!"<<std::endl;
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

template <class T> void matrix<T>::transpose()
{
    T* temp = m_data;
    m_data = new T[m_rows * m_columns];
    uint32_t newRows = m_columns;
    uint32_t newColumns = m_rows;

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

#endif //MATRIX_H