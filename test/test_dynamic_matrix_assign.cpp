#include "matrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestZeroMatrixAssign() {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(TSize1, TSize2);
    a_matrix = AMatrix::ZeroMatrix<double>(TSize1, TSize2);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 0.00);

    return 0;  // not failed
}

std::size_t TestMatrixAssign(std::size_t Size1, std::size_t Size2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    b_matrix = a_matrix;

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(b_matrix(i, j), 2.33 * i - 4.52 * j);

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestZeroMatrixAssign<1, 1>();

    number_of_failed_tests += TestZeroMatrixAssign<1, 2>();
    number_of_failed_tests += TestZeroMatrixAssign<2, 1>();
    number_of_failed_tests += TestZeroMatrixAssign<2, 2>();

    number_of_failed_tests += TestZeroMatrixAssign<3, 1>();
    number_of_failed_tests += TestZeroMatrixAssign<3, 2>();
    number_of_failed_tests += TestZeroMatrixAssign<3, 3>();
    number_of_failed_tests += TestZeroMatrixAssign<1, 3>();
    number_of_failed_tests += TestZeroMatrixAssign<2, 3>();
    number_of_failed_tests += TestZeroMatrixAssign<3, 3>();

    number_of_failed_tests += TestMatrixAssign(1, 1);

    number_of_failed_tests += TestMatrixAssign(1, 2);
    number_of_failed_tests += TestMatrixAssign(2, 1);
    number_of_failed_tests += TestMatrixAssign(2, 2);

    number_of_failed_tests += TestMatrixAssign(3, 1);
    number_of_failed_tests += TestMatrixAssign(3, 2);
    number_of_failed_tests += TestMatrixAssign(3, 3);
    number_of_failed_tests += TestMatrixAssign(1, 3);
    number_of_failed_tests += TestMatrixAssign(2, 3);
    number_of_failed_tests += TestMatrixAssign(3, 3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
