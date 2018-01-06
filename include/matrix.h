#pragma once

// A matrix Library to be simple and fast

#include "matrix_expression.h"

namespace AMatrix {

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class MatrixStorage
    : public MatrixExpression<MatrixStorage<TDataType, TSize1, TSize2>> {
    TDataType _data[TSize1 * TSize2];

   public:
    MatrixStorage() {}

    explicit MatrixStorage(std::size_t TheSize1, std::size_t TheSize2) {}

    explicit MatrixStorage(TDataType const& InitialValue) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = InitialValue;
    }

    MatrixStorage(MatrixStorage const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
    }

    MatrixStorage(MatrixStorage&& Other) = default;

    template <typename TExpressionType>
    explicit MatrixStorage(MatrixExpression<TExpressionType> const& Other)
        : MatrixStorage(Other.expression()) {}

    template <typename TOtherMatrixType>
    explicit MatrixStorage(TOtherMatrixType const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
    }

    explicit MatrixStorage(std::initializer_list<TDataType> InitialValues) {
        std::size_t position = 0;
        for (auto& i : InitialValues) {
            _data[position++] = i;
        }
    }

    explicit MatrixStorage(std::initializer_list<std::initializer_list<TDataType>> InitialRows) {
        std::size_t position = 0;
        for (auto& i_row : InitialRows) {
            for(auto i : i_row)
                _data[position++] = i;
        }
    }

    template <typename TExpressionType>
    MatrixStorage& operator=(MatrixExpression<TExpressionType> const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other.expression()(i, j);
        return *this;
    }

    template <typename TOtherMatrixType>
    MatrixStorage& operator=(TOtherMatrixType const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
        return *this;
    }

    MatrixStorage& operator=(MatrixStorage const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
        return *this;
    }

    MatrixStorage& operator=(MatrixStorage&& Other) = default;

    TDataType& operator()(std::size_t i, std::size_t j) { return at(i, j); }

    TDataType const& operator()(std::size_t i, std::size_t j) const {
        return at(i, j);
    }

    TDataType& at(std::size_t i, std::size_t j) {
        return _data[i * TSize2 + j];
    }

    TDataType const& at(std::size_t i, std::size_t j) const {
        return _data[i * TSize2 + j];
    }

    static constexpr std::size_t size1() { return TSize1; }

    static constexpr std::size_t size2() { return TSize2; }

    static constexpr std::size_t size() { return TSize1 * TSize2; }

    TDataType* data() { return _data; }

    TDataType const* data() const { return _data; }
};

