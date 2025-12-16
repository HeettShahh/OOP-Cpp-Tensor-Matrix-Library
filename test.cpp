#include "Matrix.h"
#include "Tensor3D.h"
#include <iostream>
using namespace std;

void check(bool pass, const string& msg) {
    if (pass)
        cout << "[PASS] " << msg << endl;
    else
        cout << "[FAIL] " << msg << endl;
}

int main() {

    cout << "\n--Test 1: Matrix Addition--\n";
    Matrix<double> A = {{1,2},{3,4}};
    Matrix<double> B = {{5,6},{7,8}};
    Matrix<double> C = A + B;
    check(C(0,0) == 6 && C(1,1) == 12, "Matrix addition correct");

    cout << "\n--Test 2: Matrix Multiplication--\n";
    Matrix<double> D = A * B;
    check(D(0,0) == 19 && D(1,1) == 50, "Matrix multiplication correct");

    cout << "\n--Test 3: Matrix Transpose--\n";
    Matrix<double> T = A.transpose();
    check(T(1,0) == 2 && T(0,1) == 3, "Matrix transpose correct");

    cout << "\n--Test 4: Tensor Slice--\n";
    Tensor3D<double> T3 = {
        { {1,2}, {3,4} },
        { {5,6}, {7,8} }
    };
    Matrix<double> s0 = T3.slice(0);
    check(s0(1,1) == 4, "Slice from tensor correct");

    cout << "\n--Test 5: Tensor Addition--\n";
    Tensor3D<double> Tadd = T3 + T3;
    check(Tadd(1,1,1) == 16, "Tensor addition correct");

    cout << "\n--Test 6: Elementwise Multiply--\n";
    Tensor3D<double> Tmul = T3.elemwiseMultiply(T3);
    check(Tmul(0,1,0) == 9, "Elementwise multiplication correct");

    cout << "\n=--Test 7: Tensor x Matrix--\n";
    Matrix<double> W = {{1},{1}}; // sum two columns
    Tensor3D<double> Tout = T3 * W;
    check(Tout(0,0,0) == 3, "Tensor * Matrix first slice correct");

    cout << "\n--Test 8: Reshape--\n";
    Tensor3D<double> R(1,2,2); 
    R(0,0,0) = 1; R(0,0,1) = 2; 
    R(0,1,0) = 3; R(0,1,1) = 4;

    R.reshape(2,1,2);
    check(R(1,0,1) == 4, "Reshape keeps values in order");

    cout << "\n--Test 9: Error Handling--\n";
    try {
        Matrix<double> wrong(3,3);
        Matrix<double> wrong2 = A + wrong;
        check(false, "Error not thrown when expected");
    } catch (...) {
        check(true, "Error thrown correctly for invalid addition");
    }

    cout << "\n----All Tests Completed----\n";
    return 0;
}