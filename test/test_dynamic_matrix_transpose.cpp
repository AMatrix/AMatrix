#include <iostream>

#include "matrix.h"
#include "checks.h"

template<std::size_t Size1, std::size_t Size2>
std::size_t TestMatrixTranspose() {
	AMatrix::Matrix<double, 0,0> a_matrix(Size1,Size2);
	double b = 0;
	for (std::size_t i = 0; i < a_matrix.size1(); i++)
		for (std::size_t j = 0; j < a_matrix.size2(); j++)
			a_matrix(i, j) =  b++;

	auto b_matrix = a_matrix.Transpose();
	
	for (std::size_t i = 0; i < a_matrix.size1(); i++)
		for (std::size_t j = 0; j < a_matrix.size2(); j++){
			AMATRIX_CHECK_EQUAL(b_matrix(j,i) , a_matrix(i,j));
		}
	return 0; // not failed
}


int main()
{
	std::size_t number_of_failed_tests = 0;
	number_of_failed_tests += TestMatrixTranspose<1,1>();

	number_of_failed_tests += TestMatrixTranspose<1,2>();
	number_of_failed_tests += TestMatrixTranspose<2,1>();
	number_of_failed_tests += TestMatrixTranspose<2,2>();

	number_of_failed_tests += TestMatrixTranspose<3,1>();
	number_of_failed_tests += TestMatrixTranspose<3,2>();
	number_of_failed_tests += TestMatrixTranspose<3,3>();
	number_of_failed_tests += TestMatrixTranspose<1,3>();
	number_of_failed_tests += TestMatrixTranspose<2,3>();
	number_of_failed_tests += TestMatrixTranspose<3,3>();

	std::cout << number_of_failed_tests << "tests failed" << std::endl;

	return number_of_failed_tests;
}

