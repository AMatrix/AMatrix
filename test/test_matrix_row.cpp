#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixRowAcess() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_row_i(0, j), a_matrix(i, j));
            AMATRIX_CHECK_EQUAL(a_row_i[j], a_matrix(i, j));
        }
    }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixRowAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        AMATRIX_CHECK_EQUAL(a_row_i.size(), TSize2);
        AMATRIX_CHECK_EQUAL(a_row_i.size1(), 1);
        AMATRIX_CHECK_EQUAL(a_row_i.size2(), TSize2);
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_row_i[j] = 2.33 * i - 4.52 * j;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.33 * i - 4.52 * j);
        }
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        AMATRIX_CHECK_EQUAL(a_row_i.size(), TSize2);
        AMATRIX_CHECK_EQUAL(a_row_i.size1(), 1);
        AMATRIX_CHECK_EQUAL(a_row_i.size2(), TSize2);
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_row_i(0, j) = 1.33 * i - 2.52 * j;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 1.33 * i - 2.52 * j);
        }

        return 0;  // not failed
    }
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixRowExpressionAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        AMatrix::Matrix<double, 1, TSize2> b_vector;
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            b_vector[j] = 2.33 * i - 4.52 * j;
        a_row_i = b_vector * 1.5 + b_vector;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i(
            a_matrix, i);
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.5 * ( 2.33 * i - 4.52 * j));
        }
    }

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;

    number_of_failed_tests += TestMatrixRowAcess<1, 1>();
    number_of_failed_tests += TestMatrixRowAcess<1, 2>();
    number_of_failed_tests += TestMatrixRowAcess<2, 1>();
    number_of_failed_tests += TestMatrixRowAcess<2, 2>();
    number_of_failed_tests += TestMatrixRowAcess<3, 1>();
    number_of_failed_tests += TestMatrixRowAcess<3, 2>();
    number_of_failed_tests += TestMatrixRowAcess<3, 3>();
    number_of_failed_tests += TestMatrixRowAcess<1, 3>();
    number_of_failed_tests += TestMatrixRowAcess<2, 3>();
    number_of_failed_tests += TestMatrixRowAcess<3, 3>();

    number_of_failed_tests += TestMatrixRowAssign<1, 1>();
    number_of_failed_tests += TestMatrixRowAssign<1, 2>();
    number_of_failed_tests += TestMatrixRowAssign<2, 1>();
    number_of_failed_tests += TestMatrixRowAssign<2, 2>();
    number_of_failed_tests += TestMatrixRowAssign<3, 1>();
    number_of_failed_tests += TestMatrixRowAssign<3, 2>();
    number_of_failed_tests += TestMatrixRowAssign<3, 3>();
    number_of_failed_tests += TestMatrixRowAssign<1, 3>();
    number_of_failed_tests += TestMatrixRowAssign<2, 3>();
    number_of_failed_tests += TestMatrixRowAssign<3, 3>();

    number_of_failed_tests += TestMatrixRowExpressionAssign<1, 1>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<1, 2>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<2, 1>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<2, 2>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<3, 1>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<3, 2>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<3, 3>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<1, 3>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<2, 3>();
    number_of_failed_tests += TestMatrixRowExpressionAssign<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
