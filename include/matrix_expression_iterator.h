#pragma once

#include <iterator>
#include "access_category.h"

namespace AMatrix {

template <typename TDataType, typename TExpressionType, std::size_t TCategory>
class ExpressionRandomAccessIterator
    : public std::iterator<std::random_access_iterator_tag, TDataType> {

    TExpressionType& _expression;
    std::size_t _i;
    std::size_t _j;
    const std::size_t _stride_i;
    const std::size_t _stride_j;

public:

    template <typename TBaseExpression>
    ExpressionRandomAccessIterator(
        TBaseExpression& Expression,
        std::size_t StartI, std::size_t StartJ,
        std::size_t StrideI, std::size_t StrideJ)
    : _expression(Expression)
    , _i(StartI)
    , _j(StartJ)
    , _stride_i(StrideI)
    , _stride_j(StrideJ) {
    }
};

template <typename TDataType, typename TExpressionType>
class ExpressionRandomAccessIterator<TDataType, TExpressionType, row_major_access>
    : public std::iterator<std::random_access_iterator_tag, TDataType> {

    TDataType* _data;
    const std::size_t _stride;

public:

    template <typename TBaseExpression>
    ExpressionRandomAccessIterator(
        TBaseExpression& Expression,
        std::size_t StartI, std::size_t StartJ,
        std::size_t StrideI, std::size_t StrideJ)
    : _data(&Expression(StartI,StartJ))
    , _stride(StrideJ + StrideI*Expression.size2()) {
    }


};

}