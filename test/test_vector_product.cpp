#include "matrix.h"
#include "checks.h"

template <std::size_t TSize>
std::size_t TestVectorScalarProduct() {
    AMatrix::Vector<double, TSize> a_vector;
    AMatrix::Vector<double, TSize> b_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
            a_vector[i] = 2.33 * i - 4.52;

    b_vector = 1.3 * a_vector * 0.34;
    b_vector = 2 * b_vector;
    b_vector = b_vector * 1;
    
    for (std::size_t i = 0; i < a_vector.size(); i++)
            AMATRIX_CHECK_EQUAL(b_vector[i], 2 * 1.3 * (2.33 * i - 4.52 ) * 0.34);

    return 0;  // not failed
}

template <std::size_t TSize>
std::size_t TestVectorProduct() {
    // AMatrix::Vector<double, TSize> a_vector;
    // AMatrix::Vector<double, TSize> b_vector;

    // for (std::size_t i = 0; i < a_vector.size(); i++)
    //     a_vector[i] = 2.2;

    // for (std::size_t i = 0; i < b_vector.size1(); i++)
    //         b_vector[i] = 5.1;

    // double result = a_vector * b_vector;

    // AMATRIX_CHECK_EQUAL(result, 5.1*2.2*b_vector.size());

    // std::cout << "OK" << std::endl;
    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;

    // scalar product test
    number_of_failed_tests += TestVectorScalarProduct<1>();
    number_of_failed_tests += TestVectorScalarProduct<2>();
    number_of_failed_tests += TestVectorScalarProduct<3>();
 
    // matrix product test
    number_of_failed_tests += TestVectorProduct<1>();
    number_of_failed_tests += TestVectorProduct<2>();
    number_of_failed_tests += TestVectorProduct<3>();
 
    std::cout << number_of_failed_tests << " tests failed" << std::endl;

    return number_of_failed_tests;
}
