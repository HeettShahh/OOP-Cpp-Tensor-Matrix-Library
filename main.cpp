#include "Matrix.h"   
#include "Tensor3D.h" 
#include <iostream>   
#include <cstdlib> // For rand()
#include <ctime>

// for clean output
void print_L() {
    std::cout << "- - - - - - - - - - - - - - - -" << std::endl;
}

int main() {
    //random generator
    std::srand(std::time(0));

    try {

        // Pt 1: Matrix Opt (Randomized)
        print_L();
        std::cout << "Part 1: Matrix Operations (Random)" << std::endl;
        print_L();

        int size = 2;
        Matrix<double> A(size, size); 
        Matrix<double> B(size, size);

        // Fill with random number betn(1-10)
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                A(i, j) = (std::rand() % 10) + 1;
                B(i, j) = (std::rand() % 10) + 1;
            }
        }

        std::cout << "Matrix A (Random):" << std::endl; A.print();
        std::cout << "\nMatrix B (Random):" << std::endl; B.print();

        Matrix<double> C = A + B; 
        std::cout << "\n(A+B):" << std::endl; C.print();

        Matrix<double> D = A * B; 
        std::cout << "\n(A*B):" << std::endl; D.print();

        std::cout << "\nTranspose of A:" << std::endl;
        Matrix<double> TA = A.transpose();
        std::cout << "Result of A:" << std::endl; TA.print();

        // Pt 2: Randomized Portfolio
       print_L();
        std::cout << "Part 2: Tensor x Matrix (Random Data)" << std::endl;
        print_L();

        int stocks = 2; // depth
        int days = 3; //rows
        int feat = 4; //columns
        Tensor3D<double> portfolio(stocks, days, feat);

        //Fill with random stock prices (between 50 and 150)
        for (int k = 0; k < stocks; k++) { // < 2
            for (int i = 0; i < days; i++) { // < 3
                for (int j = 0; j < feat; j++) { // < 4
                    // Random price
                    portfolio(k, i, j) = 50 + (std::rand() % 100);
                }
            }
        }
        std::cout << "Portfolio (random):" << std::endl;
        portfolio.print();

        // Weights - here i have used OHLC (Open, high ,low,close)
        Matrix<double> weights = { 
            {0.0, 0.0},   // Open
            {0.5, 1.0},   // High
            {0.5, -1.0},  // Low
            {0.0, 0.0}    // Close
        };
        std::cout << "Weights Matrix:" << std::endl;
        weights.print();

        double high = portfolio(0, 0, 1); // 1 is high
        double low  = portfolio(0, 0, 2); // 2 is low
        double expected_avg = (high + low) / 2.0 ; //avg
        double expected_vol = high - low; // high - low ==== difference (volatility)

        std::cout << "\n--Verification Logic--" << std::endl;
        std::cout << "Input High: " << high << ", Input Low: " << low << std::endl;
        std::cout << "Expected Typical price (avg.): " << expected_avg << std::endl;
        std::cout << "Expected fluctuation (range): " << expected_vol << std::endl;

        // Run actual Tensor Opt
        Tensor3D<double> result = portfolio * weights;
        std::cout << "\nProgram Result (Depth 0, Row 0):" << std::endl;
        result.print();


        // Pt 3: Tensor Addition + Elementwise Multiplication
        print_L();
        std::cout << "Part 3: Tensor Addition & Elementwise Multiplication" << std::endl;
        print_L();

        // Create two small tensor (2x2x2) for testing
        Tensor3D<double> T1 = {
            { {1, 2}, {3, 4} },   // depth slice 0
            { {5, 6}, {7, 8} }    // depth slice 1
        };
        Tensor3D<double> T2 = {
            { {10, 20}, {30, 40} },
            { {2, 3}, {4, 5} }
        };

        std::cout << "Tensor T1:" << std::endl; T1.print();
        std::cout << "Tensor T2:" << std::endl; T2.print();

        // Test: Addition
        Tensor3D<double> T_add = T1 + T2;
        std::cout << "T1 + T2 (Elementwise Addition):" << std::endl;
        T_add.print();

        // Test: Elementwise Multiplication
        Tensor3D<double> T_mul = T1.elemwiseMultiply(T2);
        std::cout << "T1 .* T2 (Elementwise Multiplication):" << std::endl;
        T_mul.print();


        // Pt 4: Extra
        print_L();
        std::cout << "Part 4: Reshaping and Error catching" << std::endl;
        print_L();

        std::cout << "Reshaping Tensor from (2,3,4) to (3,2,4)..." << std::endl;
        portfolio.reshape(3, 2, 4); //reshaping
        portfolio.print();

        //error handling
        std::cout << "\nTesting invalid addition (2x2 + 3x3)..." << std::endl;
        try {
            Matrix<double> m1(2, 2); // 2x2 matrix
            Matrix<double> m2(3, 3); // 3x3
            Matrix<double> m_fail = m1 + m2; 
        } catch (const std::exception& e) {
            std::cout << "Caught Error -> " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0; 
}