#include "matrix.h"
#include "checks.h"

template<std::size_t Size1, std::size_t Size2>
std::size_t TestMatrixTranspose() {
	AMatrix::Matrix<double, AMatrix::dynamic,AMatrix::dynamic> a_matrix(Size1,Size2);
	double b = 0;
	for (std::size_t i = 0; i < a_matrix.size1(); i++)
		for (std::size_t j = 0; j < a_matrix.size2(); j++)
			a_matrix(i, j) =  b++;

	auto b_matrix = a_matrix.transpose();
	
	for (std::size_t i = 0; i < a_matrix.size1(); i++)
		for (std::size_t j = 0; j < a_matrix.size2(); j++){
			AMATRIX_CHECK_EQUAL(b_matrix(j,i) , a_matrix(i,j));
		}
	return 0; // not failed
}


template <std::size_t Size1, std::size_t Size2,
    std::size_t NumberOfSecondRows>
std::size_t TestMatrixTransposeProduct() {
    std::cout << "Testing A(" << Size1 << "," << Size2
              << ") X B(" << Size2 << "," << NumberOfSecondRows
              << ") ";
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(Size2, SecondSize1);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> c_matrix(Size1, SecondSize1);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            if (i == j)
                a_matrix(i, j) = 2.33 * (i + 1);
            else
                a_matrix(i, j) = 0.00;

    for (std::size_t i = 0; i < b_matrix.size1(); i++)
        for (std::size_t j = 0; j < b_matrix.size2(); j++)
            b_matrix(i, j) = i + j + 1;

    c_matrix = a_matrix * b_matrix.transpose();

    for (std::size_t i = 0; i < c_matrix.size1(); i++)
        for (std::size_t j = 0; j < c_matrix.size2(); j++)
            if (static_cast<std::size_t>(i) < Size2)
                AMATRIX_CHECK_EQUAL(
                    c_matrix(i, j), b_matrix(j, i) * (i + 1) * 2.33);

    std::cout << "OK" << std::endl;
    return 0;  // not failed
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

