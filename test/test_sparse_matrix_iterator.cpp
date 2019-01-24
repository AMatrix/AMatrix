#include "amatrix.h"
#include "checks.h"

std::size_t TestCSRMatrixIterator(std::size_t Size1, std::size_t Size2) {
    AMatrix::SparseMatrix<AMatrix::CSRMatrixStorage<double>> a_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            double value = 2.33 * i - 4.52 * j;
            if (value != 0.00)
                a_matrix.insert(i, j, value);
        }
    std::cout << "a_matrix : " << a_matrix.size1() << "*" << a_matrix.size2() << std::endl;
    for (auto i_non_zero = a_matrix.begin(); i_non_zero != a_matrix.end(); i_non_zero++) {
        AMATRIX_CHECK_EQUAL(*i_non_zero, 2.33 * i_non_zero.index1() - 4.52 * i_non_zero.index2());
    }

    for (auto i_non_zero = a_matrix.begin(); i_non_zero != a_matrix.end(); ++i_non_zero) {
        AMATRIX_CHECK_EQUAL(*i_non_zero, 2.33 * i_non_zero.index1() - 4.52 * i_non_zero.index2());
    }

	auto i_non_zero = a_matrix.begin();
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            if (a_matrix(i, j) != 0.00) {
                AMATRIX_CHECK_EQUAL(i_non_zero.index1(), i);
                AMATRIX_CHECK_EQUAL(i_non_zero.index2(), j);
                i_non_zero++;
            }

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestCSRMatrixIterator(1, 1);
							  
    number_of_failed_tests += TestCSRMatrixIterator(1, 2);
    number_of_failed_tests += TestCSRMatrixIterator(2, 1);
    number_of_failed_tests += TestCSRMatrixIterator(2, 2);
							  
    number_of_failed_tests += TestCSRMatrixIterator(3, 1);
    number_of_failed_tests += TestCSRMatrixIterator(3, 2);
    number_of_failed_tests += TestCSRMatrixIterator(3, 3);
    number_of_failed_tests += TestCSRMatrixIterator(1, 3);
    number_of_failed_tests += TestCSRMatrixIterator(2, 3);
    number_of_failed_tests += TestCSRMatrixIterator(3, 3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
