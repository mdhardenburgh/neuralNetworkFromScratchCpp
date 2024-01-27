#ifndef MATRIX
#define MATRIX

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

    m_data.resize(m_rows);
    for(uint32_t iter = 0; iter < m_data.size(); iter++)
    {
        m_data.at(iter).resize(m_columns);
    }

    //if MxN matrix (rows x columns)
    if((m_rows > 1)&&(m_columns > 1))
    {
        for(uint32_t iIter = 0; iIter < m_rows; iIter++)
        {
            for(uint32_t jIter = 0; jIter < m_columns; jIter++)
            {
                (m_data)[iIter][jIter] = data[iIter][jIter];
            }
        }
    }

    // Mx1 matrix 
    if((m_rows > 1)&&(m_columns == 1))
    {
        for(uint32_t iIter = 0; iIter < m_rows; iIter++)
        {
            for(uint32_t jIter = 0; jIter < m_columns; jIter++)
            {
                (m_data)[iIter][jIter] = reinterpret_cast<T*>(data)[iIter];
            }
        }
    }

    // 1XN matrix
    if((m_rows == 1)&&(m_columns > 1))
    {
        for(uint32_t iIter = 0; iIter < m_rows; iIter++)
        {
            for(uint32_t jIter = 0; jIter < m_columns; jIter++)
            {
                (m_data)[iIter][jIter] = reinterpret_cast<T*>(data)[jIter];
            }
        }
    }
}

template <class T> matrix<T>::~matrix()
{
    //delete m_data;
}

template <class T> T matrix<T>::at(const uint32_t& row, const uint32_t& column)
{
    return (m_data)[row][column];
}

template <class T> void matrix<T>::transpose()
{
    std::vector<std::vector<T>> temp = m_data;
    uint32_t newRows = m_columns;
    uint32_t newColumns = m_rows;

    m_data.resize(newRows);
    for(uint32_t iIter = 0; iIter < m_data.size(); iIter++)
    {
        m_data.at(iIter).resize(newColumns);
    }

    for(uint32_t iIter = 0; iIter < m_rows; iIter++)
    {
        for(uint32_t jIter = 0; jIter < m_columns; jIter++)
        {
            (m_data)[iIter][jIter] = temp[jIter][iIter];
        }
    }

    m_rows = newRows;
    m_columns = newColumns;

}

#endif //MATRIX