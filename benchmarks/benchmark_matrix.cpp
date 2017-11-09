#include <iostream>
#include <cmath>

#include "timer.h"
#include "matrix.h"

#if defined(AMATRIX_COMPARE_WITH_EIGEN)
#include "Eigen/Dense"
#endif

#if defined(AMATRIX_COMPARE_WITH_UBLAS)
#include <boost/numeric/ublas/matrix.hpp>
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
    std::string mColumnName;

   protected:
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
    ComparisonColumn() = delete;

    ComparisonColumn(std::string ColumnName) : mColumnName(ColumnName) {
        initialize(mA, 0.00);
        initialize(mB, 0.00);
        initialize(mC, 0.00);
    }
    std::string const& GetColumnName() { return mColumnName; }
    TMatrixType& GetMatrixC() { return mC; }

    void MeasureSumTime() {
        int repeat_number = 10000000;
        initialize(mA, 0.01);
        initialize(mB, 0.20);
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            mC.noalias() = mA + mB;
            mB.noalias() = mC;
        }
        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }

    void MeasureMultTime() {
        int repeat_number = 10000000;
        initialize_rotation(mA, -0.0001);
        initialize_rotation(mB, 0.0001);
        TMatrixType D;
        initialize(D, 1.00);
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            mC.noalias() = mA * TMatrixType(D * mA);
            D.noalias() = mB * TMatrixType(mC * mB);
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }

#if defined(AMATRIX_COMPARE_WITH_UBLAS)

#endif
};

template <typename TMatrixType, int NumberOfRows, int NumberOfColumns>
class UblasComparisonColumn
    : public ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns> {
   public:
    using BsaeType =
        ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns>;

    UblasComparisonColumn(std::string ColumnName)
        : ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns>(
              ColumnName) {}

    void MeasureSumTime() {
        int repeat_number = 10000000;
        BsaeType::initialize(BsaeType::mA, 0.01);
        BsaeType::initialize(BsaeType::mB, 0.20);
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            boost::numeric::ublas::noalias(BsaeType::mC) =
                BsaeType::mA + BsaeType::mB;
            boost::numeric::ublas::noalias(BsaeType::mB) = BsaeType::mC;
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }
    void MeasureMultTime() {
        using namespace boost::numeric::ublas;
        int repeat_number = 10000000;
        BsaeType::initialize_rotation(BsaeType::mA, -0.0001);
        BsaeType::initialize_rotation(BsaeType::mB, 0.0001);
        TMatrixType D;
        BsaeType::initialize(D, 1.00);
        Timer timer;
        for (int i_repeat = 0; i_repeat < repeat_number; i_repeat++) {
            noalias(BsaeType::mC) = prod(BsaeType::mA, TMatrixType(prod(D, BsaeType::mA)));
            noalias(D) = prod(BsaeType::mB, TMatrixType(prod(BsaeType::mC, BsaeType::mB)));
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }
};

template <typename TMatrixType, int NumberOfRows, int NumberOfColumns>
class EmptyComparisonColumn
    : public ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns> {
   public:
    EmptyComparisonColumn(std::string ColumnName)
        : ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns>("") {}
    void MeasureSumTime() {}
    void MeasureMultTime() {}
};

template <int NumberOfRows, int NumberOfColumns>
class BenchmarkMatrix {
    ComparisonColumn<AMatrix::Matrix<double, NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mAMatrixColumn;
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mEigenColumn;
#elif
    EmptyComparisonColumn<Eigen::Matrix<double, NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mEigenColumn;
#endif
#if defined(AMATRIX_COMPARE_WITH_UBLAS)
    UblasComparisonColumn<boost::numeric::ublas::bounded_matrix<double,
                              NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mUblasColumn;
#elif
    EmptyComparisonColumn<boost::numeric::ublas::bounded_matrix<double,
                              NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mUblasColumn;
#endif
   public:
    BenchmarkMatrix()
        : mAMatrixColumn("AMatrix"),
          mEigenColumn("Eigen"),
          mUblasColumn("Ublas") {
        std::cout << "Benchmark[" << NumberOfRows << "," << NumberOfColumns
                  << "]";
        std::cout << "\t\t" << mAMatrixColumn.GetColumnName();
        std::cout << "\t\t" << mEigenColumn.GetColumnName();
        std::cout << "\t\t" << mUblasColumn.GetColumnName();
        std::cout << std::endl;
    }

    void Run() {
        std::cout << "C = A + B";
        mAMatrixColumn.MeasureSumTime();
        mEigenColumn.MeasureSumTime();
        mUblasColumn.MeasureSumTime();
        std::cout << std::endl;

        std::cout << "C = A * B";
        mAMatrixColumn.MeasureMultTime();
        mEigenColumn.MeasureMultTime();
        mUblasColumn.MeasureMultTime();
        std::cout << std::endl;        
        
        std::cout << std::endl;
    }
};

int main() {
    BenchmarkMatrix<3, 3> benchmark_3_3;
    benchmark_3_3.Run();

    BenchmarkMatrix<4, 4> benchmark_4_4;
    benchmark_4_4.Run();

    BenchmarkMatrix<6, 6> benchmark_6_6;
    benchmark_6_6.Run();
   
    return 0;
}
