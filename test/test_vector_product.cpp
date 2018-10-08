#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize>
int TestVectorScalarProduct() {
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
int TestVectorScalarSelfProduct() {
    AMatrix::Vector<double, TSize> a_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
            a_vector[i] = 2.33 * i - 4.52;

    a_vector *= 2.4;
    
    for (std::size_t i = 0; i < a_vector.size(); i++)
            AMATRIX_CHECK_EQUAL(a_vector[i], 2.4 * (2.33 * i - 4.52 ));

    return 0;  // not failed
}

template <std::size_t TSize>
int TestVectorProduct() {
    AMatrix::Vector<double, TSize> a_vector;
    AMatrix::Vector<double, TSize> b_vector;

    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = i+1.00;

    for (std::size_t i = 0; i < b_vector.size1(); i++)
            b_vector[i] = 5.1;

    double result = a_vector.dot(b_vector);

    auto n = b_vector.size();

    AMATRIX_CHECK_EQUAL(result, 5.1*int(n*(n+1)/2));

    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

template <std::size_t TSize1, std::size_t TSize2>
int TestVectorOuterProduct() {
    AMatrix::Vector<double, TSize1> a_vector;
    AMatrix::Vector<double, TSize2> b_vector;

    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = i+1.00;

    for (std::size_t i = 0; i < b_vector.size(); i++)
            b_vector[i] = 5.1 * i;

    auto result = OuterProduct(a_vector, b_vector);

    auto n = b_vector.size();

    AMATRIX_CHECK_EQUAL(result.size1(), TSize1);
    AMATRIX_CHECK_EQUAL(result.size2(), TSize2);

    for(std::size_t i = 0 ; i < result.size1() ; i++)
        for(std::size_t j = 0 ; j < result.size2() ; j++)
            AMATRIX_CHECK_EQUAL(result(i,j), (i+1)*(5.1*j));


    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    // scalar product test
    number_of_failed_tests += TestVectorScalarProduct<1>();
    number_of_failed_tests += TestVectorScalarProduct<2>();
    number_of_failed_tests += TestVectorScalarProduct<3>();
 
    // scalar product test
    number_of_failed_tests += TestVectorScalarSelfProduct<1>();
    number_of_failed_tests += TestVectorScalarSelfProduct<2>();
    number_of_failed_tests += TestVectorScalarSelfProduct<3>();
 
    // vector product test
    number_of_failed_tests += TestVectorProduct<1>();
    number_of_failed_tests += TestVectorProduct<2>();
    number_of_failed_tests += TestVectorProduct<3>();

    number_of_failed_tests += TestVectorOuterProduct<1, 1>();

    number_of_failed_tests += TestVectorOuterProduct<1, 2>();
    number_of_failed_tests += TestVectorOuterProduct<2, 1>();
    number_of_failed_tests += TestVectorOuterProduct<2, 2>();

    number_of_failed_tests += TestVectorOuterProduct<3, 1>();
    number_of_failed_tests += TestVectorOuterProduct<3, 2>();
    number_of_failed_tests += TestVectorOuterProduct<3, 3>();
    number_of_failed_tests += TestVectorOuterProduct<1, 3>();
    number_of_failed_tests += TestVectorOuterProduct<2, 3>();
    number_of_failed_tests += TestVectorOuterProduct<3, 3>();
 
    std::cout << number_of_failed_tests << " tests failed" << std::endl;

    return number_of_failed_tests;
}
