#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list> // to create matrices like {{1,2}, {3,4}}
#include <iostream>

// template for Matrix holding any type (int, double, or any other)
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int rows;
    int cols; 

public:
    // Create a rows x cols matrix filled with init
    Matrix(int r, int c, T init = T());

    // from initializer list: Matrix<double>
    Matrix(std::initializer_list<std::initializer_list<T>> list);

    int numRows() const;
    int numCols() const;
    
    // 1: Allow changing value (m(0,0) = 5)
    T& operator()(int i, int j); 
    const T& operator()(int i, int j) const; 
    
    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> transpose() const;
    
    void print() const;
};

#endif