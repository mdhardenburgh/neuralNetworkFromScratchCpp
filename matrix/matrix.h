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

        T at(const uint32_t& index);
        void transpose();
        //matrix add(matrix B);
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

template <class T> T matrix<T>::at(const uint32_t& index)
{
    return m_data[index];
}

template <class T> void matrix<T>::transpose()
{
    T* temp = m_data;
    m_data = new T[m_rows * m_columns];
    uint32_t newRows = m_columns;
    uint32_t newColumns = m_rows;

    for(uint32_t iIter = 0; iIter < m_rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < m_columns; jIter++)
        {
            m_data[iIter + (jIter * m_columns)] = temp[jIter + (iIter * m_rows)];
        }       
    }

    m_rows = newRows;
    m_columns = newColumns;
    delete temp;
}

#endif //MATRIX_H