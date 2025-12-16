#include "Matrix.h"
#include <stdexcept> // throw errors if something goes wrong
#include <iomanip>   // aligment

// Constructor 1: Initialize the matrix with specific dimensions
template <typename T>
Matrix<T>::Matrix(int r, int c, T init) {
    rows = r;
    cols = c; 
    
    data.resize(rows);

    // Go through each row and make it 'cols'
    for (int i = 0; i < rows; i++) {
        data[i].resize(cols, init);
    }
}

// Constructor from initializer
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    rows = list.size(); // number of items in list is row count

    if (rows == 0) {
        cols = 0;
        data.resize(0);
        return; 
    } else {
        cols = list.begin()->size();
        data.resize(rows); // Make space for all the rows
    }

    int i = 0;
    for (auto row : list) {
        // Safety check: make sure every row is the same length
        if (row.size() != cols) {
            throw std::invalid_argument("All rows must have the same length.");
        }
        
        data[i] = row;
        i++;
    }
}

//---//

// getter to return the row count
template <typename T>
int Matrix<T>::numRows() const { 
    return rows; 
}

// same for columns counts
template <typename T>
int Matrix<T>::numCols() const { 
    return cols; 
}

//---//


// Operator(): writes data like m(0,0) = 5
template <typename T>
T& Matrix<T>::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds.");
    }
    return data[i][j]; 
}

// Operator(): reads data even if the matrix is read-only
template <typename T>
const T& Matrix<T>::operator()(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds.");
    }
    return data[i][j];
}

//Adds this matrix to another one
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions must match for addition.");
    }

    Matrix<T> result(rows, cols); // Make a new matrix for the answer
    // Loop through every single one
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Adds
            result(i, j) = data[i][j] + other(i, j);
        }
    }
    return result;
}

// Multiplies this matrix by another one
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    // columns must match the other matrix's rows
    if (cols != other.rows) {
        throw std::invalid_argument("Invalid dimensions for multiplication.");
    }

    int K = other.cols;
    Matrix<T> result(rows, K); // result matrix (starts at 0)

    // Standard loop for matrix multiplication
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < cols; k++) {
                result(i, j) += data[i][k] * other(k, j); // mutliplies
            }
        }
    }
    return result;
}

// Transpose: Swaps the rows and columns
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols, rows); // flipped dimensions
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Take value at (i,j) and put it at (j,i)
            result(j, i) = data[i][j]; 
        }
    }
    return result;
}

// Print: Shows the matrix nicely on the screen
template <typename T>
void Matrix<T>::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(8) << std::setprecision(4) << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// for splitting from .h header file and to work with double
template class Matrix<double>;