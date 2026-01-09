# Buchberger's Algorithm Implementation

A C++ implementation of **Buchberger's Algorithm** for computing the reduced Gröbner Basis of a polynomial ideal. This project demonstrates the intersection of computational algebraic geometry and object-oriented software design.

## Features

* **Multivariate Polynomial Arithmetic:** Supports addition, subtraction, and multiplication of polynomials in Rational Numbers.
* **Monomial Orderings:** Implements flexible term orderings required for Gröbner basis computations:
    * Lexicographic Order (LEX)
    * Graded Lexicographic Order (GRADED_LEX)
    * Graded Reverse Lexicographic Order (GREVLEX)
* **Buchberger's Algorithm:** Full implementation including:
    * S-Polynomial computation
    * Multivariate polynomial division
    * Basis minimization and reduction

## Usage

### Prerequisites
* A C++ compiler supporting C++14 or later (clang++ or g++).
* Make.

### Build and Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/YOUR_USERNAME/buchbergers-algorithm.git](https://github.com/YOUR_USERNAME/buchbergers-algorithm.git)
    cd buchbergers-algorithm
    ```

2.  **Compile:**
    ```bash
    make
    ```

3.  **Run:**
    ```bash
    ./main
    ```

## Project Structure

* `Polynomial.{hpp,cpp}`: Defines the `Term` and `Polynomial` classes and arithmetic operators.
* `Buchbergers.{hpp,cpp}`: Implements the algorithmic core (`solve`, `find_s_poly`, `reduce_poly`).
* `main.cpp`: Test suite and entry point.

## Author
Alperen Buğra Başar
Undergraduate Student, Computer Science & Mathematics
Bilkent University