template <typename TDataType>
class MatrixStorage<TDataType, dynamic, dynamic>
    : public MatrixExpression<MatrixStorage<TDataType, dynamic, dynamic>> {
    std::size_t _size1;
    std::size_t _size2;
    TDataType* _data;

   public:
    MatrixStorage() = delete;

    MatrixStorage(std::size_t TheSize1, std::size_t TheSize2)
        : _size1(TheSize1), _size2(TheSize2) {
        _data = new TDataType[size()];
    }

    explicit MatrixStorage(std::size_t TheSize1, std::size_t TheSize2,
        TDataType const& InitialValue)
        : _size1(TheSize1), _size2(TheSize2) {
        _data = new TDataType[size()];
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = InitialValue;
    }

    MatrixStorage(MatrixStorage const& Other)
        : _size1(Other.size1()), _size2(Other.size2()) {
        _data = new TDataType[size()];
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
    }

    MatrixStorage(MatrixStorage&& Other)
        : _size1(Other.size1()), _size2(Other.size2()), _data(Other._data) {
        Other._data = nullptr;
    }

    explicit MatrixStorage(std::initializer_list<std::initializer_list<TDataType>> InitialRows): _size1(0), _size2(0), _data(nullptr) {
        const std::size_t size1 = InitialRows.size();
        if (size1 == 0) return;
        const std::size_t size2 = InitialRows.begin()->size();
        if(size2 == 0) return;
        _size1 = size1;
        _size2 = size2;
        _data = new TDataType[size()];
        std::size_t position = 0;
        for (auto& i_row : InitialRows) {
            for(auto i : i_row)
                _data[position++] = i;
        }
    }

    virtual ~MatrixStorage() {
        if (_data)
            delete[] _data;
    }

    template <typename TExpressionType>
    explicit MatrixStorage(MatrixExpression<TExpressionType> const& Other)
        : MatrixStorage(Other.expression()) {}

    template <typename TOtherMatrixType>
    explicit MatrixStorage(TOtherMatrixType const& Other)
        : _size1(Other.size1()), _size2(Other.size2()) {
        _data = new TDataType[size()];
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
    }

    template <typename TExpressionType>
    MatrixStorage& operator=(MatrixExpression<TExpressionType> const& Other) {
        auto& other_expression = Other.expression();
        std::size_t new_size =
            other_expression.size1() * other_expression.size2();
        if (size() != new_size) {
            delete[] _data;
            _data = new TDataType[new_size];
        }
        _size1 = other_expression.size1();
        _size2 = other_expression.size2();

        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other.expression()(i, j);
        return *this;
    }

    template <typename TOtherMatrixType>
    MatrixStorage& operator=(TOtherMatrixType const& Other) {
        std::size_t new_size = Other.size1() * Other.size2();
        if (size() != new_size) {
            delete[] _data;
            _data = new TDataType[new_size];
        }
        _size1 = Other.size1();
        _size2 = Other.size2();

        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
        return *this;
    }

    MatrixStorage& operator=(MatrixStorage const& Other) {
        std::size_t new_size = Other.size1() * Other.size2();
        if (size() != new_size) {
            delete[] _data;
            _data = new TDataType[new_size];
        }
        _size1 = Other.size1();
        _size2 = Other.size2();

        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
        return *this;
    }

    MatrixStorage& operator=(MatrixStorage&& Other) {
        if (_data)
            delete[] _data;

        _size1 = Other.size1();
        _size2 = Other.size2();
        _data = Other._data;
        Other._data = nullptr;

        return *this;
    }

    TDataType& operator()(std::size_t i, std::size_t j) { return at(i, j); }

    TDataType const& operator()(std::size_t i, std::size_t j) const {
        return at(i, j);
    }

    TDataType& at(std::size_t i, std::size_t j) {
        return _data[i * _size2 + j];
    }

    TDataType const& at(std::size_t i, std::size_t j) const {
        return _data[i * _size2 + j];
    }

    std::size_t size1() const { return _size1; }

    std::size_t size2() const { return _size2; }

    std::size_t size() const { return _size1 * _size2; }

    TDataType* data() { return _data; }

    TDataType const* data() const { return _data; }
};

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix : public MatrixStorage<TDataType, TSize1, TSize2> {
   public:
    using data_type = TDataType;
    using base_type = MatrixStorage<TDataType, TSize1, TSize2>;
    using base_type::at;
    using base_type::size1;
    using base_type::size2;

    Matrix() {}

    explicit Matrix(std::size_t TheSize1, std::size_t TheSize2)
        : base_type(TheSize1, TheSize2) {}

    explicit Matrix(TDataType const& InitialValue) : base_type(InitialValue) {}

    Matrix(Matrix const& Other) : base_type(Other) {}

    Matrix(Matrix&& Other) : base_type(Other) {}

    template <typename TExpressionType>
    explicit Matrix(MatrixExpression<TExpressionType> const& Other)
        : base_type(Other) {}

    template <typename TOtherMatrixType>
    explicit Matrix(TOtherMatrixType const& Other) : base_type(Other) {}

    explicit Matrix(std::initializer_list<TDataType> InitialValues)
        : base_type(InitialValues) {}

    explicit Matrix(std::initializer_list<std::initializer_list<TDataType>> InitialRows)
        : base_type(InitialRows) {}

    template <typename TOtherMatrixType>
    Matrix& operator=(TOtherMatrixType const& Other) {
        base_type::operator=(Other);
        return *this;
    }

    Matrix& operator=(Matrix const& Other) {
        base_type::operator=(Other);
        return *this;
    }

    Matrix& operator=(Matrix&& Other) {
        base_type::operator=(Other);
        return *this;
    }

    friend bool operator==(Matrix const& First, Matrix const& Second) {
        for (std::size_t i = 0; i < First.size(); i++)
            if (First._data[i] != Second._data[i])
                return false;
        return true;
    }

    Matrix& operator+=(Matrix const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) += Other(i, j);

        return *this;
    }

    Matrix& operator-=(Matrix const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) -= Other(i, j);

        return *this;
    }

    friend Matrix operator*(
        TDataType const& TheScalar, Matrix const& TheMatrix) {
        Matrix result(TheMatrix.size1(), TheMatrix.size2());
        const TDataType* __restrict second_data = TheMatrix.data();
        TDataType* __restrict result_data = result.data();
        for (std::size_t i = 0; i < TheMatrix.size(); ++i)
            *result_data++ = TheScalar * (*second_data++);

        return result;
    }

    friend Matrix operator*(
        Matrix const& TheMatrix, TDataType const& TheScalar) {
        return TheScalar * TheMatrix;
    }

    Matrix& noalias() { return *this; }

    TransposeMatrix<Matrix<TDataType, TSize1, TSize2>> transpose() {
        return TransposeMatrix<Matrix<TDataType, TSize1, TSize2>>(*this);
    }
};

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
bool operator!=(Matrix<TDataType, TSize1, TSize2> const& First,
    Matrix<TDataType, TSize1, TSize2> const& Second) {
    return !(First == Second);
}

