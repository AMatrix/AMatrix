
#include <iostream>

#include "timer.h"
#include "matrix.h"

#if defined(AMATRIX_COMPARE_WITH_EIGEN)
#include "Eigen/Dense"
#endif

template <typename TMatrixType, int NumberOfRows, int NumberOfColumns>
class ComparisonColumn {
    TMatrixType mA;
    TMatrixType mB;
    void initialize(TMatrixType& TheMatrix, double Value) {
        for (int i = 0; i < NumberOfRows; i++)
            for (int j = 0; j < NumberOfColumns; j++)
                TheMatrix(i, j) = Value;
    }

   public:
    ComparisonColumn() {
        initialize(mA, 0.01);
        initialize(mB, 1.00);
    }

    Timer::duration_type MeasureSumTime() {
        int repeat_number = 10000000;
        TMatrixType C = mA;
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            C = mA + mB;
            mB = C;
        }

        return timer.elapsed().count();
    }

    Timer::duration_type MeasureMultTime() {
        int repeat_number = 100000000;
        TMatrixType C = mA;
        TMatrixType D = mA;
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            D = mA;
            for (int i = 0; i < 1000; i++) {
                C = D * mB;
                D = C;
            }
        }

        return timer.elapsed().count();
    }
};

void CompareSumTime() {
    ComparisonColumn<AMatrix::Matrix<double, 3, 3>, 3, 3> a_matrix_column;
    std::cout << "C = A + B\t\t" << a_matrix_column.MeasureSumTime();
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, 3, 3>, 3, 3> eigen_column;
    std::cout << "t\t" << eigen_column.MeasureSumTime();
#endif
    std::cout << std::endl;
}

void CompareMultTime() {
    ComparisonColumn<AMatrix::Matrix<double, 3, 3>, 3, 3> a_matrix_column;
    std::cout << "C = A * B\t\t" << a_matrix_column.MeasureMultTime();
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, 3, 3>, 3, 3> eigen_column;
    std::cout << "\t\t" << eigen_column.MeasureMultTime();
#endif
    std::cout << std::endl;
}

int main() {
    std::cout << "operation\t\tAMatrix\t\tEigen\t\tUblas\t\tAtlas" << std::endl;
    CompareSumTime();
    CompareMultTime();
    return 0;
}
