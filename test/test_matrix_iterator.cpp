#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixIteratorAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    double memberwise_coeficient = 0.00;
    for (auto i = a_matrix.begin(); i != a_matrix.end(); i++)
        *i = 2.33 * (++memberwise_coeficient);

    memberwise_coeficient = 0.00;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            double value = 2.33 * (++memberwise_coeficient);

            AMATRIX_CHECK_EQUAL(a_matrix(i, j), value);
        }
    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixForEachIteratorAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    double memberwise_coeficient = 0.00;
    for (auto& i : a_matrix)
        i = 2.33 * (++memberwise_coeficient);

    memberwise_coeficient = 0.00;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            double value = 2.33 * (++memberwise_coeficient);
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), value);
        }
    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixIteratorAssign<1, 1>();

    number_of_failed_tests += TestMatrixIteratorAssign<1, 2>();
    number_of_failed_tests += TestMatrixIteratorAssign<2, 1>();
    number_of_failed_tests += TestMatrixIteratorAssign<2, 2>();

    number_of_failed_tests += TestMatrixIteratorAssign<3, 1>();
    number_of_failed_tests += TestMatrixIteratorAssign<3, 2>();
    number_of_failed_tests += TestMatrixIteratorAssign<3, 3>();
    number_of_failed_tests += TestMatrixIteratorAssign<1, 3>();
    number_of_failed_tests += TestMatrixIteratorAssign<2, 3>();
    number_of_failed_tests += TestMatrixIteratorAssign<3, 3>();

    number_of_failed_tests += TestMatrixForEachIteratorAssign<1, 1>();

    number_of_failed_tests += TestMatrixForEachIteratorAssign<1, 2>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<2, 1>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<2, 2>();

    number_of_failed_tests += TestMatrixForEachIteratorAssign<3, 1>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<3, 2>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<3, 3>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<1, 3>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<2, 3>();
    number_of_failed_tests += TestMatrixForEachIteratorAssign<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
