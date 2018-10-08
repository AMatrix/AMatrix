#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixScalarSelfDivision() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    a_matrix /= 2.3;
    
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), (2.33 * i - 4.52 * j) / 2.3);

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixScalarDivision() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    auto b_matrix = a_matrix / 2.3;
    
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(b_matrix(i, j), (2.33 * i - 4.52 * j) / 2.3);

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    // scalar self product test
    number_of_failed_tests += TestMatrixScalarSelfDivision<1, 1>();

    number_of_failed_tests += TestMatrixScalarSelfDivision<1, 2>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<2, 1>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<2, 2>();

    number_of_failed_tests += TestMatrixScalarSelfDivision<3, 1>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<3, 2>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<3, 3>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<1, 3>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<2, 3>();
    number_of_failed_tests += TestMatrixScalarSelfDivision<3, 3>();

    number_of_failed_tests += TestMatrixScalarDivision<1, 1>();

    number_of_failed_tests += TestMatrixScalarDivision<1, 2>();
    number_of_failed_tests += TestMatrixScalarDivision<2, 1>();
    number_of_failed_tests += TestMatrixScalarDivision<2, 2>();

    number_of_failed_tests += TestMatrixScalarDivision<3, 1>();
    number_of_failed_tests += TestMatrixScalarDivision<3, 2>();
    number_of_failed_tests += TestMatrixScalarDivision<3, 3>();
    number_of_failed_tests += TestMatrixScalarDivision<1, 3>();
    number_of_failed_tests += TestMatrixScalarDivision<2, 3>();
    number_of_failed_tests += TestMatrixScalarDivision<3, 3>();

     std::cout << number_of_failed_tests << " tests failed" << std::endl;

    return number_of_failed_tests;
}
