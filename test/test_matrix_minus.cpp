#include <iostream>

#include "matrix.h"
#include "checks.h"




template<std::size_t NumberOfRows, std::size_t NumberOfCulomns>
int TestMatrixMinus() {
	AMatrix::Matrix<double, NumberOfRows,NumberOfCulomns> a_matrix;
	AMatrix::Matrix<double, NumberOfRows,NumberOfCulomns> b_matrix;
	AMatrix::Matrix<double, NumberOfRows,NumberOfCulomns> c_matrix;
	for (int i = 0; i < a_matrix.size1(); i++)
		for (int j = 0; j < a_matrix.size2(); j++)
			a_matrix(i, j) =  2.33 * i - 4.52 * j;

	b_matrix = a_matrix;
	c_matrix = a_matrix - b_matrix;
	
	for (int i = 0; i < a_matrix.size1(); i++)
		for (int j = 0; j < a_matrix.size2(); j++)
			AMATRIX_CHECK_EQUAL(c_matrix(i,j), 0.00);

	return 0; // not failed
}


int main()
{
	int number_of_failed_tests = 0;
	number_of_failed_tests += TestMatrixMinus<1,1>();

	number_of_failed_tests += TestMatrixMinus<1,2>();
	number_of_failed_tests += TestMatrixMinus<2,1>();
	number_of_failed_tests += TestMatrixMinus<2,2>();

	number_of_failed_tests += TestMatrixMinus<3,1>();
	number_of_failed_tests += TestMatrixMinus<3,2>();
	number_of_failed_tests += TestMatrixMinus<3,3>();
	number_of_failed_tests += TestMatrixMinus<1,3>();
	number_of_failed_tests += TestMatrixMinus<2,3>();
	number_of_failed_tests += TestMatrixMinus<3,3>();

	std::cout << number_of_failed_tests << "tests failed" << std::endl;

	return number_of_failed_tests;
}

