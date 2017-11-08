#include <iostream>

#include "matrix.h"
#include "checks.h"

template <std::size_t NumberOfRows, std::size_t NumberOfCulomns>
int TestMatrixScalarProduct() {
    AMatrix::Matrix<double, NumberOfRows, NumberOfCulomns> a_matrix;
    AMatrix::Matrix<double, NumberOfRows, NumberOfCulomns> b_matrix;
    for (int i = 0; i < a_matrix.size1(); i++)
        for (int j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    b_matrix = 1.3 * a_matrix * 0.34;
    b_matrix = 2 * b_matrix;

    for (int i = 0; i < a_matrix.size1(); i++)
        for (int j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(b_matrix(i, j), 2 * 1.3 * (2.33 * i - 4.52 * j) * 0.34);

    return 0;  // not failed
}

template <std::size_t NumberOfRows, std::size_t NumberOfCulomns,
    std::size_t NumberOfSecondRows>
int TestMatrixProduct() {
    std::cout << "Testing A(" << NumberOfRows << "," << NumberOfCulomns
              << ") X B(" << NumberOfCulomns << "," << NumberOfSecondRows
              << ") ";
    AMatrix::Matrix<double, NumberOfRows, NumberOfCulomns> a_matrix;
    AMatrix::Matrix<double, NumberOfCulomns, NumberOfSecondRows> b_matrix;
    AMatrix::Matrix<double, NumberOfRows, NumberOfSecondRows> c_matrix;
    for (int i = 0; i < a_matrix.size1(); i++)
        for (int j = 0; j < a_matrix.size2(); j++)
            if (i == j)
                a_matrix(i, j) = 2.33 * (i + 1);
            else
                a_matrix(i, j) = 0.00;

    for (int i = 0; i < b_matrix.size1(); i++)
        for (int j = 0; j < b_matrix.size2(); j++)
            b_matrix(i, j) = i + j + 1;

    c_matrix = a_matrix * b_matrix;

    for (int i = 0; i < c_matrix.size1(); i++)
        for (int j = 0; j < c_matrix.size2(); j++)
            if (static_cast<std::size_t>(i) < NumberOfCulomns)
                AMATRIX_CHECK_EQUAL(
                    c_matrix(i, j), b_matrix(i, j) * (i + 1) * 2.33);

    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    // scalar product test
    number_of_failed_tests += TestMatrixScalarProduct<1, 1>();

    number_of_failed_tests += TestMatrixScalarProduct<1, 2>();
    number_of_failed_tests += TestMatrixScalarProduct<2, 1>();
    number_of_failed_tests += TestMatrixScalarProduct<2, 2>();

    number_of_failed_tests += TestMatrixScalarProduct<3, 1>();
    number_of_failed_tests += TestMatrixScalarProduct<3, 2>();
    number_of_failed_tests += TestMatrixScalarProduct<3, 3>();
    number_of_failed_tests += TestMatrixScalarProduct<1, 3>();
    number_of_failed_tests += TestMatrixScalarProduct<2, 3>();
    number_of_failed_tests += TestMatrixScalarProduct<3, 3>();

    // matrix product test
    number_of_failed_tests += TestMatrixProduct<1, 1, 1>();

    number_of_failed_tests += TestMatrixProduct<1, 1, 2>();
    number_of_failed_tests += TestMatrixProduct<2, 1, 1>();
    number_of_failed_tests += TestMatrixProduct<2, 1, 2>();

    number_of_failed_tests += TestMatrixProduct<3, 1, 1>();
    number_of_failed_tests += TestMatrixProduct<3, 1, 2>();
    number_of_failed_tests += TestMatrixProduct<3, 1, 3>();
    number_of_failed_tests += TestMatrixProduct<1, 1, 3>();
    number_of_failed_tests += TestMatrixProduct<2, 1, 3>();
    number_of_failed_tests += TestMatrixProduct<3, 1, 3>();

    number_of_failed_tests += TestMatrixProduct<1, 2, 1>();

    number_of_failed_tests += TestMatrixProduct<1, 2, 2>();
    number_of_failed_tests += TestMatrixProduct<2, 2, 1>();
    number_of_failed_tests += TestMatrixProduct<2, 2, 2>();

    number_of_failed_tests += TestMatrixProduct<3, 2, 1>();
    number_of_failed_tests += TestMatrixProduct<3, 2, 2>();
    number_of_failed_tests += TestMatrixProduct<3, 2, 3>();
    number_of_failed_tests += TestMatrixProduct<1, 2, 3>();
    number_of_failed_tests += TestMatrixProduct<2, 2, 3>();
    number_of_failed_tests += TestMatrixProduct<3, 2, 3>();

    number_of_failed_tests += TestMatrixProduct<1, 3, 1>();

    number_of_failed_tests += TestMatrixProduct<1, 3, 2>();
    number_of_failed_tests += TestMatrixProduct<2, 3, 1>();
    number_of_failed_tests += TestMatrixProduct<2, 3, 2>();

    number_of_failed_tests += TestMatrixProduct<3, 3, 1>();
    number_of_failed_tests += TestMatrixProduct<3, 3, 2>();
    number_of_failed_tests += TestMatrixProduct<3, 3, 3>();
    number_of_failed_tests += TestMatrixProduct<1, 3, 3>();
    number_of_failed_tests += TestMatrixProduct<2, 3, 3>();
    number_of_failed_tests += TestMatrixProduct<3, 3, 3>();

    std::cout << number_of_failed_tests << " tests failed" << std::endl;

    return number_of_failed_tests;
}
