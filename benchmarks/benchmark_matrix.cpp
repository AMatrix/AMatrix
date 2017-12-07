#include <iostream>
#include <cmath>
#include <string>

#include "timer.h"
#include "matrix.h"

#if defined(AMATRIX_COMPARE_WITH_EIGEN)
#include "Eigen/Dense"
#endif

#if defined(AMATRIX_COMPARE_WITH_UBLAS)
#include <boost/numeric/ublas/matrix.hpp>
#endif

#define AMATRIX_MEASURE_ABC_OPERATION(name, operation)                   \
    void name() {                                                        \
        TMatrixType A(TSize1, TSize2);                                   \
        TMatrixType B(TSize1, TSize2);                                   \
        initialize(A);                                                   \
        initialize(B);                                                   \
        Timer timer;                                                     \
        for (std::size_t i_repeat = 0; i_repeat < mRepeat; i_repeat++) { \
            operation                                                    \
        }                                                                \
        auto elapsed = timer.elapsed().count();                          \
        std::cout << "\t\t" << elapsed;                                  \
    }

#define AMATRIX_MEASURE_ABCD_OPERATION(name, operation)                   \
    void name() {                                                         \
        TMatrixType A(TSize1, TSize2);                                    \
        TMatrixType B(TSize1, TSize2);                                    \
        initialize(A);                                                    \
        initializeInverse(B);                                             \
        initializeInverse(D);                                             \
        Timer timer;                                                      \
        for (std::size_t i_repeat = 0; i_repeat < mRepeat / (2 * TSize2); \
             i_repeat++) {                                                \
            operation                                                     \
        }                                                                 \
        auto elapsed = timer.elapsed().count();                           \
        std::cout << "\t\t" << elapsed;                                   \
    }

template <typename TMatrixType, std::size_t TSize1, std::size_t TSize2>
class ComparisonColumn {
   protected:
    static constexpr std::size_t mRepeat =
        static_cast<std::size_t>(1e8 / (TSize1 * TSize2));

    TMatrixType C;
    TMatrixType D;
    std::string mColumnName;

    void initialize(TMatrixType& TheMatrix) {
        for (std::size_t i = 0; i < TSize1; i++)
            for (std::size_t j = 0; j < TSize2; j++)
                TheMatrix(i, j) = j + 1.00;
    }

    void initializeInverse(TMatrixType& TheMatrix) {
        for (std::size_t i = 0; i < TSize1; i++)
            for (std::size_t j = 0; j < TSize2; j++)
                TheMatrix(i, j) = 1.00 / (i + 1);
    }

   public:
    ComparisonColumn() = delete;

    ComparisonColumn(std::string ColumnName) 
        : C(TSize1, TSize2),
          D(TSize1, TSize2), mColumnName(ColumnName) {
        initialize(C);
    }
    std::string const& GetColumnName() { return mColumnName; }
    TMatrixType& GetResult() { return C; }

    template <typename TMatrixType2>
    bool CheckResult(TMatrixType2 const& Reference) {
        constexpr double tolerance = 1e-12;
        for (std::size_t i = 0; i < TSize1; i++)
            for (std::size_t j = 0; j < TSize2; j++)
                if (std::abs(C(i, j) != Reference(i, j)) > tolerance) {
                    std::cout << " " << C(i, j) << " != " << Reference(i, j);
                    return false;
                }

        return true;
    }

    AMATRIX_MEASURE_ABC_OPERATION(MeasureSumTime,C.noalias() = A + B; B.noalias() = C;)

    AMATRIX_MEASURE_ABCD_OPERATION(MeasureMultTime,C.noalias() = D * A; D.noalias() = B;)

    AMATRIX_MEASURE_ABCD_OPERATION(MeasureABAMultTime, C.noalias() = A * TMatrixType(D * A); D.noalias() = B;)

    AMATRIX_MEASURE_ABCD_OPERATION(MeasureATransposeBAMultTime,C.noalias() = A.transpose() * TMatrixType(D * A); D.noalias() = B;)

};


#if defined(AMATRIX_COMPARE_WITH_UBLAS)
using namespace boost::numeric::ublas;
template <typename TMatrixType, std::size_t TSize1,
    std::size_t TSize2>

class UblasComparisonColumn
    : public ComparisonColumn<TMatrixType, TSize1, TSize2> {
   public:
    using BaseType =
        ComparisonColumn<TMatrixType, TSize1, TSize2>;

    UblasComparisonColumn(std::string ColumnName)
        : ComparisonColumn<TMatrixType, TSize1, TSize2>(
              ColumnName) {}


    AMATRIX_MEASURE_ABC_OPERATION(MeasureSumTime, noalias(BaseType::C) =  A + B; noalias(B) = BaseType::C;)
    AMATRIX_MEASURE_ABCD_OPERATION(MeasureMultTime,noalias(BaseType::C) = prod(BaseType::D, A); noalias(BaseType::D) = B;)
    AMATRIX_MEASURE_ABCD_OPERATION(MeasureABAMultTime, noalias(BaseType::C) = prod(A, TMatrixType(prod(BaseType::D, A))); noalias(BaseType::D) = B;)
    AMATRIX_MEASURE_ABCD_OPERATION(MeasureATransposeBAMultTime, noalias(BaseType::C) = prod(trans(A), TMatrixType(prod(BaseType::D, A)));noalias(BaseType::D) = B;)

};
#endif

template <typename TMatrixType, std::size_t TSize1,
    std::size_t TSize2>
