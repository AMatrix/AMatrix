#include "amatrix.h"
#include "checks.h"

template <std::size_t TSize>
int TestSubVectorAcess() {
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

    for (std::size_t i = 0; i < sub_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(sub_vector(0, i), a_vector[i + sub_index]);

	AMATRIX_CHECK_EQUAL(sub_vector.data(), &a_vector[sub_index]);

    return 0;  // not failed
}

template <std::size_t TSize>
int TestSubVectorMemberwiseAssign() {
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

    for (std::size_t i = 0; i < sub_vector.size(); i++)
        sub_vector(0, i) = 1.33 * i;

    for (std::size_t i = sub_index; i < a_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(a_vector[i], 1.33 * (i - sub_index));

    return 0;  // not failed
}

template <std::size_t TSize>
int TestSubVectorAssign() {
    AMatrix::Vector<double, TSize> a_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = 1.23;

    std::size_t sub_size = (TSize > 1) ? TSize - 1 : 1;
    std::size_t sub_index = (TSize > 1) ? 1 : 0;

    AMatrix::SubVector<AMatrix::Vector<double, TSize>> sub_vector(
        a_vector, sub_index, sub_size);

    AMATRIX_CHECK_EQUAL(sub_vector.size(), sub_size);

    sub_vector = AMatrix::ZeroMatrix<double>(sub_size, 1);

    for (std::size_t i = sub_index; i < a_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(a_vector[i], 0);

    return 0;  // not failed
}

template <std::size_t TSize>
int TestSubVectorPlusEqual() {
    AMatrix::Vector<double, TSize> a_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = 1.23;

    std::size_t sub_size = (TSize > 1) ? TSize - 1 : 1;
    std::size_t sub_index = (TSize > 1) ? 1 : 0;

    AMatrix::Vector<double, AMatrix::dynamic> b_vector(sub_size);
    for (std::size_t i = 0; i < b_vector.size(); i++)
        b_vector[i] = 4.56 * (i + sub_index);

    AMatrix::SubVector<AMatrix::Vector<double, TSize>> sub_vector(
        a_vector, sub_index, sub_size);

    AMATRIX_CHECK_EQUAL(sub_vector.size(), sub_size);

    sub_vector += b_vector;

    for (std::size_t i = sub_index; i < a_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(a_vector[i], 1.23 + 4.56 * i);

    return 0;  // not failed
}

template <std::size_t TSize>
int TestSubVectorMinusEqual() {
    AMatrix::Vector<double, TSize> a_vector;
    for (std::size_t i = 0; i < a_vector.size(); i++)
        a_vector[i] = 1.23;

    std::size_t sub_size = (TSize > 1) ? TSize - 1 : 1;
    std::size_t sub_index = (TSize > 1) ? 1 : 0;

    AMatrix::Vector<double, AMatrix::dynamic> b_vector(sub_size);
    for (std::size_t i = 0; i < b_vector.size(); i++)
        b_vector[i] = 4.56 * (i + sub_index);

    AMatrix::SubVector<AMatrix::Vector<double, TSize>> sub_vector(
        a_vector, sub_index, sub_size);

    AMATRIX_CHECK_EQUAL(sub_vector.size(), sub_size);

    sub_vector -= b_vector;

    for (std::size_t i = sub_index; i < a_vector.size(); i++)
        AMATRIX_CHECK_EQUAL(a_vector[i], 1.23 - 4.56 * i);

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;

    number_of_failed_tests += TestSubVectorAcess<1>();
    number_of_failed_tests += TestSubVectorAcess<2>();
    number_of_failed_tests += TestSubVectorAcess<3>();

    number_of_failed_tests += TestSubVectorMemberwiseAssign<1>();
    number_of_failed_tests += TestSubVectorMemberwiseAssign<2>();
    number_of_failed_tests += TestSubVectorMemberwiseAssign<3>();

    number_of_failed_tests += TestSubVectorAssign<1>();
    number_of_failed_tests += TestSubVectorAssign<2>();
    number_of_failed_tests += TestSubVectorAssign<3>();

    number_of_failed_tests += TestSubVectorPlusEqual<1>();
    number_of_failed_tests += TestSubVectorPlusEqual<2>();
    number_of_failed_tests += TestSubVectorPlusEqual<3>();

    number_of_failed_tests += TestSubVectorMinusEqual<1>();
    number_of_failed_tests += TestSubVectorMinusEqual<2>();
    number_of_failed_tests += TestSubVectorMinusEqual<3>();

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
