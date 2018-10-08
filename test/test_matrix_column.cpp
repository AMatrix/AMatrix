#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixColumnAcess() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
    }

    for (std::size_t j = 0; j < a_matrix.size2(); j++) {
        const AMatrix::MatrixColumn<AMatrix::Matrix<double, TSize1, TSize2>> a_column_j = a_matrix.column(j);

        for (std::size_t i = 0; i < a_matrix.size1(); i++) {
            AMATRIX_CHECK_EQUAL(a_column_j(i, 0), a_matrix(i, j));
            AMATRIX_CHECK_EQUAL(a_column_j[i], a_matrix(i, j));
        }
    }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixColumnAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t j = 0; j < a_matrix.size2(); j++) {
        AMatrix::MatrixColumn<AMatrix::Matrix<double, TSize1, TSize2>> a_column_j = a_matrix.column(j);
        AMATRIX_CHECK_EQUAL(a_column_j.size(), TSize1);
        AMATRIX_CHECK_EQUAL(a_column_j.size1(), TSize1);
        AMATRIX_CHECK_EQUAL(a_column_j.size2(), 1);
        for (std::size_t i = 0; i < a_matrix.size1(); i++)
            a_column_j[i] = 2.33 * i - 4.52 * j;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.33 * i - 4.52 * j);
        }
    }

    for (std::size_t j = 0; j < a_matrix.size2(); j++) {
        AMatrix::MatrixColumn<AMatrix::Matrix<double, TSize1, TSize2>>
            a_column_j = a_matrix.column(j);
        AMATRIX_CHECK_EQUAL(a_column_j.size(), TSize1);
        AMATRIX_CHECK_EQUAL(a_column_j.size1(), TSize1);
        AMATRIX_CHECK_EQUAL(a_column_j.size2(), 1);
        for (std::size_t i = 0; i < a_matrix.size1(); i++)
            a_column_j(i, 0) = 1.33 * i - 2.52 * j;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 1.33 * i - 2.52 * j);
        }
    }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixColumnExpressionAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t j = 0; j < a_matrix.size2(); j++) {
        AMatrix::MatrixColumn<AMatrix::Matrix<double, TSize1, TSize2>> a_column_j = a_matrix.column(j);
        AMatrix::Matrix<double, 1, TSize1> b_vector;
        for (std::size_t i = 0; i < a_matrix.size1(); i++)
            b_vector[i] = 2.33 * i - 4.52 * j;
        a_column_j = b_vector * 1.5 + b_vector;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.5 * ( 2.33 * i - 4.52 * j));
        }
    }

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    number_of_failed_tests += TestMatrixColumnAcess<1, 1>();
    number_of_failed_tests += TestMatrixColumnAcess<1, 2>();
    number_of_failed_tests += TestMatrixColumnAcess<2, 1>();
    number_of_failed_tests += TestMatrixColumnAcess<2, 2>();
    number_of_failed_tests += TestMatrixColumnAcess<3, 1>();
    number_of_failed_tests += TestMatrixColumnAcess<3, 2>();
    number_of_failed_tests += TestMatrixColumnAcess<3, 3>();
    number_of_failed_tests += TestMatrixColumnAcess<1, 3>();
    number_of_failed_tests += TestMatrixColumnAcess<2, 3>();
    number_of_failed_tests += TestMatrixColumnAcess<3, 3>();

    number_of_failed_tests += TestMatrixColumnAssign<1, 1>();
    number_of_failed_tests += TestMatrixColumnAssign<1, 2>();
    number_of_failed_tests += TestMatrixColumnAssign<2, 1>();
    number_of_failed_tests += TestMatrixColumnAssign<2, 2>();
    number_of_failed_tests += TestMatrixColumnAssign<3, 1>();
    number_of_failed_tests += TestMatrixColumnAssign<3, 2>();
    number_of_failed_tests += TestMatrixColumnAssign<3, 3>();
    number_of_failed_tests += TestMatrixColumnAssign<1, 3>();
    number_of_failed_tests += TestMatrixColumnAssign<2, 3>();
    number_of_failed_tests += TestMatrixColumnAssign<3, 3>();

    number_of_failed_tests += TestMatrixColumnExpressionAssign<1, 1>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<1, 2>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<2, 1>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<2, 2>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<3, 1>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<3, 2>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<3, 3>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<1, 3>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<2, 3>();
    number_of_failed_tests += TestMatrixColumnExpressionAssign<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
