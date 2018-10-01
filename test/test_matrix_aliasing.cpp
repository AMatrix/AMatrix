#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixCheckAliasing() {
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
int TestTransposeCheckAliasing() {
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

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixRowCheckAliasing() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix = AMatrix::ZeroMatrix<double>(TSize1, TSize2);

    AMatrix::Matrix<double, TSize1, TSize2> b_matrix;
    b_matrix = a_matrix;

    // Note: without this print the optimizer will take out a_matrix and b_matrix allocation resuting in test failure
    std::cout << "Check overlapping of a_matrix.data() " << a_matrix.data()
              << " and b_matrix.data() " << b_matrix.data() << std::endl;

	for (std::size_t i = 1; i < a_matrix.size(); i++) {
        AMATRIX_CHECK(a_matrix.row(i).check_aliasing(
            a_matrix.data(), a_matrix.data() + a_matrix.size()));

        AMATRIX_CHECK_EQUAL(b_matrix.row(i).check_aliasing(a_matrix.data(),
                                a_matrix.data() + a_matrix.size()),
            false);
        AMATRIX_CHECK_EQUAL(a_matrix.row(i).check_aliasing(b_matrix.data(),
                                b_matrix.data() + b_matrix.size()),
            false);
    }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestMatrixColumnCheckAliasing() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix = AMatrix::ZeroMatrix<double>(TSize1, TSize2);

    AMatrix::Matrix<double, TSize1, TSize2> b_matrix;
    b_matrix = a_matrix;

    // Note: without this print the optimizer will take out a_matrix and b_matrix allocation resuting in test failure
    std::cout << "Check overlapping of a_matrix.data() " << a_matrix.data()
              << " and b_matrix.data() " << b_matrix.data() << std::endl;

    for (std::size_t i = 1; i < a_matrix.size(); i++) {
        AMATRIX_CHECK(a_matrix.column(i).check_aliasing(
            a_matrix.data(), a_matrix.data() + a_matrix.size()));

        AMATRIX_CHECK_EQUAL(b_matrix.column(i).check_aliasing(a_matrix.data(),
                                a_matrix.data() + a_matrix.size()),
            false);
        AMATRIX_CHECK_EQUAL(a_matrix.column(i).check_aliasing(b_matrix.data(),
                                b_matrix.data() + b_matrix.size()),
            false);
    }

    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestSubMatrixCheckAliasing() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix = AMatrix::ZeroMatrix<double>(TSize1, TSize2);
    AMatrix::Matrix<double, TSize1, TSize2> b_matrix;
    b_matrix = a_matrix;


    std::size_t sub_size1 = (TSize1 > 1) ? TSize1 - 1 : 1;
    std::size_t sub_size2 = (TSize2 > 1) ? TSize2 - 1 : 1;

    std::size_t sub_index1 = (TSize1 > 1) ? 1 : 0;
    std::size_t sub_index2 = (TSize2 > 1) ? 1 : 0;

    AMatrix::SubMatrix<AMatrix::Matrix<double, TSize1, TSize2>> sub_matrix(
        a_matrix, sub_index1, sub_index2, sub_size1, sub_size2);

    // Note: without this print the optimizer will take out a_matrix and b_matrix allocation resuting in test failure
    std::cout << "Check overlapping of a_matrix.data() " << a_matrix.data()
              << " and b_matrix.data() " << b_matrix.data() << std::endl;

	for (std::size_t i = 1; i < a_matrix.size(); i++) {
        AMATRIX_CHECK(sub_matrix.check_aliasing(
            a_matrix.data(), a_matrix.data() + a_matrix.size()));

        AMATRIX_CHECK_EQUAL(sub_matrix.check_aliasing(b_matrix.data(),
                                b_matrix.data() + b_matrix.size()),
            false);
    }

    return 0;  // not failed
}

template <std::size_t TSize>
int TestSubVectorCheckAliasing() {
    AMatrix::Vector<double, TSize> a_vector(
        AMatrix::ZeroMatrix<double>(TSize, 1));
    AMatrix::Vector<double, TSize> b_vector(
        AMatrix::ZeroMatrix<double>(TSize, 1));

    std::size_t sub_size = (TSize > 1) ? TSize - 1 : 1;
    std::size_t sub_index = (TSize > 1) ? 1 : 0;

    AMatrix::SubVector<AMatrix::Vector<double, TSize>> sub_vector(
        a_vector, sub_index, sub_size);

    // Note: without this print the optimizer will take out a_matrix and b_matrix allocation resuting in test failure
    std::cout << "Check overlapping of a_vector.data() " << a_vector.data()
              << " and b_vector.data() " << b_vector.data() << std::endl;

    for (std::size_t i = 1; i < a_vector.size(); i++) {
        AMATRIX_CHECK(sub_vector.check_aliasing(
            a_vector.data(), a_vector.data() + a_vector.size()));

        AMATRIX_CHECK_EQUAL(sub_vector.check_aliasing(b_vector.data(),
                                b_vector.data() + b_vector.size()),
            false);
    }

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;
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

    number_of_failed_tests += TestMatrixRowCheckAliasing<1, 1>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<1, 2>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<2, 1>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<2, 2>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<3, 1>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<3, 2>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<3, 3>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<1, 3>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<2, 3>();
    number_of_failed_tests += TestMatrixRowCheckAliasing<3, 3>();

    number_of_failed_tests += TestMatrixColumnCheckAliasing<1, 1>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<1, 2>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<2, 1>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<2, 2>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<3, 1>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<3, 2>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<3, 3>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<1, 3>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<2, 3>();
    number_of_failed_tests += TestMatrixColumnCheckAliasing<3, 3>();

    number_of_failed_tests += TestSubMatrixCheckAliasing<1, 1>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<1, 2>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<2, 1>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<2, 2>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<3, 1>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<3, 2>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<3, 3>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<1, 3>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<2, 3>();
    number_of_failed_tests += TestSubMatrixCheckAliasing<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
