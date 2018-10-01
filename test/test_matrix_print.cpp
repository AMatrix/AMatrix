#include <sstream>
#include <string>
#include "amatrix.h"
#include "checks.h"

int TestMatrixPrint() {
    AMatrix::Matrix<double, 3, 3> a_matrix;

    for (size_t i = 0; i < 9; i++) {
        a_matrix[i] = static_cast<double>(i * i);
    }

    std::stringstream string_stream;

    string_stream << a_matrix;

    std::string actual = string_stream.str();
    std::string expected = "[[ 0,  1,  4],\n [ 9, 16, 25],\n [36, 49, 64]]";

    AMATRIX_CHECK_EQUAL(actual, expected);

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixPrint();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
