#include <iostream>

#include "matrix.h"
#include "checks.h"

template <typename TMatrixType>
std::size_t TestThisMatrixAcess(TMatrixType& ThisMatrix) {
    for (std::size_t i = 0; i < ThisMatrix.size1(); i++)
        for (std::size_t j = 0; j < ThisMatrix.size2(); j++)
            ThisMatrix(i, j) = 2.33 * i - 4.52 * j;

    for (std::size_t i = 0; i < ThisMatrix.size1(); i++)
        for (std::size_t j = 0; j < ThisMatrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(ThisMatrix(i, j), 2.33 * i - 4.52 * j);
        }
    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixAcess() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    AMatrix::Matrix<double, 0, 0> a_dynamic_matrix(TSize1, TSize2);
    return TestThisMatrixAcess(a_matrix) +
           TestThisMatrixAcess(a_dynamic_matrix);
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixAcess<1, 1>();

    number_of_failed_tests += TestMatrixAcess<1, 2>();
    number_of_failed_tests += TestMatrixAcess<2, 1>();
    number_of_failed_tests += TestMatrixAcess<2, 2>();

    number_of_failed_tests += TestMatrixAcess<3, 1>();
    number_of_failed_tests += TestMatrixAcess<3, 2>();
    number_of_failed_tests += TestMatrixAcess<3, 3>();
    number_of_failed_tests += TestMatrixAcess<1, 3>();
    number_of_failed_tests += TestMatrixAcess<2, 3>();
    number_of_failed_tests += TestMatrixAcess<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
