#include "amatrix.h"
#include "checks.h"

std::size_t TestMatrixMinus(std::size_t Size1, std::size_t Size2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> c_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    b_matrix = a_matrix;
    c_matrix = a_matrix - b_matrix;

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(c_matrix(i, j), 0.00);

    return 0;  // not failed
}

std::size_t TestMatrixMinusEqual(std::size_t Size1, std::size_t Size2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    b_matrix = a_matrix;
    a_matrix -= b_matrix;

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 0.00);

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
 	number_of_failed_tests += TestMatrixMinus(1,1);

	number_of_failed_tests += TestMatrixMinus(1,2);
	number_of_failed_tests += TestMatrixMinus(2,1);
	number_of_failed_tests += TestMatrixMinus(2,2);

	number_of_failed_tests += TestMatrixMinus(3,1);
	number_of_failed_tests += TestMatrixMinus(3,2);
	number_of_failed_tests += TestMatrixMinus(3,3);
	number_of_failed_tests += TestMatrixMinus(1,3);
	number_of_failed_tests += TestMatrixMinus(2,3);
	number_of_failed_tests += TestMatrixMinus(3,3);

 	number_of_failed_tests += TestMatrixMinusEqual(1,1);

	number_of_failed_tests += TestMatrixMinusEqual(1,2);
	number_of_failed_tests += TestMatrixMinusEqual(2,1);
	number_of_failed_tests += TestMatrixMinusEqual(2,2);

	number_of_failed_tests += TestMatrixMinusEqual(3,1);
	number_of_failed_tests += TestMatrixMinusEqual(3,2);
	number_of_failed_tests += TestMatrixMinusEqual(3,3);
	number_of_failed_tests += TestMatrixMinusEqual(1,3);
	number_of_failed_tests += TestMatrixMinusEqual(2,3);
	number_of_failed_tests += TestMatrixMinusEqual(3,3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
