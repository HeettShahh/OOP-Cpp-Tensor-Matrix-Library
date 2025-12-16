# C++ Tensor & Matrix Library

A custom C++17 linear algebra library designed to handle **Matrix** and **3D Tensor** operations. This project implements core mathematical structures from scratch, supporting template-based data types, dynamic resizing, and advanced tensor-matrix multiplications.

## Features

### Matrix Operations
* **Core Math:** Addition `+`, Multiplication `*`, Transpose.
* **Accessors:** Read/Write access via `(row, col)` operator overloading.
* **Validation:** Error handling for dimension mismatches and out-of-bounds access.

### 3D Tensor Operations
* **Structure:** Represents data as `Depth x Rows x Cols`.
* **Tensor Math:** Element-wise addition and multiplication.
* **Tensor-Matrix Product:** Multiplies every depth slice by a 2D Matrix.
* **Utilities:** Slicing (extract 2D plane from 3D), Reshaping (change dimensions while preserving data), and formatted printing.

### Technical Implementation
* **Templates:** Written with C++ templates (`template <typename T>`) to support various data types (currently instantiated for `double`).
* **Memory Management:** Utilizes `std::vector` for dynamic storage and memory safety.
* **Error Handling:** Robust `try-catch` blocks using `std::invalid_argument` and `std::out_of_range`.

---

## Getting Started

### Prerequisites
* A C++ compiler supporting **C++17** (e.g., `clang++`, `g++`, or MSVC).

### Compilation & Running

This project includes two main entry points: a demo application (`main.cpp`) and a unit test suite (`test.cpp`).

#### 1. Running the Main Demo
The main application demonstrates randomized matrix operations, financial portfolio simulations (Tensor representation), and reshaping logic.

```bash
# Compile
clang++ Matrix.cpp Tensor3D.cpp main.cpp -o main_app -std=c++17

# Run
./main_app
