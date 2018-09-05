#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestSubMatrixAcess() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    std::size_t sub_size1 = (TSize1 > 1) ? TSize1 - 1 : 1;
    std::size_t sub_size2 = (TSize2 > 1) ? TSize2 - 1 : 1;

    std::size_t sub_index1 = (TSize1 > 1) ? 1 : 0;
    std::size_t sub_index2 = (TSize2 > 1) ? 1 : 0;

    AMatrix::SubMatrix<AMatrix::Matrix<double, TSize1, TSize2>> sub_matrix(
        a_matrix, sub_index1, sub_index2, sub_size1, sub_size2);

    AMATRIX_CHECK_EQUAL(sub_matrix.size(), sub_size1 * sub_size2);
    AMATRIX_CHECK_EQUAL(sub_matrix.size1(), sub_size1);
    AMATRIX_CHECK_EQUAL(sub_matrix.size2(), sub_size2);

    for (std::size_t i = 0; i < sub_matrix.size1(); i++)
        for (std::size_t j = 0; j < sub_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(
                sub_matrix(i, j), a_matrix(i + sub_index1, j + sub_index2));
        }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestSubMatrixAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix(
        AMatrix::ZeroMatrix<double>(TSize1, TSize2));

    std::size_t sub_size1 = (TSize1 > 1) ? TSize1 - 1 : 1;
    std::size_t sub_size2 = (TSize2 > 1) ? TSize2 - 1 : 1;

    std::size_t sub_index1 = (TSize1 > 1) ? 1 : 0;
    std::size_t sub_index2 = (TSize2 > 1) ? 1 : 0;

    AMatrix::SubMatrix<AMatrix::Matrix<double, TSize1, TSize2>> sub_matrix(
        a_matrix, sub_index1, sub_index2, sub_size1, sub_size2);

    AMATRIX_CHECK_EQUAL(sub_matrix.size1(), sub_size1);
    AMATRIX_CHECK_EQUAL(sub_matrix.size2(), sub_size2);

    for (std::size_t i = 0; i < sub_matrix.size1(); i++)
        for (std::size_t j = 0; j < sub_matrix.size2(); j++) {
            sub_matrix(i, j) = 2.33 * i - 4.52 * j;
        }

    for (std::size_t i = sub_index1; i < a_matrix.size1(); i++)
        for (std::size_t j = sub_index2; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j),
                2.33 * (i - sub_index1) - 4.52 * (j - sub_index2));
        }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestSubMatrixExpressionAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix(
        AMatrix::ZeroMatrix<double>(TSize1, TSize2));

    std::size_t sub_size1 = (TSize1 > 1) ? TSize1 - 1 : 1;
    std::size_t sub_size2 = (TSize2 > 1) ? TSize2 - 1 : 1;

    std::size_t sub_index1 = (TSize1 > 1) ? 1 : 0;
    std::size_t sub_index2 = (TSize2 > 1) ? 1 : 0;

    AMatrix::SubMatrix<AMatrix::Matrix<double, TSize1, TSize2>> sub_matrix(
        a_matrix, sub_index1, sub_index2, sub_size1, sub_size2);

    AMATRIX_CHECK_EQUAL(sub_matrix.size1(), sub_size1);
    AMATRIX_CHECK_EQUAL(sub_matrix.size2(), sub_size2);

     AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(
        sub_size1, sub_size2);
    for (std::size_t i = 0; i < sub_matrix.size1(); i++)
        for (std::size_t j = 0; j < sub_matrix.size2(); j++) {
            b_matrix(i, j) = 2.33 * i - 4.52 * j;
        }

	sub_matrix = 2.00 * b_matrix + b_matrix;

    for (std::size_t i = sub_index1; i < a_matrix.size1(); i++)
        for (std::size_t j = sub_index2; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j),
                3.00 * (2.33 * (i - sub_index1) - 4.52 * (j - sub_index2)));
        }

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;

    number_of_failed_tests += TestSubMatrixAcess<1, 1>();

    number_of_failed_tests += TestSubMatrixAcess<1, 2>();
    number_of_failed_tests += TestSubMatrixAcess<2, 1>();
    number_of_failed_tests += TestSubMatrixAcess<2, 2>();

    number_of_failed_tests += TestSubMatrixAcess<3, 1>();
    number_of_failed_tests += TestSubMatrixAcess<3, 2>();
    number_of_failed_tests += TestSubMatrixAcess<3, 3>();
    number_of_failed_tests += TestSubMatrixAcess<1, 3>();
    number_of_failed_tests += TestSubMatrixAcess<2, 3>();
    number_of_failed_tests += TestSubMatrixAcess<3, 3>();

    number_of_failed_tests += TestSubMatrixAssign<1, 1>();

    number_of_failed_tests += TestSubMatrixAssign<1, 2>();
    number_of_failed_tests += TestSubMatrixAssign<2, 1>();
    number_of_failed_tests += TestSubMatrixAssign<2, 2>();

    number_of_failed_tests += TestSubMatrixAssign<3, 1>();
    number_of_failed_tests += TestSubMatrixAssign<3, 2>();
    number_of_failed_tests += TestSubMatrixAssign<3, 3>();
    number_of_failed_tests += TestSubMatrixAssign<1, 3>();
    number_of_failed_tests += TestSubMatrixAssign<2, 3>();
    number_of_failed_tests += TestSubMatrixAssign<3, 3>();

    number_of_failed_tests += TestSubMatrixExpressionAssign<1, 1>();
							  
    number_of_failed_tests += TestSubMatrixExpressionAssign<1, 2>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<2, 1>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<2, 2>();
							  
    number_of_failed_tests += TestSubMatrixExpressionAssign<3, 1>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<3, 2>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<3, 3>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<1, 3>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<2, 3>();
    number_of_failed_tests += TestSubMatrixExpressionAssign<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
