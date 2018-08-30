#include "amatrix.h"
#include "checks.h"
#include <limits>

std::size_t TestMatrixLUDeterminant3() {
    AMatrix::Matrix<double, 3, 3> a_matrix;

    double value = 0.00;
    for(auto& i_value : a_matrix)
        i_value = value++;

    a_matrix(2,2) = 9.00;

   AMatrix::LUFactorization< AMatrix::Matrix<double, 3, 3>, AMatrix::Vector<std::size_t, AMatrix::dynamic> > lu_factorization(a_matrix);

    AMATRIX_CHECK_EQUAL(lu_factorization.determinant(), -3.00);
    
    return 0;  // not failed
}

std::size_t TestMatrixLUInverse3() {
    AMatrix::Matrix<double, 3, 3> a_matrix;
    AMatrix::Matrix<double, 3, 3> correct_result{
        -1. / 3., -5. / 3., 1., -1., 4., -2., 1., -2., 1.};

    double value = 0.00;
    for (auto& i_value : a_matrix)
        i_value = value++;

    a_matrix(2, 2) = 9.00;

    AMatrix::LUFactorization<AMatrix::Matrix<double, 3, 3>,
        AMatrix::Vector<std::size_t, AMatrix::dynamic> >
        lu_factorization(a_matrix);
    auto a_inverse = lu_factorization.inverse();

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            AMATRIX_CHECK_ALMOST_EQUAL(a_inverse(i, j), correct_result(i, j));

    return 0;  // not failed
}


std::size_t TestMatrixLUISolve3() {
    AMatrix::Matrix<double, 3, 3> a_matrix;
    AMatrix::Matrix<double, 3, 1> b{3., -6., 0.};
    AMatrix::Matrix<double, 3, 1> correct_result{9., -27., 15.};

    double value = 0.00;
    for (auto& i_value : a_matrix)
        i_value = value++;

    a_matrix(2, 2) = 9.00;

    AMatrix::LUFactorization<AMatrix::Matrix<double, 3, 3>,
        AMatrix::Vector<std::size_t, AMatrix::dynamic> >
        lu_factorization(a_matrix);
 
	auto x = lu_factorization.solve(b);
 
	for (std::size_t i = 0; i < a_matrix.size1(); i++)
        AMATRIX_CHECK_ALMOST_EQUAL(x[i], correct_result[i]);

    return 0;  // not failed
}

std::size_t TestMatrixLUISolveNoPermutation3() {
    AMatrix::Matrix<double, 3, 3> a_matrix{6.,7.,9.
										  ,0.,1.,2.
										  ,3.,4.,5.};
    AMatrix::Matrix<double, 3, 1> b{0., 3., -6};
    AMatrix::Matrix<double, 3, 1> correct_result{9., -27., 15.};

    AMatrix::LUFactorization<AMatrix::Matrix<double, 3, 3>,
        AMatrix::Vector<std::size_t, AMatrix::dynamic> >
        lu_factorization(a_matrix);

    auto x = lu_factorization.solve(b);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        AMATRIX_CHECK_ALMOST_EQUAL(x[i], correct_result[i]);

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixLUDeterminant3();
    number_of_failed_tests += TestMatrixLUInverse3();
    number_of_failed_tests += TestMatrixLUISolveNoPermutation3();
    number_of_failed_tests += TestMatrixLUISolve3();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
