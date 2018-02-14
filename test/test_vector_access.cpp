#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize>
std::size_t TestVectorAcess() {
    AMatrix::Vector<double, TSize> a_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
            a_vector[i] = 2.33 * i;

    for (std::size_t i = 0; i < a_vector.size(); i++)
            AMATRIX_CHECK_EQUAL( a_vector[i], 2.33 * i);
    
    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestVectorAcess<1>();
    number_of_failed_tests += TestVectorAcess<2>();
    number_of_failed_tests += TestVectorAcess<3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
