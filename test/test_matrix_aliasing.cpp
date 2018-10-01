#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestMatrixCheckAliasing() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix = AMatrix::ZeroMatrix<double>(TSize1, TSize2);

    AMatrix::Matrix<double, TSize1, TSize2> b_matrix;
    b_matrix = a_matrix;

	// Note: without this print the optimizer will take out a_matrix and b_matrix allocation resuting in test failure
    std::cout << "Check overlapping of a_matrix.data() " << a_matrix.data()
              << " and b_matrix.data() " << b_matrix.data() << std::endl;

    AMATRIX_CHECK(a_matrix.check_aliasing(
        a_matrix.data(), a_matrix.data() + a_matrix.size()));


    AMATRIX_CHECK_EQUAL(b_matrix.check_aliasing(
                            a_matrix.data(), a_matrix.data() + a_matrix.size()),
        false);
    AMATRIX_CHECK_EQUAL(a_matrix.check_aliasing(
                            b_matrix.data(), b_matrix.data() + b_matrix.size()),
        false);

    for (std::size_t i = 1; i < a_matrix.size(); i++) {
            auto begin = a_matrix.data() - a_matrix.size() + i;
        AMATRIX_CHECK(a_matrix.check_aliasing(begin, begin + a_matrix.size()));
        }
    AMATRIX_CHECK(a_matrix.check_aliasing(
        a_matrix.data() - 1, a_matrix.data() + a_matrix.size()));

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
std::size_t TestTransposeCheckAliasing() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix = AMatrix::ZeroMatrix<double>(TSize1, TSize2);

    AMatrix::Matrix<double, TSize1, TSize2> b_matrix;
    b_matrix = a_matrix;

	// Note: without this print the optimizer will take out a_matrix and b_matrix allocation resuting in test failure
    std::cout << "Check overlapping of a_matrix.data() " << a_matrix.data()
              << " and b_matrix.data() " << b_matrix.data() << std::endl;

    AMATRIX_CHECK(a_matrix.transpose().check_aliasing(
        a_matrix.data(), a_matrix.data() + a_matrix.size()));

    AMATRIX_CHECK_EQUAL(b_matrix.transpose().check_aliasing(
                            a_matrix.data(), a_matrix.data() + a_matrix.size()),
        false);
    AMATRIX_CHECK_EQUAL(a_matrix.transpose().check_aliasing(
                            b_matrix.data(), b_matrix.data() + b_matrix.size()),
        false);

    for (std::size_t i = 1; i < a_matrix.size(); i++) {
        auto begin = a_matrix.data() - a_matrix.size() + i;
        AMATRIX_CHECK(
            a_matrix.transpose().check_aliasing(begin, begin + a_matrix.size()));
    }
    AMATRIX_CHECK(a_matrix.transpose().check_aliasing(
        a_matrix.data() - 1, a_matrix.data() + a_matrix.size()));

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixCheckAliasing<1, 1>();

    number_of_failed_tests += TestMatrixCheckAliasing<1, 2>();
    number_of_failed_tests += TestMatrixCheckAliasing<2, 1>();
    number_of_failed_tests += TestMatrixCheckAliasing<2, 2>();

    number_of_failed_tests += TestMatrixCheckAliasing<3, 1>();
    number_of_failed_tests += TestMatrixCheckAliasing<3, 2>();
    number_of_failed_tests += TestMatrixCheckAliasing<3, 3>();
    number_of_failed_tests += TestMatrixCheckAliasing<1, 3>();
    number_of_failed_tests += TestMatrixCheckAliasing<2, 3>();
    number_of_failed_tests += TestMatrixCheckAliasing<3, 3>();

    number_of_failed_tests += TestTransposeCheckAliasing<1, 1>();
								  
    number_of_failed_tests += TestTransposeCheckAliasing<1, 2>();
    number_of_failed_tests += TestTransposeCheckAliasing<2, 1>();
    number_of_failed_tests += TestTransposeCheckAliasing<2, 2>();
								  
    number_of_failed_tests += TestTransposeCheckAliasing<3, 1>();
    number_of_failed_tests += TestTransposeCheckAliasing<3, 2>();
    number_of_failed_tests += TestTransposeCheckAliasing<3, 3>();
    number_of_failed_tests += TestTransposeCheckAliasing<1, 3>();
    number_of_failed_tests += TestTransposeCheckAliasing<2, 3>();
    number_of_failed_tests += TestTransposeCheckAliasing<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
