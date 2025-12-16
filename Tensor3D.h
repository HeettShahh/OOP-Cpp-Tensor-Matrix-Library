#ifndef TENSOR3D_H
#define TENSOR3D_H

#include "Matrix.h"
#include <vector>
#include <initializer_list>

template <typename T>
class Tensor3D {
private:
    // 3D vector (vector inside a vector)
    std::vector<std::vector<std::vector<T>>> data;
    int depth; 
    int rows;  // no. of rows 
    int cols; //  and columns

public:
    // tensor with shape depth x rows x cols
    Tensor3D(int d, int r, int c, T init = T());

    // from nested initializer list
    Tensor3D(std::initializer_list<std::initializer_list<std::initializer_list<T>>> list);

    // allow accessing data at depth, row and column (col)
    T& operator()(int k, int i, int j);
    const T& operator()(int k, int i, int j) const;

    // elementwise (same shapes)
    Tensor3D<T> operator+(const Tensor3D<T>& other) const;
    Tensor3D<T> elemwiseMultiply(const Tensor3D<T>& other) const;

    Tensor3D<T> operator*(const Matrix<T>& M) const;

    // pulls depth slice as Matrix
    Matrix<T> slice(int k) const;

    void reshape(int newD, int newR, int newC); // reshaping    
    void print() const;
};

#endif