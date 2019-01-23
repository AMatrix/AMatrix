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

    TDataType* _p_data;
    const std::size_t _stride;

public:
    using base_type = std::iterator<std::random_access_iterator_tag, TDataType>;
    using typename base_type::difference_type;
    ExpressionRandomAccessIterator() = default;
    ExpressionRandomAccessIterator(ExpressionRandomAccessIterator const& Other) = default;
    ExpressionRandomAccessIterator(ExpressionRandomAccessIterator&& Other) = default;

    template <typename TBaseExpression>
    ExpressionRandomAccessIterator(
        TBaseExpression& Expression,
        std::size_t StartI, std::size_t StartJ,
        std::size_t StrideI, std::size_t StrideJ)
    : _p_data(&Expression(StartI,StartJ))
    , _stride(StrideJ + StrideI*Expression.size2()) {
    }

    template <typename TOtherDataType>
    ExpressionRandomAccessIterator(
        ExpressionRandomAccessIterator<TOtherDataType, TExpressionType, row_major_access> const& Other)
    : _p_data(Other.operator->())
    , _stride(Other._stride) {}

    ExpressionRandomAccessIterator& operator=(
        ExpressionRandomAccessIterator const& Other) = default;

    bool operator==(const ExpressionRandomAccessIterator& Other) const {
        return _p_data == Other._p_data;
    }

    bool operator!=(const ExpressionRandomAccessIterator& Other) const {
        return _p_data != Other._p_data;
    }

    TDataType const& operator*() const { return *_p_data; }

    TDataType& operator*() { return *_p_data; }

    TDataType* const operator->() const { return _p_data; }

    TDataType* operator->() { return _p_data; }

    ExpressionRandomAccessIterator& operator++() {
        _p_data += _stride;
        return *this;
    }

    ExpressionRandomAccessIterator operator++(int) {
        ExpressionRandomAccessIterator temp(*this);
        _p_data += _stride;
        return temp;
    }

    ExpressionRandomAccessIterator& operator--() {
        _p_data -= _stride;
        return *this;
    }

    ExpressionRandomAccessIterator operator--(int) {
        ExpressionRandomAccessIterator temp(*this);
        _p_data -= _stride;
        return temp;
    }

    ExpressionRandomAccessIterator& operator+=(difference_type Offset) {
        _p_data += Offset;
        return *this;
    }

    ExpressionRandomAccessIterator& operator-=(difference_type Offset) {
        _p_data -= Offset;
        return *this;
    }

    friend ExpressionRandomAccessIterator operator+(
        ExpressionRandomAccessIterator First, difference_type Second) {
        First += Second;
        return First;
    }

    friend ExpressionRandomAccessIterator operator+(
        difference_type First, ExpressionRandomAccessIterator Second) {
        Second += First;
        return Second;
    }

    friend ExpressionRandomAccessIterator operator-(
        ExpressionRandomAccessIterator First, difference_type Second) {
        First -= Second;
        return First;
    }

    friend difference_type operator-(
        ExpressionRandomAccessIterator const& First, ExpressionRandomAccessIterator const& Second) {
        return First._p_data - Second._p_data;
    }

    friend bool operator<(
        ExpressionRandomAccessIterator const& First, ExpressionRandomAccessIterator const& Second) {
        return First._p_data < Second._p_data;
    }

    friend bool operator>(
        ExpressionRandomAccessIterator const& First, ExpressionRandomAccessIterator const& Second) {
        return Second < First;
    }
    friend bool operator<=(
        ExpressionRandomAccessIterator const& First, ExpressionRandomAccessIterator const& Second) {
        return !(First > Second);
    }
    friend bool operator>=(
        ExpressionRandomAccessIterator const& First, ExpressionRandomAccessIterator const& Second) {
        return !(First < Second);
    }

};

}