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
std::size_t TestMatrixIteratorForwardBackward() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    double memberwise_coeficient = 0.00;

    auto i_value = a_matrix.begin();
    for (; i_value != a_matrix.end(); i_value++)
        *i_value = 2.33 * (++memberwise_coeficient);

    for (int i = a_matrix.size1() - 1; i >= 0; i--)
        for (int j = a_matrix.size2() - 1; j >= 0; j--) {
            i_value--;

            AMATRIX_CHECK_EQUAL(a_matrix(i, j), *i_value);
        }

    for (; i_value != a_matrix.end(); ++i_value)
        *i_value = 1.34 * (++memberwise_coeficient);

    for (int i = a_matrix.size1() - 1; i >= 0; i--)
        for (int j = a_matrix.size2() - 1; j >= 0; j--) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), *(--i_value));
        }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixIteratorArithmetic() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    double memberwise_coeficient = 0.00;

    auto i_value = a_matrix.begin();
    for (; i_value != a_matrix.end(); i_value++)
        *i_value = (++memberwise_coeficient);
    // test -= and +=
    i_value -= a_matrix.size();
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), *i_value);
            i_value += 1;
        }

    for (int i = a_matrix.size1() - 1; i >= 0; i--)
        for (int j = a_matrix.size2() - 1; j >= 0; j--) {
            i_value -= 1;
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), *i_value);
        }

    // test it + n operator
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j),
                *(a_matrix.begin() + (i * a_matrix.size2() + j)));
        }

    // test n + it operator
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j),
                *((i * a_matrix.size2() + j) + a_matrix.begin()));
        }

    // test it - n operator
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j),
                *(a_matrix.end() -
                    (a_matrix.size() - i * a_matrix.size2() - j)));
        }

    // test it1 - it2 operator
    AMATRIX_CHECK_EQUAL(a_matrix.size(), a_matrix.end() - a_matrix.begin());

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixForEachIteratorAssign() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    double memberwise_coeficient = 0.00;

    for (auto& value : a_matrix)
        value = 2.33 * (++memberwise_coeficient);

    memberwise_coeficient = 0.00;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            double value = 2.33 * (++memberwise_coeficient);
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), value);
        }
    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixInequality() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix(AMatrix::ZeroMatrix<double>(TSize1, TSize2));

    for(auto i = a_matrix.begin() ; i != a_matrix.end() ; i++){
        AMATRIX_CHECK(i >= a_matrix.begin());
        AMATRIX_CHECK(i <= a_matrix.end());
    }

    for(auto i = a_matrix.begin() + 1 ; i != a_matrix.end()  ; i++){
        AMATRIX_CHECK(i > a_matrix.begin());
    }

    for(auto i = a_matrix.begin() ; i != a_matrix.end() - 1 ; i++){
        AMATRIX_CHECK(i < a_matrix.end());
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

    number_of_failed_tests += TestMatrixIteratorForwardBackward<1, 1>();

    number_of_failed_tests += TestMatrixIteratorForwardBackward<1, 2>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<2, 1>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<2, 2>();

    number_of_failed_tests += TestMatrixIteratorForwardBackward<3, 1>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<3, 2>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<3, 3>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<1, 3>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<2, 3>();
    number_of_failed_tests += TestMatrixIteratorForwardBackward<3, 3>();

    number_of_failed_tests += TestMatrixIteratorArithmetic<1, 1>();

    number_of_failed_tests += TestMatrixIteratorArithmetic<1, 2>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<2, 1>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<2, 2>();

    number_of_failed_tests += TestMatrixIteratorArithmetic<3, 1>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<3, 2>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<3, 3>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<1, 3>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<2, 3>();
    number_of_failed_tests += TestMatrixIteratorArithmetic<3, 3>();

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

    number_of_failed_tests += TestMatrixInequality<1, 1>();

    number_of_failed_tests += TestMatrixInequality<1, 2>();
    number_of_failed_tests += TestMatrixInequality<2, 1>();
    number_of_failed_tests += TestMatrixInequality<2, 2>();

    number_of_failed_tests += TestMatrixInequality<3, 1>();
    number_of_failed_tests += TestMatrixInequality<3, 2>();
    number_of_failed_tests += TestMatrixInequality<3, 3>();
    number_of_failed_tests += TestMatrixInequality<1, 3>();
    number_of_failed_tests += TestMatrixInequality<2, 3>();
    number_of_failed_tests += TestMatrixInequality<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
