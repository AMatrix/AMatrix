#include "amatrix.h"
#include "checks.h"

template<std::size_t TSize1, std::size_t TSize2>
int TestMatrixTranspose() {
	AMatrix::Matrix<double, TSize1,TSize2> a_matrix;
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


template <std::size_t TSize1, std::size_t TSize2,
    std::size_t NumberOfSecondRows>
int TestMatrixTransposeProduct() {
    std::cout << "Testing A(" << TSize1 << "," << TSize2
              << ") X B(" << TSize2 << "," << NumberOfSecondRows
              << ") ";
    AMatrix::Matrix<double, TSize1, TSize2> a_matrix;
    AMatrix::Matrix<double, NumberOfSecondRows, TSize2> b_matrix;
    AMatrix::Matrix<double, TSize1, NumberOfSecondRows> c_matrix;
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++)
            if (i == j)
                a_matrix(i, j) = 2.33 * (i + 1);
            else
                a_matrix(i, j) = 0.00;

    for (std::size_t i = 0; i < b_matrix.size1(); i++)
        for (std::size_t j = 0; j < b_matrix.size2(); j++)
            b_matrix(i, j) = i + j + 1.00;

    c_matrix = a_matrix * b_matrix.transpose();

    for (std::size_t i = 0; i < c_matrix.size1(); i++)
        for (std::size_t j = 0; j < c_matrix.size2(); j++)
            if (static_cast<std::size_t>(i) < TSize2)
                AMATRIX_CHECK_EQUAL(
                    c_matrix(i, j), b_matrix(j, i) * (i + 1) * 2.33);

    std::cout << "OK" << std::endl;
    return 0;  // not failed
}

int main()
{
	int number_of_failed_tests = 0;
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

    // matrix transpose product test
    number_of_failed_tests += TestMatrixTransposeProduct<1, 1, 1>();

    number_of_failed_tests += TestMatrixTransposeProduct<1, 2, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 1, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 2, 1>();

    number_of_failed_tests += TestMatrixTransposeProduct<3, 1, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 2, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 3, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<1, 3, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 3, 1>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 3, 1>();

    number_of_failed_tests += TestMatrixTransposeProduct<1, 1, 2>();

    number_of_failed_tests += TestMatrixTransposeProduct<1, 2, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 1, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 2, 2>();

    number_of_failed_tests += TestMatrixTransposeProduct<3, 1, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 2, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 3, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<1, 3, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 3, 2>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 3, 2>();

    number_of_failed_tests += TestMatrixTransposeProduct<1, 1, 3>();

    number_of_failed_tests += TestMatrixTransposeProduct<1, 2, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 1, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 2, 3>();

    number_of_failed_tests += TestMatrixTransposeProduct<3, 1, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 2, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 3, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<1, 3, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<2, 3, 3>();
    number_of_failed_tests += TestMatrixTransposeProduct<3, 3, 3>();

	std::cout << number_of_failed_tests << "tests failed" << std::endl;

	return number_of_failed_tests;
}

