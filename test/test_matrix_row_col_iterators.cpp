#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixRowExpressionIterator() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        AMatrix::MatrixRow<AMatrix::Matrix<double, TSize1, TSize2>> a_row_i =
            a_matrix.row(i);

        std::size_t j = 0;
        for ( auto row_iterator = a_row_i.begin(); row_iterator < a_row_i.end(); ++row_iterator)
            *row_iterator = 2.33 * i - 4.52 * j++;
    }

    for (std::size_t i = 0; i < a_matrix.size1(); i++) {
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.33 * i - 4.52 * j);
        }
    }

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    number_of_failed_tests += TestMatrixRowExpressionIterator<1, 1>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<1, 2>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<2, 1>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<2, 2>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<3, 1>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<3, 2>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<3, 3>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<1, 3>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<2, 3>();
    number_of_failed_tests += TestMatrixRowExpressionIterator<3, 3>();

    return number_of_failed_tests;
}