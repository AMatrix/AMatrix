#include "matrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixInitializeToZero() {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(
        AMatrix::ZeroMatrix<double>(TSize1, TSize2));

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 0.00);

    return 0;  // not failed
}

std::size_t TestMatrixInitialize1() {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix{1.2};

    AMATRIX_CHECK_EQUAL(a_matrix.size1(), 1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), 1);
    AMATRIX_CHECK_EQUAL(a_matrix(0, 0), 1.2);

    return 0;  // not failed
}

std::size_t TestMatrixInitialize2() {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix{1.2, 2.3};

    AMATRIX_CHECK_EQUAL(a_matrix.size1(), 1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), 2);
    AMATRIX_CHECK_EQUAL(a_matrix(0, 0), 1.2);
    AMATRIX_CHECK_EQUAL(a_matrix(0, 1), 2.3);

    return 0;  // not failed
}

std::size_t TestMatrixInitialize3() {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix{ 1.2, 2.3, 3.4 };

    AMATRIX_CHECK_EQUAL(a_matrix.size1(), 1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), 3);
    AMATRIX_CHECK_EQUAL(a_matrix(0, 0), 1.2);
    AMATRIX_CHECK_EQUAL(a_matrix(0, 1), 2.3);
    AMATRIX_CHECK_EQUAL(a_matrix(0, 2), 3.4);

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixInitializeToZero<1, 1>();

    number_of_failed_tests += TestMatrixInitializeToZero<1, 2>();
    number_of_failed_tests += TestMatrixInitializeToZero<2, 1>();
    number_of_failed_tests += TestMatrixInitializeToZero<2, 2>();

    number_of_failed_tests += TestMatrixInitializeToZero<3, 1>();
    number_of_failed_tests += TestMatrixInitializeToZero<3, 2>();
    number_of_failed_tests += TestMatrixInitializeToZero<3, 3>();
    number_of_failed_tests += TestMatrixInitializeToZero<1, 3>();
    number_of_failed_tests += TestMatrixInitializeToZero<2, 3>();
    number_of_failed_tests += TestMatrixInitializeToZero<3, 3>();

    number_of_failed_tests += TestMatrixInitialize1();
    number_of_failed_tests += TestMatrixInitialize2();
    number_of_failed_tests += TestMatrixInitialize3();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
