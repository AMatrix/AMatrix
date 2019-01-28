#include "amatrix.h"
#include "checks.h"

std::size_t TestSparseGraphRowSize(std::size_t Size1, std::size_t Size2) {
    AMatrix::SparseGraph a_graph(Size1, Size2);

    AMATRIX_CHECK_EQUAL(a_graph.size1(), Size1);
    AMATRIX_CHECK_EQUAL(a_graph.size2(), Size2);

    // Filling upper triangle
    for (std::size_t i = 0; i < Size1; i++)
        for (std::size_t j = i; j < Size2; j++)
            a_graph.insert(i, j);

    for (std::size_t i = 0; i < Size1; i++) {
        if (i >= Size2) {
            AMATRIX_CHECK_EQUAL(a_graph.row_size(i), 0);
        } else {
            AMATRIX_CHECK_EQUAL(a_graph.row_size(i), Size2 - i);
        }
    }

    // Now filling all columns
    for (std::size_t i = 0; i < Size1; i++)
        for (std::size_t j = 0; j < Size2; j++)
            a_graph.insert(i, j);

    for (std::size_t i = 0; i < Size1; i++) {
        AMATRIX_CHECK_EQUAL(a_graph.row_size(i), Size2);
    }

    AMATRIX_CHECK_EQUAL(a_graph.non_zeros_size(), Size1 * Size2);

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;
    number_of_failed_tests += TestSparseGraphRowSize(1, 1);

    number_of_failed_tests += TestSparseGraphRowSize(1, 2);
    number_of_failed_tests += TestSparseGraphRowSize(2, 1);
    number_of_failed_tests += TestSparseGraphRowSize(2, 2);

    number_of_failed_tests += TestSparseGraphRowSize(3, 1);
    number_of_failed_tests += TestSparseGraphRowSize(3, 2);
    number_of_failed_tests += TestSparseGraphRowSize(3, 3);
    number_of_failed_tests += TestSparseGraphRowSize(1, 3);
    number_of_failed_tests += TestSparseGraphRowSize(2, 3);
    number_of_failed_tests += TestSparseGraphRowSize(3, 3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
