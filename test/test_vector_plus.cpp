#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize>
std::size_t TestVectorPlus() {
    AMatrix::Vector<double, TSize> a_vector;
    AMatrix::Vector<double, TSize> b_vector;
    AMatrix::Vector<double, TSize> c_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
            a_vector[i] = 2.33 * i - 4.52;

    b_vector = a_vector;
    c_vector = a_vector + b_vector;

    for (std::size_t i = 0; i < a_vector.size(); i++)
            AMATRIX_CHECK_EQUAL(c_vector[i], 2.00 * (2.33 * i - 4.52));

    return 0;  // not failed
}

template <std::size_t TSize>
std::size_t TestMatrixPlusEqual() {
    AMatrix::Vector<double, TSize> a_vector;
    AMatrix::Vector<double, TSize> b_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
            a_vector[i] = 2.33 * i - 4.52;

    b_vector = a_vector;
    a_vector += b_vector;

    for (std::size_t i = 0; i < a_vector.size(); i++)
            AMATRIX_CHECK_EQUAL(a_vector[i], 2.00 * (2.33 * i - 4.52));

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestVectorPlus<1>();
    number_of_failed_tests += TestVectorPlus<2>();
    number_of_failed_tests += TestVectorPlus<3>();

    number_of_failed_tests += TestMatrixPlusEqual<1>();
    number_of_failed_tests += TestMatrixPlusEqual<2>();
    number_of_failed_tests += TestMatrixPlusEqual<3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
