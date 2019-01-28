#include "amatrix.h"
#include "checks.h"

std::size_t TestCSRMatrixConstructorGraph(std::size_t Size1, std::size_t Size2) {
    AMatrix::SparseGraph a_graph(Size1, Size2);

    // Filling upper triangle
    for (std::size_t i = 0; i < Size1; i++)
        for (std::size_t j = i; j < Size2; j++)
            a_graph.insert(i, j);

    AMatrix::SparseMatrix<AMatrix::CSRMatrixStorage<double>> a_matrix(a_graph);

	AMATRIX_CHECK_EQUAL(a_matrix.size1(), Size1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), Size2);
    AMATRIX_CHECK_EQUAL(a_matrix.non_zeros_size(), a_graph.non_zeros_size());


    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = i; j < a_matrix.size2(); j++)
            a_matrix.set(i, j, 2.33 * i - 4.52 * j);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++) {
            if (j >= i) {
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.33 * i - 4.52 * j);
            } else {
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 0);
            }
        }

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestCSRMatrixConstructorGraph(1, 1);

    number_of_failed_tests += TestCSRMatrixConstructorGraph(1, 2);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(2, 1);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(2, 2);

    number_of_failed_tests += TestCSRMatrixConstructorGraph(3, 1);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(3, 2);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(3, 3);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(1, 3);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(2, 3);
    number_of_failed_tests += TestCSRMatrixConstructorGraph(3, 3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
