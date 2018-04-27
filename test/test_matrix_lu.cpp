#include "amatrix.h"
#include "checks.h"

std::size_t TestMatrixLUDeterminant3() {
    AMatrix::Matrix<double, 3, 3> a_matrix;

    double value = 0.00;
    for(auto& i_value : a_matrix)
        i_value = value++;

    a_matrix(2,2) = 0.00;

    // double* A[3];
    
    // value = 0;
    // for(int i = 0 ; i < 3 ; i++){
    //     A[i] = new double[3];
    //     for(int j = 0 ; j < 3 ; j++)
    //         A[i][j] = value++;
    // }

    // int P[4];
    
    // LUPDecompose(A,3,1e-12,P);

    AMatrix::Matrix<double, 3, 3> U{6,7,8,0,1,2,0,0,0};
    AMatrix::Matrix<double, 3, 3> L{1,0,0,0,1,0,0.5,0.5,1};

    AMatrix::Matrix<double, 3, 3> LU (L * U);

    std::cout << LU << std::endl;

    AMatrix::Matrix<double, 3, 3> result_matrix{3,4,5,
                                               0,1,2,
                                               0,0,-8};
    // for(int i = 0 ; i < 3 ; i++){
    //     for(int j = 0 ; j < 3 ; j++)
    //         a_matrix(i,j) = A[i][j];
    //     delete A[i];
    // }

   AMatrix::LUFactorization< AMatrix::Matrix<double, 3, 3>, AMatrix::Vector<std::size_t, AMatrix::dynamic> > lu_factorization(a_matrix);

    
    AMATRIX_CHECK_EQUAL(lu_factorization.Determinant(), 24);
    
    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestMatrixLUDeterminant3();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
