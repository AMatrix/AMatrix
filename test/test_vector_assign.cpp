#include "matrix.h"
#include "checks.h"

template<std::size_t TSize>
std::size_t TestZeroVectorAssign() {
	AMatrix::Vector<double, TSize> a_vector;
	a_vector = AMatrix::ZeroVector<double>(TSize);
	
	for (std::size_t i = 0; i < a_vector.size(); i++)
			AMATRIX_CHECK_EQUAL(a_vector[i], 0.00);

	return 0; // not failed
}

template<std::size_t TSize>
std::size_t TestVectorAssign() {
	AMatrix::Vector<double, TSize> a_vector;
	AMatrix::Vector<double, TSize> b_vector;
	for (std::size_t i = 0; i < a_vector.size(); i++)
			a_vector[i] =  2.33 * i;

	b_vector = a_vector;
	
	for (std::size_t i = 0; i < a_vector.size(); i++)
			AMATRIX_CHECK_EQUAL(b_vector[i], 2.33 * i);

	return 0; // not failed
}


int main()
{
	std::size_t number_of_failed_tests = 0;
	number_of_failed_tests += TestZeroVectorAssign<1>();
	number_of_failed_tests += TestZeroVectorAssign<2>();
	number_of_failed_tests += TestZeroVectorAssign<3>();
	number_of_failed_tests += TestVectorAssign<1>();
	number_of_failed_tests += TestVectorAssign<2>();
	number_of_failed_tests += TestVectorAssign<3>();

	std::cout << number_of_failed_tests << "tests failed" << std::endl;

	return number_of_failed_tests;
}

