#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize>
std::size_t TestSubVectorAcess() {
    AMatrix::Vector<double, TSize> a_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = 2.33 * i;

    std::size_t sub_size = (TSize > 1) ? TSize - 1 : 1;
    std::size_t sub_index = (TSize > 1) ? 1 : 0;

    AMatrix::SubVector<AMatrix::Vector<double, TSize>> sub_vector(
        a_vector, sub_index, sub_size);

    AMATRIX_CHECK_EQUAL(sub_vector.size(), sub_size);

    for (std::size_t i = 0; i < sub_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(sub_vector[i], a_vector[i + sub_index]);

    return 0;  // not failed
}

template <std::size_t TSize>
std::size_t TestSubVectorAssign() {
    AMatrix::Vector<double, TSize> a_vector(
        AMatrix::ZeroMatrix<double>(TSize, 1));

    std::size_t sub_size = (TSize > 1) ? TSize - 1 : 1;
    std::size_t sub_index = (TSize > 1) ? 1 : 0;

    AMatrix::SubVector<AMatrix::Vector<double, TSize>> sub_vector(
        a_vector, sub_index, sub_size);

    AMATRIX_CHECK_EQUAL(sub_vector.size(), sub_size);

    for (std::size_t i = 0; i < sub_vector.size(); i++)
        sub_vector[i] = 2.33 * i;

    for (std::size_t i = sub_index; i < a_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(a_vector[i], 2.33 * (i - sub_index));

    return 0;  // not failed
}

int main() {
    std::size_t number_of_failed_tests = 0;

    number_of_failed_tests += TestSubVectorAcess<1>();
    number_of_failed_tests += TestSubVectorAcess<2>();
    number_of_failed_tests += TestSubVectorAcess<3>();

    number_of_failed_tests += TestSubVectorAssign<1>();
    number_of_failed_tests += TestSubVectorAssign<2>();
    number_of_failed_tests += TestSubVectorAssign<3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