class EmptyComparisonColumn
    : public ComparisonColumn<TMatrixType, TSize1, TSize2> {
   public:
    EmptyComparisonColumn(std::string ColumnName)
        : ComparisonColumn<TMatrixType, TSize1, TSize2>("") {}
    void MeasureSumTime() { std::cout << "\t\t"; }
    void MeasureMultTime() { std::cout << "\t\t"; }
    void MeasureABAMultTime() { std::cout << "\t\t"; }
    void MeasureATransposeBAMultTime() { std::cout << "\t\t"; }

    template <typename TMatrixType2>
    bool CheckResult(TMatrixType2 const& Reference) {
        return true;
    }
};

#define RUN_BENCHMARK(name, function)                          \
    std::cout << name;                                         \
    mAMatrixColumn.function();                                 \
    mEigenColumn.function();                                   \
    if (!mEigenColumn.CheckResult(mAMatrixColumn.GetResult())) \
        std::cout << "(Failed!)";                              \
    mUblasColumn.function();                                   \
    if (!mUblasColumn.CheckResult(mAMatrixColumn.GetResult())) \
        std::cout << "(Failed!)";                              \
    std::cout << std::endl;

template <std::size_t TSize1, std::size_t TSize2>
class BenchmarkMatrix {
    ComparisonColumn<AMatrix::Matrix<double, TSize1, TSize2>,
        TSize1, TSize2>
        mAMatrixColumn;
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<Eigen::Matrix<double, TSize1, TSize2>,
        TSize1, TSize2>
        mEigenColumn;
#else
    EmptyComparisonColumn<
        AMatrix::Matrix<double, TSize1, TSize2>, TSize1,
        TSize2>
        mEigenColumn;
#endif
#if defined(AMATRIX_COMPARE_WITH_UBLAS)
    UblasComparisonColumn<boost::numeric::ublas::bounded_matrix<double,
                              TSize1, TSize2>,
        TSize1, TSize2>
        mUblasColumn;
#else
    EmptyComparisonColumn<
        AMatrix::Matrix<double, TSize1, TSize2>, TSize1,
        TSize2>
        mUblasColumn;
#endif
   public:
    BenchmarkMatrix()
        : mAMatrixColumn("AMatrix"),
          mEigenColumn("Eigen"),
          mUblasColumn("Ublas") {
        std::cout << "Benchmark[" << TSize1 << "," << TSize2
                  << "]";
        std::cout << "\t\t" << mAMatrixColumn.GetColumnName();
        std::cout << "\t\t" << mEigenColumn.GetColumnName();
        std::cout << "\t\t" << mUblasColumn.GetColumnName();
        std::cout << std::endl;
    }

    ~BenchmarkMatrix() = default;
    void Run() {
        RUN_BENCHMARK("C = A + B", MeasureSumTime)
        RUN_BENCHMARK("C = A * B", MeasureMultTime)
        RUN_BENCHMARK("C = A * B * A", MeasureABAMultTime)
        RUN_BENCHMARK("C = A^T * B * A", MeasureATransposeBAMultTime)

        std::cout << std::endl;
    }
};

template <std::size_t TSize1, std::size_t TSize2>
class BenchmarkDynamicMatrix {
    ComparisonColumn<AMatrix::Matrix<double, 0, 0>, TSize1,
        TSize2>
        mAMatrixColumn;
#if defined(AMATRIX_COMPARE_WITH_EIGEN)
    ComparisonColumn<
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>, TSize1,
        TSize2>
        mEigenColumn;
#else
    EmptyComparisonColumn<
        AMatrix::Matrix<double, TSize1, TSize2>, TSize1,
        TSize2>
        mEigenColumn;
#endif
#if defined(AMATRIX_COMPARE_WITH_UBLAS)
    UblasComparisonColumn<boost::numeric::ublas::matrix<double>,
        TSize1, TSize2>
        mUblasColumn;
#else
    EmptyComparisonColumn<
        AMatrix::Matrix<double, TSize1, TSize2>, TSize1,
        TSize2>
        mUblasColumn;
#endif
   public:
    BenchmarkDynamicMatrix()
        : mAMatrixColumn("AMatrix"),
          mEigenColumn("Eigen"),
          mUblasColumn("Ublas") {
        std::cout << "Benchmark[" << TSize1 << "," << TSize2
                  << "]";
        std::cout << "\t\t" << mAMatrixColumn.GetColumnName();
        std::cout << "\t\t" << mEigenColumn.GetColumnName();
        std::cout << "\t\t" << mUblasColumn.GetColumnName();
        std::cout << std::endl;
    }

    ~BenchmarkDynamicMatrix() = default;
    void Run() {
        RUN_BENCHMARK("C = A + B", MeasureSumTime)
        RUN_BENCHMARK("C = A * B", MeasureMultTime)
        RUN_BENCHMARK("C = A * B * A", MeasureABAMultTime)
//        RUN_BENCHMARK("C = A^T * B * A", MeasureATransposeBAMultTime)

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

    BenchmarkDynamicMatrix<3, 3> dynamic_bechmark_3_3;
    dynamic_bechmark_3_3.Run();

    BenchmarkDynamicMatrix<4, 4> dynamic_benchmark_4_4;
    dynamic_benchmark_4_4.Run();

    BenchmarkDynamicMatrix<6, 6> dynamic_benchmark_6_6;
    dynamic_benchmark_6_6.Run();

    BenchmarkDynamicMatrix<12, 12> dynamic_benchmark_12_12;
    dynamic_benchmark_12_12.Run();

    BenchmarkDynamicMatrix<16, 16> dynamic_benchmark_16_16;
    dynamic_benchmark_16_16.Run();

    return 0;
}
