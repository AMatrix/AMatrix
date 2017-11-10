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

template <typename TMatrixType, std::size_t NumberOfRows, std::size_t NumberOfColumns>
class ComparisonColumn {

   protected:
    static constexpr std::size_t mRepeat = static_cast<std::size_t>(1e8/(NumberOfRows*NumberOfColumns));
    TMatrixType mA;
    TMatrixType mB;
    TMatrixType mResult;
    std::string mColumnName;
    
    void initialize(TMatrixType& TheMatrix) {
        for (std::size_t i = 0; i < NumberOfRows; i++)
            for (std::size_t j = 0; j < NumberOfColumns; j++)
                TheMatrix(i, j) = j + 1.00;
    }

    void initializeInverse(TMatrixType& TheMatrix) {
        for (std::size_t i = 0; i < NumberOfRows; i++)
            for (std::size_t j = 0; j < NumberOfColumns; j++)
                TheMatrix(i, j) = 1.00 / (i + 1);
    }

    void initialize(TMatrixType& TheMatrix, double Value) {
        for (std::size_t i = 0; i < NumberOfRows; i++)
            for (std::size_t j = 0; j < NumberOfColumns; j++)
                TheMatrix(i, j) = Value;
    }

    void initialize_rotation(TMatrixType& TheMatrix, double AngleInRadian) {
        AMatrix::Matrix<double, 3, 3> block;

        for (std::size_t i = 0; i < 3; i++)
            for (std::size_t j = 0; j < 3; j++)
                block(i, j) = 0.00;

        block(0, 0) = std::cos(AngleInRadian);
        block(0, 1) = -std::sin(AngleInRadian);
        block(1, 0) = std::sin(AngleInRadian);
        block(1, 1) = std::cos(AngleInRadian);
        block(2, 2) = 1.00;

        for (std::size_t i = 0; i < NumberOfRows; i++)
            for (std::size_t j = 0; j < NumberOfColumns; j++) {
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
        initialize(mResult, 0.00);
    }
    std::string const& GetColumnName() { return mColumnName; }
    TMatrixType& GetResult() { return mResult; }

    template <typename TMatrixType2>
    bool CheckResult(TMatrixType2 const& Reference) {
        for (std::size_t i = 0; i < NumberOfRows; i++)
            for (std::size_t j = 0; j < NumberOfColumns; j++)
                if (mResult(i, j) != Reference(i, j))
                    return false;

        return true;
    }

    void MeasureSumTime() {
        initialize(mA, 0.01);
        initialize(mB, 0.20);
        Timer timer;
        for (std::size_t i_repeat = 0; i_repeat < mRepeat; i_repeat++) {
            mResult.noalias() = mA + mB;
            mB.noalias() = mResult;
        }
        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }

    void MeasureMultTime() {
        initialize(mA);
        initializeInverse(mB);
        TMatrixType D;
        initializeInverse(D);
        Timer timer;
        for (std::size_t i_repeat = 0; i_repeat < mRepeat; i_repeat++) {
            mResult.noalias() = D * mA;
            D.noalias() = mB;
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }

    void MeasureABAMultTime() {
        initialize(mA);
        initializeInverse(mB);
        TMatrixType D;
        initializeInverse(D);
        Timer timer;
        for (std::size_t i_repeat = 0; i_repeat < mRepeat; i_repeat++) {
            mResult.noalias() = mA * TMatrixType(D * mA);
            D.noalias() = mB;
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }

#if defined(AMATRIX_COMPARE_WITH_UBLAS)

#endif
};

template <typename TMatrixType, std::size_t NumberOfRows, std::size_t NumberOfColumns>
class UblasComparisonColumn
    : public ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns> {
   public:
    using BaseType =
        ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns>;

    UblasComparisonColumn(std::string ColumnName)
        : ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns>(
              ColumnName) {}

    void MeasureSumTime() {
        BaseType::initialize(BaseType::mA, 0.01);
        BaseType::initialize(BaseType::mB, 0.20);
        Timer timer;
        for (std::size_t i_repeat = 0; i_repeat < BaseType::mRepeat; i_repeat++) {
            boost::numeric::ublas::noalias(BaseType::mResult) =
                BaseType::mA + BaseType::mB;
            boost::numeric::ublas::noalias(BaseType::mB) = BaseType::mResult;
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }
    void MeasureMultTime() {
        using namespace boost::numeric::ublas;
        BaseType::initialize(BaseType::mA);
        BaseType::initializeInverse(BaseType::mB);
        TMatrixType D;
        BaseType::initializeInverse(D);
        Timer timer;
        for (std::size_t i_repeat = 0; i_repeat < BaseType::mRepeat; i_repeat++) {
            noalias(BaseType::mResult) = prod(D, BaseType::mA);
            noalias(D) = BaseType::mB;
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }
    void MeasureABAMultTime() {
        using namespace boost::numeric::ublas;
        BaseType::initialize(BaseType::mA);
        BaseType::initializeInverse(BaseType::mB);
        TMatrixType D;
        BaseType::initializeInverse(D);
        Timer timer;
        for (std::size_t i_repeat = 0; i_repeat < mRepeat; i_repeat++) {
            noalias(BaseType::mResult) =
                prod(BaseType::mA, TMatrixType(prod(D, BaseType::mA)));
            noalias(D) = BaseType::mB;
        }

        auto elapsed = timer.elapsed().count();
        std::cout << "\t\t" << elapsed;
    }
};

template <typename TMatrixType, std::size_t NumberOfRows, std::size_t NumberOfColumns>
class EmptyComparisonColumn
    : public ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns> {
   public:
    EmptyComparisonColumn(std::string ColumnName)
        : ComparisonColumn<TMatrixType, NumberOfRows, NumberOfColumns>("") {}
    void MeasureSumTime() {std::cout << "\t\t";}
    void MeasureMultTime() {std::cout << "\t\t";}
    void MeasureABAMultTime() {std::cout << "\t\t";}
    
    template <typename TMatrixType2>
    bool CheckResult(TMatrixType2 const& Reference) {
        return true;
    }
};

template <std::size_t NumberOfRows, std::size_t NumberOfColumns>
class BenchmarkMatrix {
    ComparisonColumn<AMatrix::Matrix<double, NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mAMatrixColumn;
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mEigenColumn;
#else
    EmptyComparisonColumn<AMatrix::Matrix<double, NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mEigenColumn;
#endif
#if defined(AMATRIX_COMPARE_WITH_UBLAS)
    UblasComparisonColumn<boost::numeric::ublas::bounded_matrix<double,
                              NumberOfRows, NumberOfColumns>,
        NumberOfRows, NumberOfColumns>
        mUblasColumn;
#else
    EmptyComparisonColumn<AMatrix::Matrix<double,
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

    ~BenchmarkMatrix() = default;
    void Run() {
        std::cout << "C = A + B";
        mAMatrixColumn.MeasureSumTime();
        mEigenColumn.MeasureSumTime();
        if (!mEigenColumn.CheckResult(mAMatrixColumn.GetResult()))
            std::cout << "(Failed!)";
        mUblasColumn.MeasureSumTime();
        if (!mUblasColumn.CheckResult(mAMatrixColumn.GetResult()))
            std::cout << "(Failed!)";
        std::cout << std::endl;

        std::cout << "C = A * B";
        mAMatrixColumn.MeasureMultTime();
        mEigenColumn.MeasureMultTime();
        if (!mEigenColumn.CheckResult(mAMatrixColumn.GetResult()))
            std::cout << "(Failed!)";
        mUblasColumn.MeasureMultTime();
        if (!mUblasColumn.CheckResult(mAMatrixColumn.GetResult()))
            std::cout << "(Failed!)";
        std::cout << std::endl;

        std::cout << "C = A * B * A";
        mAMatrixColumn.MeasureABAMultTime();
        mEigenColumn.MeasureABAMultTime();
        if (!mEigenColumn.CheckResult(mAMatrixColumn.GetResult()))
            std::cout << "(Failed!)";
        mUblasColumn.MeasureABAMultTime();
        if (!mUblasColumn.CheckResult(mAMatrixColumn.GetResult()))
            std::cout << "(Failed!)";
        std::cout << std::endl;

        // std::cout << "AMatrix : " << mAMatrixColumn.GetResult() << std::endl;
        // std::cout << "Eigen   : " << mEigenColumn.GetResult() << std::endl;

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

    BenchmarkMatrix<12, 12> benchmark_12_12;
    benchmark_12_12.Run();

    BenchmarkMatrix<16, 16> benchmark_16_16;
    benchmark_16_16.Run();

    return 0;
}