template <typename TDataType, std::size_t TSize1, std::size_t TSize2,
    std::size_t SecondNumberOfColumns>
inline Matrix<TDataType, TSize1, SecondNumberOfColumns> operator*(
    Matrix<TDataType, TSize1, TSize2> const& First,
    Matrix<TDataType, TSize2, SecondNumberOfColumns> const& Second) {
    Matrix<TDataType, TSize1, SecondNumberOfColumns> result;
    for (std::size_t i = 0; i < TSize1; i++)
        for (std::size_t j = 0; j < SecondNumberOfColumns; j++) {
            TDataType temp = TDataType();
            for (std::size_t k = 0; k < TSize2; k++)
                temp += First(i, k) * Second(k, j);

            result(i, j) = temp;
        }

    return result;
}

template <typename TDataType>
inline Matrix<TDataType, 0, 0> operator*(Matrix<TDataType, 0, 0> const& First,
    Matrix<TDataType, 0, 0> const& Second) {
    Matrix<TDataType, 0, 0> result(First.size1(), Second.size2());
    for (std::size_t i = 0; i < First.size1(); i++)
        for (std::size_t j = 0; j < Second.size2(); j++) {
            TDataType temp = TDataType();
            for (std::size_t k = 0; k < First.size2(); k++)
                temp += First(i, k) * Second(k, j);

            result(i, j) = temp;
        }

    return result;
}

template <typename TExpressionType1, typename TExpressionType2>
inline Matrix<typename TExpressionType1::data_type, dynamic, dynamic> operator*(
    TExpressionType1 const& First, TExpressionType2 const& Second) {
    auto const& first_expression = First.expression();
    auto const& second_expression = Second.expression();
    Matrix<typename TExpressionType1::data_type, 0, 0> result(
        first_expression.size1(), second_expression.size2());
    for (std::size_t i = 0; i < first_expression.size1(); i++)
        for (std::size_t j = 0; j < second_expression.size2(); j++) {
            typename TExpressionType1::data_type temp =
                typename TExpressionType1::data_type();
            for (std::size_t k = 0; k < first_expression.size2(); k++)
                temp += first_expression(i, k) * second_expression(k, j);

            result(i, j) = temp;
        }

    return result;
}

/// output stream function
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
inline std::ostream& operator<<(std::ostream& rOStream,
    Matrix<TDataType, TSize1, TSize2> const& TheMatrix) {
    rOStream << "{";
    for (std::size_t i = 0; i < TSize1; i++) {
        for (std::size_t j = 0; j < TSize2; j++)
            rOStream << TheMatrix(i, j) << ",";
        rOStream << std::endl;
    }
    rOStream << "}";

    return rOStream;
}
}  // namespace AMatrix
