#include "amatrix.h"
#include "checks.h"

int TestCSRMatrixProduct(std::size_t Size1, std::size_t Size2) {
    std::cout << "Testing A(" << Size1 << "," << Size2
              << ") X B(" << Size2 << ") ";
    AMatrix::SparseMatrix<AMatrix::CSRMatrixStorage<double>> a_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            a_matrix.insert(i, j, 2.1 * i );
    AMatrix::Matrix<double, AMatrix::dynamic, 1> b_vector(Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, 1> c_vector(Size1);

	b_vector.fill(4.50);
    AMatrix::Product(a_matrix, b_vector, c_vector);

    for (std::size_t i = 0; i < c_vector.size1(); i++)
        AMATRIX_CHECK_EQUAL(c_vector[i], i * 2.1 * Size2 * 4.5);

    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    number_of_failed_tests += TestCSRMatrixProduct(1,1);
							  
    number_of_failed_tests += TestCSRMatrixProduct(1,2);
    number_of_failed_tests += TestCSRMatrixProduct(2,1);
    number_of_failed_tests += TestCSRMatrixProduct(2,2);
							  
    number_of_failed_tests += TestCSRMatrixProduct(3,1);
    number_of_failed_tests += TestCSRMatrixProduct(3,2);
    number_of_failed_tests += TestCSRMatrixProduct(3,3);
    number_of_failed_tests += TestCSRMatrixProduct(1,3);
    number_of_failed_tests += TestCSRMatrixProduct(2,3);


    std::cout << number_of_failed_tests << " tests failed" << std::endl;

    return number_of_failed_tests;
}
