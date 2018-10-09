#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize>
int TestVectorNorm() {
    AMatrix::Vector<double, TSize> a_vector;
    double results[] = {0, 1, 5, 14, 30, 55, 91, 140, 204, 285};

    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = i + 1.00;

    AMATRIX_CHECK_EQUAL(a_vector.norm(), std::sqrt(results[TSize]));
    AMATRIX_CHECK_EQUAL(a_vector.squared_norm(), results[TSize]);

    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

template <std::size_t TSize>
int TestVectorNormalize() {
    AMatrix::Vector<double, TSize> a_vector;

    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = i + 1;

    a_vector.normalize();

    AMATRIX_CHECK_EQUAL(a_vector.norm(), 1.00);
    AMATRIX_CHECK_EQUAL(a_vector.squared_norm(), 1.00);

    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    // norm test
    number_of_failed_tests += TestVectorNorm<1>();
    number_of_failed_tests += TestVectorNorm<2>();
    number_of_failed_tests += TestVectorNorm<3>();

    std::cout << number_of_failed_tests << " tests failed" << std::endl;

    return number_of_failed_tests;
}
