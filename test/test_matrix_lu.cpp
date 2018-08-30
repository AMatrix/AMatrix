#include "amatrix.h"
#include "checks.h"
#include <limits>

std::size_t TestMatrixLUDeterminant3() {
    AMatrix::Matrix<double, 3, 3> a_matrix;

    double value = 0.00;
    for(auto& i_value : a_matrix)
        i_value = value++;

    a_matrix(2,2) = 0.00;

   AMatrix::LUFactorization< AMatrix::Matrix<double, 3, 3>, AMatrix::Vector<std::size_t, AMatrix::dynamic> > lu_factorization(a_matrix);

    AMATRIX_CHECK_EQUAL(lu_factorization.determinant(), 24);
    
    return 0;  // not failed
}

std::size_t TestMatrixLUInvert3() {
    AMatrix::Matrix<double, 3, 3> a_matrix;
    AMatrix::Matrix<double, 3, 3> a_inverse;
    AMatrix::Matrix<double, 3, 3> correct_result{-35./24., 7./12., -1./8., 
                                                 5./4., -1./2., 1./4., 
                                                 -1./8., 1./4., -1./8};

    double value = 0.00;
    for(auto& i_value : a_matrix)
        i_value = value++;

    a_matrix(2,2) = 0.00;

    AMatrix::LUFactorization< AMatrix::Matrix<double, 3, 3>, AMatrix::Vector<std::size_t, AMatrix::dynamic> > lu_factorization(a_matrix);
    lu_factorization.invert(a_inverse);

    std::cout << a_inverse << std::endl;
    std::cout << correct_result << std::endl;

    
    for(std::size_t i = 0 ; i < a_matrix.size1() ; i++)
        for(std::size_t j = 0 ; j < a_matrix.size2() ; j++)
            AMATRIX_CHECK_ALMOST_EQUAL(a_inverse(i,j), correct_result(i,j));
    
    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixLUDeterminant3();
    number_of_failed_tests += TestMatrixLUInvert3();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
