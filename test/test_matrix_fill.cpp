#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize1, std::size_t TSize2>
int TestFillZero() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix.fill(0.00);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 0.00);

    return 0;  // not failed
}

template <std::size_t TSize>
int TestFillIdentity() {
    AMatrix::Matrix<double, TSize, TSize> a_matrix;
    a_matrix.fill_identity();

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            if (i == j) {
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 1.00);
            } else {
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 0.00);
            }
		}
		
    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestFillScalar() {
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    a_matrix.fill(1.23);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 1.23);

    return 0;  // not failed
}


int main() {
    int number_of_failed_tests = 0;
    number_of_failed_tests += TestFillZero<1, 1>();

    number_of_failed_tests += TestFillZero<1, 2>();
    number_of_failed_tests += TestFillZero<2, 1>();
    number_of_failed_tests += TestFillZero<2, 2>();

    number_of_failed_tests += TestFillZero<3, 1>();
    number_of_failed_tests += TestFillZero<3, 2>();
    number_of_failed_tests += TestFillZero<3, 3>();
    number_of_failed_tests += TestFillZero<1, 3>();
    number_of_failed_tests += TestFillZero<2, 3>();
    number_of_failed_tests += TestFillZero<3, 3>();

    number_of_failed_tests += TestFillIdentity<1>();
    number_of_failed_tests += TestFillIdentity<2>();
    number_of_failed_tests += TestFillIdentity<3>();

    number_of_failed_tests += TestFillScalar<1, 1>();

    number_of_failed_tests += TestFillScalar<1, 2>();
    number_of_failed_tests += TestFillScalar<2, 1>();
    number_of_failed_tests += TestFillScalar<2, 2>();

    number_of_failed_tests += TestFillScalar<3, 1>();
    number_of_failed_tests += TestFillScalar<3, 2>();
    number_of_failed_tests += TestFillScalar<3, 3>();
    number_of_failed_tests += TestFillScalar<1, 3>();
    number_of_failed_tests += TestFillScalar<2, 3>();
    number_of_failed_tests += TestFillScalar<3, 3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
