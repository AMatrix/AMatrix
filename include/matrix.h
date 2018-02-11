#pragma once

// A matrix Library to be simple and fast

#include "matrix_expression.h"

namespace AMatrix {

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class MatrixStorage {
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
        auto i_data = _data;
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                *(i_data++) = Other(i, j);
    }

    explicit MatrixStorage(std::initializer_list<TDataType> InitialValues) {
        std::size_t position = 0;
        for (auto& i : InitialValues) {
            _data[position++] = i;
        }
    }

    template <typename TExpressionType>
    MatrixStorage& operator=(MatrixExpression<TExpressionType> const& Other) {
        auto i_data = _data;
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                *(i_data++) = Other.expression()(i, j);
        return *this;
    }

    template <typename TOtherMatrixType>
    MatrixStorage& operator=(TOtherMatrixType const& Other) {
        auto i_data = _data;
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                *(i_data++) = Other(i, j);
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

    TDataType& operator[](std::size_t i) { return at(i); }

    TDataType const& operator[](std::size_t i) const {
        return at(i);
    }

    TDataType& at(std::size_t i) {
        return _data[i];
    }

    TDataType const& at(std::size_t i) const {
        return _data[i];
    }

    static constexpr std::size_t size1() { return TSize1; }

    static constexpr std::size_t size2() { return TSize2; }

    static constexpr std::size_t size() { return TSize1 * TSize2; }

    TDataType* data() { return _data; }

    TDataType const* data() const { return _data; }
};

template <typename TDataType>
class MatrixStorage<TDataType, dynamic, dynamic> {
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

    explicit MatrixStorage(std::initializer_list<TDataType> InitialValues)
        : _size1(1), _size2(InitialValues.size()), _data(nullptr) {
        if (_size2 == 0)
            return;
        _data = new TDataType[size()];
        std::size_t position = 0;
        for (auto& i : InitialValues) {
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
        auto i_data = _data;
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                *(i_data++) = Other(i, j);
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

        auto i_data = _data;
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                *(i_data++) = Other.expression()(i, j);
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

        auto i_data = _data;
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                *(i_data++) = Other(i, j);
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

    TDataType& operator[](std::size_t i) { return at(i); }

    TDataType const& operator[](std::size_t i) const {
        return at(i);
    }

    TDataType& at(std::size_t i) {
        return _data[i];
    }

    TDataType const& at(std::size_t i) const {
        return _data[i];
    }

    std::size_t size1() const { return _size1; }

    std::size_t size2() const { return _size2; }

    std::size_t size() const { return _size1 * _size2; }

    TDataType* data() { return _data; }

    TDataType const* data() const { return _data; }
};

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix : public MatrixExpression<Matrix<TDataType, TSize1, TSize2>>,
               public MatrixStorage<TDataType, TSize1, TSize2> {
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

/// output stream function
template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
inline std::ostream& operator<<(std::ostream& rOStream,
    Matrix<TDataType, TSize1, TSize2> const& TheMatrix) {
    rOStream << "{";
    for (std::size_t i = 0; i < TheMatrix.size1(); i++) {
        for (std::size_t j = 0; j < TheMatrix.size2(); j++)
            rOStream << TheMatrix(i, j) << ",";
        rOStream << std::endl;
    }
    rOStream << "}";

    return rOStream;
}

template <typename TDataType>
using Matrix11 = Matrix<TDataType, 1, 1>;

template <typename TDataType>
using Matrix22 = Matrix<TDataType, 2, 2>;

template <typename TDataType>
using Matrix33 = Matrix<TDataType, 3, 3>;

template <typename TDataType>
using Matrix44 = Matrix<TDataType, 4, 4>;

template <typename TDataType>
using Matrix55 = Matrix<TDataType, 5, 5>;

template <typename TDataType>
using Matrix66 = Matrix<TDataType, 6, 6>;

template <typename TDataType>
using Matrix77 = Matrix<TDataType, 7, 7>;

template <typename TDataType>
using Matrix88 = Matrix<TDataType, 8, 8>;

template <typename TDataType>
using Matrix99 = Matrix<TDataType, 9, 9>;

template <typename TDataType, std::size_t TSize>
using Vector = Matrix<TDataType, TSize, 1>;

template <typename TDataType>
using Vector1 = Matrix<TDataType, 1, 1>;

template <typename TDataType>
using Vector2 = Matrix<TDataType, 2, 1>;

template <typename TDataType>
using Vector3 = Matrix<TDataType, 3, 1>;

template <typename TDataType>
using Vector4 = Matrix<TDataType, 4, 1>;

template <typename TDataType>
using Vector5 = Matrix<TDataType, 5, 1>;

template <typename TDataType>
using Vector6 = Matrix<TDataType, 6, 1>;

template <typename TDataType>
using Vector7 = Matrix<TDataType, 7, 1>;

template <typename TDataType>
using Vector8 = Matrix<TDataType, 8, 1>;

template <typename TDataType>
using Vector9 = Matrix<TDataType, 9, 1>;

template <typename TDataType, std::size_t TSize>
using RowVector = Matrix<TDataType, 1, TSize>;

template <typename TDataType>
using RowVector1 = Matrix<TDataType, 1, 1>;

template <typename TDataType>
using RowVector2 = Matrix<TDataType, 1, 2>;

template <typename TDataType>
using RowVector3 = Matrix<TDataType, 1, 3>;

template <typename TDataType>
using RowVector4 = Matrix<TDataType, 1, 4>;

template <typename TDataType>
using RowVector5 = Matrix<TDataType, 1, 5>;

template <typename TDataType>
using RowVector6 = Matrix<TDataType, 1, 6>;

template <typename TDataType>
using RowVector7 = Matrix<TDataType, 1, 7>;

template <typename TDataType>
using RowVector8 = Matrix<TDataType, 1, 8>;

template <typename TDataType>
using RowVector9 = Matrix<TDataType, 1, 9>;

template <typename TDataType>
using ZeroVector = ZeroMatrix<TDataType>;

}  // namespace AMatrix
