#include "matrix.h"
#include "checks.h"

template <std::size_t TSize>
std::size_t TestVectorInitializeToZero() {
    const AMatrix::ZeroVector<double> zero_vector(TSize);
    AMatrix::Vector<double, TSize> a_vector(zero_vector);

    for (std::size_t i = 0; i < a_vector.size(); i++)
            AMATRIX_CHECK_EQUAL(a_vector[i], 0.00);

    return 0;  // not failed
}

std::size_t TestVectorInitialize1() {
    AMatrix::Vector<double, 1> a_vector{1.2};

    AMATRIX_CHECK_EQUAL(a_vector[0], 1.2);

    return 0;  // not failed
}

std::size_t TestVectorInitialize2() {
    AMatrix::Vector<double, 2> a_vector{1.2, 2.3};

    AMATRIX_CHECK_EQUAL(a_vector[0], 1.2);
    AMATRIX_CHECK_EQUAL(a_vector[1], 2.3);

    return 0;  // not failed
}

std::size_t TestVectorInitialize3() {
    AMatrix::Vector<double, 3> a_vector{1.2, 2.3, 3.4};

    AMATRIX_CHECK_EQUAL(a_vector[0], 1.2);
    AMATRIX_CHECK_EQUAL(a_vector[1], 2.3);
    AMATRIX_CHECK_EQUAL(a_vector(2, 0), 3.4);

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestVectorInitializeToZero<1>();
    number_of_failed_tests += TestVectorInitializeToZero<2>();
    number_of_failed_tests += TestVectorInitializeToZero<3>();

    number_of_failed_tests += TestVectorInitialize1();
    number_of_failed_tests += TestVectorInitialize2();
    number_of_failed_tests += TestVectorInitialize3();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
