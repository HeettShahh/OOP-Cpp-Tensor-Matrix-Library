#include "Tensor3D.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

// Constructor: dimensions
template <typename T>
Tensor3D<T>::Tensor3D(int d, int r, int c, T init) {
    depth = d; rows = r; cols = c;
    
    // 3D structure
    data.resize(depth);
    for (int k = 0; k < depth; k++) {
        data[k].resize(rows);
        for (int i = 0; i < rows; i++) {
            data[k][i].resize(cols, init); // Make columns and fill with default
        }
    }
}

// Constructor from initializer list
template <typename T>
Tensor3D<T>::Tensor3D(std::initializer_list<std::initializer_list<std::initializer_list<T>>> list) {
    depth = list.size();

    if (depth > 0) {
        // If; have sheets, check size of first sheet
        rows = list.begin()->size();
    } else {
        rows = 0;
    }

    if (rows > 0) {
        // If it has rows, check the size of the first row
        cols = list.begin()->begin()->size();
    } else {
        cols = 0;
    }

    data.resize(depth);
    int k = 0;

    for (auto matrix : list) {
        data[k].resize(rows);
        int i = 0;
        for (auto row : matrix) {
            data[k][i] = row; // Assigned
            i++;
        }
        k++;
    }
}

// Writes access
template <typename T>
T& Tensor3D<T>::operator()(int k, int i, int j) {
    if (k < 0 || k >= depth || i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Tensor3D index out of bounds.");
    }
    return data[k][i][j];
}

// Reads access
template <typename T>
const T& Tensor3D<T>::operator()(int k, int i, int j) const {
    if (k < 0 || k >= depth || i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Tensor3D index out of bounds.");
    }
    return data[k][i][j];
}

// Slicing: takes one and turns it into as Matrix
template <typename T>
Matrix<T> Tensor3D<T>::slice(int k) const {
    // Checks if layer index exists
    if (k < 0 || k >= depth) throw std::out_of_range("Slice index error");
    
    // new Matrix to hold the data
    Matrix<T> result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Copies data
            result(i, j) = data[k][i][j];
        }
    }
    return result;
}

// Tensor addition
template <typename T>
Tensor3D<T> Tensor3D<T>::operator+(const Tensor3D<T>& other) const {
    if (depth != other.depth || rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions mismatch for addition");
    }
    Tensor3D<T> result(depth, rows, cols);
    for (int k = 0; k < depth; k++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(k, i, j) = data[k][i][j] + other(k, i, j);
            }
        }
    }
    return result;
}

// Elementwise Multiplication
template <typename T>
Tensor3D<T> Tensor3D<T>::elemwiseMultiply(const Tensor3D<T>& other) const {
    if (depth != other.depth || rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions mismatch for elementwise multiplication");
    }
    Tensor3D<T> result(depth, rows, cols);
    for (int k = 0; k < depth; k++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(k, i, j) = data[k][i][j] * other(k, i, j);
            }
        }
    }
    return result;
}

// Operator*: Applies a Matrix calculation each slice by Matrix
template <typename T>
Tensor3D<T> Tensor3D<T>::operator*(const Matrix<T>& M) const {
    // Checks if dimensions match for multiplication
    if (cols != M.numRows()) throw std::invalid_argument("Dimension mismatch for Tensor * Matrix");

    int K = M.numCols();
    Tensor3D<T> result(depth, rows, K);

    for (int k = 0; k < depth; k++) {
        Matrix<T> s = this->slice(k);
        Matrix<T> out = s * M;

        // updated answre into the new Tensor structure
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < K; j++) {
                result(k, i, j) = out(i, j);
            }
        }
    }
    return result;
}

// reshape: changes the shape (here, 2x3x4 -> 3x2x4) without deleting data
template <typename T>
void Tensor3D<T>::reshape(int newD, int newR, int newC) {
    // rechecking total number of items - same 
    if (depth * rows * cols != newD * newR * newC) {
        throw std::invalid_argument("Total size must remain constant.");
    }

    // copy everything into one long list
    std::vector<T> flat;
    for (int k = 0; k < depth; k++)
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                flat.push_back(data[k][i][j]);

    // clear old data and make space for new shape
    data.clear();
    data.resize(newD);
    int idx = 0;
    
    for (int k = 0; k < newD; k++) {
        data[k].resize(newR);
        for (int i = 0; i < newR; i++) {
            data[k][i].resize(newC);
            for (int j = 0; j < newC; j++) {
                data[k][i][j] = flat[idx++]; // using data and move index
            }
        }
    }
    depth = newD; rows = newR; cols = newC;
}

// a heelper to print the Tensor by each layerr
template <typename T>
void Tensor3D<T>::print() const {
    for (int k = 0; k < depth; k++) {
        std::cout << "Depth Slice " << k << ":" << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << std::setw(8) << std::setprecision(4) << data[k][i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

// needed for splitting templates into .cpp files
template class Tensor3D<double>;