#include "amatrix.h"
#include "checks.h"

int TestMatrixSwap(std::size_t Size1, std::size_t Size2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(Size1, Size2);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
            b_matrix(i, j) = 3.14;
        }

    a_matrix.swap(b_matrix);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            AMATRIX_CHECK_EQUAL(a_matrix(i, j), 3.14);
            AMATRIX_CHECK_EQUAL(b_matrix(i, j),2.33 * i - 4.52 * j);
        }

    return 0;  // not failed
}

int TestMatrixSwapResize(std::size_t Size1, std::size_t Size2) {
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> a_matrix(Size1, Size2);
    AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic> b_matrix(Size1+1, Size2+1);
    b_matrix.fill(2.22);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
            b_matrix(i, j) = 3.14;
        }

    a_matrix.swap(b_matrix);
    AMATRIX_CHECK_EQUAL(a_matrix.size1(), Size1+1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), Size2+1);
    AMATRIX_CHECK_EQUAL(b_matrix.size1(), Size1);
    AMATRIX_CHECK_EQUAL(b_matrix.size2(), Size2);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            if(i < Size1 && j < Size2){
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 3.14);
                AMATRIX_CHECK_EQUAL(b_matrix(i, j),2.33 * i - 4.52 * j);
            }
            else{
               AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.22);
            }
        }

    return 0;  // not failed
}
template<std::size_t TSize2>
int TestMatrixSwapSize1Resize(std::size_t Size1) {
    AMatrix::Matrix<double, AMatrix::dynamic, TSize2> a_matrix(Size1, TSize2);
    AMatrix::Matrix<double, AMatrix::dynamic, TSize2> b_matrix(Size1+1, TSize2);
    b_matrix.fill(2.22);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
            b_matrix(i, j) = 3.14;
        }

    a_matrix.swap(b_matrix);
    AMATRIX_CHECK_EQUAL(a_matrix.size1(), Size1+1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), TSize2);
    AMATRIX_CHECK_EQUAL(b_matrix.size1(), Size1);
    AMATRIX_CHECK_EQUAL(b_matrix.size2(), TSize2);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            if(i < Size1 && j < TSize2){
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 3.14);
                AMATRIX_CHECK_EQUAL(b_matrix(i, j),2.33 * i - 4.52 * j);
            }
            else{
               AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.22);
            }
        }

    return 0;  // not failed
}

template<std::size_t TSize1>
int TestMatrixSwapSize2Resize(std::size_t Size2) {
    AMatrix::Matrix<double, TSize1, AMatrix::dynamic> a_matrix(TSize1, Size2);
    AMatrix::Matrix<double, TSize1, AMatrix::dynamic> b_matrix(TSize1, Size2+1);
    b_matrix.fill(2.22);
    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            a_matrix(i, j) = 2.33 * i - 4.52 * j;
            b_matrix(i, j) = 3.14;
        }

    a_matrix.swap(b_matrix);
    AMATRIX_CHECK_EQUAL(a_matrix.size1(), TSize1);
    AMATRIX_CHECK_EQUAL(a_matrix.size2(), Size2+1);
    AMATRIX_CHECK_EQUAL(b_matrix.size1(), TSize1);
    AMATRIX_CHECK_EQUAL(b_matrix.size2(), Size2);

    for (std::size_t i = 0; i < a_matrix.size1(); i++)
        for (std::size_t j = 0; j < a_matrix.size2(); j++){
            if(i < TSize1 && j < Size2){
                AMATRIX_CHECK_EQUAL(a_matrix(i, j), 3.14);
                AMATRIX_CHECK_EQUAL(b_matrix(i, j),2.33 * i - 4.52 * j);
            }
            else{
               AMATRIX_CHECK_EQUAL(a_matrix(i, j), 2.22);
            }
        }

    return 0;  // not failed
}

int main() {
    int number_of_failed_tests = 0;
	number_of_failed_tests += TestMatrixSwap(1,1);

	number_of_failed_tests += TestMatrixSwap(1,2);
	number_of_failed_tests += TestMatrixSwap(2,1);
	number_of_failed_tests += TestMatrixSwap(2,2);

	number_of_failed_tests += TestMatrixSwap(3,1);
	number_of_failed_tests += TestMatrixSwap(3,2);
	number_of_failed_tests += TestMatrixSwap(3,3);
	number_of_failed_tests += TestMatrixSwap(1,3);
	number_of_failed_tests += TestMatrixSwap(2,3);
	number_of_failed_tests += TestMatrixSwap(3,3);

	number_of_failed_tests += TestMatrixSwapResize(1,1);

	number_of_failed_tests += TestMatrixSwapResize(1,2);
	number_of_failed_tests += TestMatrixSwapResize(2,1);
	number_of_failed_tests += TestMatrixSwapResize(2,2);

	number_of_failed_tests += TestMatrixSwapResize(3,1);
	number_of_failed_tests += TestMatrixSwapResize(3,2);
	number_of_failed_tests += TestMatrixSwapResize(3,3);
	number_of_failed_tests += TestMatrixSwapResize(1,3);
	number_of_failed_tests += TestMatrixSwapResize(2,3);
	number_of_failed_tests += TestMatrixSwapResize(3,3);

	number_of_failed_tests += TestMatrixSwapSize1Resize<1>(1);

	number_of_failed_tests += TestMatrixSwapSize1Resize<2>(1);
	number_of_failed_tests += TestMatrixSwapSize1Resize<1>(2);
	number_of_failed_tests += TestMatrixSwapSize1Resize<2>(2);

	number_of_failed_tests += TestMatrixSwapSize1Resize<1>(3);
	number_of_failed_tests += TestMatrixSwapSize1Resize<2>(3);
	number_of_failed_tests += TestMatrixSwapSize1Resize<3>(3);
	number_of_failed_tests += TestMatrixSwapSize1Resize<3>(1);
	number_of_failed_tests += TestMatrixSwapSize1Resize<3>(2);
	number_of_failed_tests += TestMatrixSwapSize1Resize<3>(3);

	number_of_failed_tests += TestMatrixSwapSize2Resize<1>(1);

	number_of_failed_tests += TestMatrixSwapSize2Resize<2>(1);
	number_of_failed_tests += TestMatrixSwapSize2Resize<1>(2);
	number_of_failed_tests += TestMatrixSwapSize2Resize<2>(2);

	number_of_failed_tests += TestMatrixSwapSize2Resize<1>(3);
	number_of_failed_tests += TestMatrixSwapSize2Resize<2>(3);
	number_of_failed_tests += TestMatrixSwapSize2Resize<3>(3);
	number_of_failed_tests += TestMatrixSwapSize2Resize<3>(1);
	number_of_failed_tests += TestMatrixSwapSize2Resize<3>(2);
	number_of_failed_tests += TestMatrixSwapSize2Resize<3>(3);

    std::cout << number_of_failed_tests << "tests failed" << std::endl;

    return number_of_failed_tests;
}
