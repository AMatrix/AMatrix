// AMatrix.cpp : Defines the entry point for the console application.
//

#include <chrono>
#include <iostream>

#include "matrix.h"
//#include "Eigen/Dense"

class Timer {
	std::chrono::high_resolution_clock::time_point _start;
public:
	Timer() : _start(std::chrono::high_resolution_clock::now()) {
	}
	std::chrono::milliseconds elapsed() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _start);
	}
	void reset() {
		_start = std::chrono::high_resolution_clock::now();
	}
};

template<typename TMatrixType>
long long MeasureAccessTime(TMatrixType& A) {
	int repeat_number = 10000;
	Timer timer;
	for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				A(i, j) += i - j;
	return timer.elapsed().count();
}


template<typename TMatrixType>
std::size_t MeasureAssignTime(TMatrixType& A) {
	int repeat_number = 10000;
	TMatrixType B = A;
	Timer timer;
	for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				B(i, j) += i - j;
		A = B;
	}

	return timer.elapsed().count();
}

template<typename TMatrixType>
std::size_t MeasureSumTime(TMatrixType& A, TMatrixType& B) {
	int repeat_number = 10000;
	TMatrixType C = A;
	TMatrixType D = A;
	Timer timer;
	for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
		C = A + B ; 
		B = C;
	}

	return timer.elapsed().count();
}

template<typename TMatrixType1, typename TMatrixType2>
std::size_t MeasureMultTime(TMatrixType1& A, TMatrixType2& B) {
	int repeat_number = 1000;
	TMatrixType1 C = A;
	TMatrixType1 D = A;
	Timer timer;
	for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
		D = A;
		for (int i = 0; i < 1000; i++) {
			C = D * B;
			D = C;
		}
	}

	return timer.elapsed().count();
}



int main()
{
	std::cout << "Measuring Access time" << std::endl;
	MeasureAccessTime(AMatrix::Matrix<double,3,3>(0.00));
	throw std::runtime_error("Test Fail Message!");
	return 0;
}

