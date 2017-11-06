
#include <iostream>
#include <cmath>

#include "timer.h"
#include "matrix.h"

#if defined(AMATRIX_COMPARE_WITH_EIGEN)
#include "Eigen/Dense"
#endif

template <typename TMatrixType1, typename TMatrixType2>
bool CheckEqual(TMatrixType1 const& Matrix1, TMatrixType2 const& Matrix2) {
    for (int i = 0; i < Matrix1.size1(); i++)
        for (int j = 0; j < Matrix1.size2(); j++)
            if (Matrix1(i, j) != Matrix2(i, j))
                return false;

    return true;
}

template <typename TMatrixType, int NumberOfRows, int NumberOfColumns>
class ComparisonColumn {
    TMatrixType mA;
    TMatrixType mB;
    TMatrixType mC;

    void initialize(TMatrixType& TheMatrix, double Value) {
        for (int i = 0; i < NumberOfRows; i++)
            for (int j = 0; j < NumberOfColumns; j++)
                TheMatrix(i, j) = Value;
    }

    void initialize_rotation(TMatrixType& TheMatrix, double AngleInRadian) {
        AMatrix::Matrix<double, 3, 3> block;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
				block(i, j) = 0.00;
				
        block(0, 0) = std::cos(AngleInRadian);
        block(0, 1) = -std::sin(AngleInRadian);
        block(1, 0) = std::sin(AngleInRadian);
        block(1, 1) = std::cos(AngleInRadian);
        block(2, 2) = 1.00;

        for (int i = 0; i < NumberOfRows; i++)
            for (int j = 0; j < NumberOfColumns; j++) {
                auto block_i = i % 3;
                auto block_j = j % 3;
                TheMatrix(i, j) = block(block_i, block_j);
            }
    }

   public:
    ComparisonColumn() {
        initialize(mA, 0.00);
        initialize(mB, 0.00);
        initialize(mC, 0.00);
    }

    TMatrixType& GetMatrixC() { return mC; }

    Timer::duration_type MeasureSumTime() {
        int repeat_number = 10000000;
        initialize(mA, 0.01);
        initialize(mB, 0.20);
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            mC = mA + mB;
            mB = mC;
        }

        return timer.elapsed().count();
    }

    Timer::duration_type MeasureMultTime() {
        int repeat_number = 10000000;
        initialize_rotation(mA, -0.0001);
        initialize_rotation(mB, 0.0001);
        TMatrixType D;
        initialize(D, 1.00);
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            mC = D * mA;
            D = mC * mB;
        }

        return timer.elapsed().count();
    }
};

void CompareSumTime() {
    ComparisonColumn<AMatrix::Matrix<double, 3, 3>, 3, 3> a_matrix_column;
    std::cout << "C = A + B\t\t" << a_matrix_column.MeasureSumTime();
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, 3, 3>, 3, 3> eigen_column;
    std::cout << "\t\t" << eigen_column.MeasureSumTime();
    if (!CheckEqual(a_matrix_column.GetMatrixC(), eigen_column.GetMatrixC()))
        std::cout << "(Failed!)";

#endif
    std::cout << std::endl;
}

void CompareMultTime() {
    ComparisonColumn<AMatrix::Matrix<double, 3, 3>, 3, 3> a_matrix_column;
    std::cout << "C = A * B\t\t" << a_matrix_column.MeasureMultTime();
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, 3, 3>, 3, 3> eigen_column;
    std::cout << "\t\t" << eigen_column.MeasureMultTime();
    if (!CheckEqual(a_matrix_column.GetMatrixC(), eigen_column.GetMatrixC()))
        std::cout << "(Failed!)";
#endif
    std::cout << std::endl;
    // std::cout << "AMatrix C = " << a_matrix_column.GetMatrixC() << std::endl;
    // std::cout << "Eigen C = " << eigen_column.GetMatrixC() << std::endl;
}

int main() {
    std::cout << "operation\t\tAMatrix\t\tEigen\t\tUblas\t\tAtlas" << std::endl;
    CompareSumTime();
    CompareMultTime();
    return 0;
}
