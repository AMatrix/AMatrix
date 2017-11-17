#include <iostream>

#include "matrix.h"
#include "checks.h"

std::size_t TestDynamicMatrixAcess(std::size_t Size1, std::size_t Size2) {
    AMatrix::Matrix<double, 0, 0> a_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix(i, j) = 2.33 * i - 4.52 * j;

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.33 * i - 4.52 * j);
        }
    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestDynamicMatrixAcess(1, 1);

    number_of_failed_tests += TestDynamicMatrixAcess(1,2);
    number_of_failed_tests += TestDynamicMatrixAcess(2,1);
    number_of_failed_tests += TestDynamicMatrixAcess(2,2);

    number_of_failed_tests += TestDynamicMatrixAcess(3,1);
    number_of_failed_tests += TestDynamicMatrixAcess(3,2);
    number_of_failed_tests += TestDynamicMatrixAcess(3,3);
    number_of_failed_tests += TestDynamicMatrixAcess(1,3);
    number_of_failed_tests += TestDynamicMatrixAcess(2,3);
    number_of_failed_tests += TestDynamicMatrixAcess(3,3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
