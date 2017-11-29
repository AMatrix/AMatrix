#pragma once

#include <iostream>

namespace AMatrix {
constexpr std::size_t dynamic = 0;

template <typename TMatrixType, std::size_t TSize1, std::size_t TSize2>
class MatrixExpression {
    TMatrixType& derived() { return *static_cast<TMatrixType*>(this); }
    TMatrixType const& derived() const {
        return *static_cast<const TMatrixType* const>(this);
    }

   public:
    // using value_type = TMatrixType::value_type;
    MatrixExpression() {}

    MatrixExpression(MatrixExpression const& Other) = default;

    MatrixExpression(MatrixExpression&& Other) = default;

    MatrixExpression& operator=(MatrixExpression const& Other) = default;

    MatrixExpression& operator=(MatrixExpression&& Other) = default;

    // value_type& operator()(std::size_t i, std::size_t j) { return derived().at(i, j); }

    // value_type const& operator()(std::size_t i, std::size_t j) const {
    //     return derived().at(i, j);
    // }

    static constexpr std::size_t size1() { return TSize1; }

    static constexpr std::size_t size2() { return TSize2; }

    static constexpr std::size_t size() { return TSize1 * TSize2; }

    // friend bool operator==(Matrix const& First, Matrix const& Second) {
    //     for (std::size_t i = 0; i < First.size(); i++)
    //         if (First._data[i] != Second._data[i])
    //             return false;
    //     return true;
    // }

    TMatrixType& operator+=(MatrixExpression const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                derived().at(i, j) += Other.derived()(i, j);

        return derived();
    }

    TMatrixType& operator-=(MatrixExpression const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                derived().at(i, j) -= Other.derived()(i, j);

        return derived();
    }

    // friend Matrix operator*(
    //     TDataType const& TheScalar, Matrix const& TheMatrix) {
    //     Matrix result;
    //     const TDataType* __restrict second_data = TheMatrix._data;
    //     TDataType* __restrict result_data = result._data;
    //     for (std::size_t i = 0; i < TheMatrix.size(); ++i)
    //         *result_data++ = TheScalar * (*second_data++);

    //     return result;
    // }

    // friend Matrix operator*(
    //     Matrix const& TheMatrix, TDataType const& TheScalar) {
    //     return TheScalar * TheMatrix;
    // }

    TMatrixType& noalias() { return derived(); }

    // TransposeMatrix<value_type, TSize1, TSize2> transpose() {  // Eigen benchmark
    //     return TransposeMatrix<TDataType, TSize1, TSize2>(*this);
    // }
};


template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix;
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class TransposeMatrix : public Matrix<TDataType, TSize1, TSize2> {
    Matrix<TDataType, TSize1, TSize2> const& mOriginal;

   public:
    using value_type = TDataType;
    TransposeMatrix() = delete;

    TransposeMatrix(Matrix<TDataType, TSize1, TSize2> const& Original)
        : mOriginal(Original) {}

    inline value_type const& operator()(std::size_t i, std::size_t j) const {
        return mOriginal(j, i);
    }

    inline static constexpr std::size_t size1() {
        return Matrix<TDataType, TSize1, TSize2>::size2();
    }
    inline static constexpr std::size_t size2() {
        return Matrix<TDataType, TSize1, TSize2>::size1();
    }
};

template <typename TDataType>
class TransposeMatrix<TDataType, 0, 0> {
    Matrix<TDataType, 0, 0> const& mOriginal;

   public:
    using value_type = TDataType;
    TransposeMatrix() = delete;

    TransposeMatrix(Matrix<TDataType, 0, 0> const& Original)
        : mOriginal(Original) {}

    inline value_type const& operator()(std::size_t i, std::size_t j) const {
        return mOriginal(j, i);
    }

    inline std::size_t size1() { return mOriginal.size2(); }
    inline std::size_t size2() { return mOriginal.size1(); }
};

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class ZeroMatrix {
   public:
    using data_type = TDataType;

    ZeroMatrix() {}

    inline TDataType operator()(std::size_t i, std::size_t j) const {
        return 0.0;
    }

    inline constexpr std::size_t size1() const { return TSize1; }
    inline constexpr std::size_t size2() const { return TSize2; }
};

}  // namespace AMatrix