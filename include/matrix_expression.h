#pragma once

#include <iostream>

namespace AMatrix {
constexpr std::size_t dynamic = 0;

template <typename TExpressionType>
class MatrixExpression {

   public:
    // using value_type = TExpressionType::value_type;
    MatrixExpression() {}

    MatrixExpression(MatrixExpression const& Other) = default;

    MatrixExpression(MatrixExpression&& Other) = default;

    MatrixExpression& operator=(MatrixExpression const& Other) = default;

    MatrixExpression& operator=(MatrixExpression&& Other) = default;

    TExpressionType& expression() { return *static_cast<TExpressionType*>(this); }
    TExpressionType const& expression() const {
        return *static_cast<const TExpressionType* const>(this);
    }

    TExpressionType& noalias() { return expression(); }
};


template <typename TExpressionType>
class TransposeMatrix : public MatrixExpression<TransposeMatrix<TExpressionType>> {
    TExpressionType const& mOriginal;

   public:
    using data_type = typename TExpressionType::data_type;
    TransposeMatrix() = delete;

    TransposeMatrix(TExpressionType const& Original)
        : mOriginal(Original) {}

    inline data_type const& operator()(std::size_t i, std::size_t j) const {
        return mOriginal(j, i);
    }

    inline std::size_t size1() const { return mOriginal.size2(); }
    inline std::size_t size2() const { return mOriginal.size1(); }
};


template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class ZeroMatrix : public MatrixExpression<ZeroMatrix<TDataType, TSize1, TSize2>> {
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