#pragma once

// A matrix Library to be simple and fast

#include "matrix_expression.h"

namespace AMatrix {

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
class MatrixStorage {
    TDataType _data[TSize1 * TSize2];

   public:
    MatrixStorage() {}
    explicit MatrixStorage(TDataType const& InitialValue) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = InitialValue;
    }

    MatrixStorage(MatrixStorage const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
    }

    MatrixStorage(MatrixStorage&& Other) = default;

    template <typename TOtherMatrixType>
    explicit MatrixStorage(TOtherMatrixType const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
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

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix : public MatrixStorage<TDataType, TSize1, TSize2> {
   public:
    using value_type = TDataType;
    using base_type = MatrixStorage<TDataType, TSize1, TSize2>;
    using base_type::size1;
    using base_type::size2;
    using base_type::at;

    Matrix() {}
    explicit Matrix(TDataType const& InitialValue) : base_type(InitialValue) {}

    Matrix(Matrix const& Other) : base_type(Other) {}

    Matrix(Matrix&& Other) : base_type(Other) {}

    template <typename TOtherMatrixType>
    explicit Matrix(TOtherMatrixType const& Other) : base_type(Other) {}

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
        Matrix result;
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

    TransposeMatrix<TDataType, TSize1, TSize2> transpose() {  // Eigen benchmark
        return TransposeMatrix<TDataType, TSize1, TSize2>(*this);
    }

    TransposeMatrix<TDataType, TSize1, TSize2> Transpose() {
        return TransposeMatrix<TDataType, TSize1, TSize2>(*this);
    }
};

template <typename TDataType>
class Matrix<TDataType, 0, 0> {
    std::size_t _size1;
    std::size_t _size2;
    TDataType* _data;

   public:
    using value_type = TDataType;
    Matrix(std::size_t TheSize1, std::size_t TheSize2)
        : _size1(TheSize1), _size2(TheSize2) {
        _data = new TDataType[size()];
    }
    explicit Matrix(std::size_t TheSize1, std::size_t TheSize2,
        TDataType const& InitialValue)
        : _size1(TheSize1), _size2(TheSize2) {
        _data = new TDataType[size()];
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = InitialValue;
    }

    Matrix(Matrix const& Other) : _size1(Other.size1()), _size2(Other.size2()) {
        _data = new TDataType[size()];
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
    }

    Matrix(Matrix&& Other)
        : _size1(Other.size1()), _size2(Other.size2()), _data(Other._data) {
        Other._data = nullptr;
    }

    ~Matrix() {
        if (_data)
            delete[] _data;
    }

    template <typename TOtherMatrixType>
    explicit Matrix(TOtherMatrixType const& Other)
        : _size1(Other.size1()), _size2(Other.size2()) {
        _data = new TDataType[size()];
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
    }

    template <typename TOtherMatrixType>
    Matrix& operator=(TOtherMatrixType const& Other) {
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

    Matrix& operator=(Matrix const& Other) {
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

    Matrix& operator=(Matrix&& Other) {
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
        return _data[i * size2() + j];
    }

    TDataType const& at(std::size_t i, std::size_t j) const {
        return _data[i * size2() + j];
    }

    std::size_t size1() const { return _size1; }

    std::size_t size2() const { return _size2; }

    std::size_t size() const { return _size1 * _size2; }

    friend bool operator==(Matrix const& First, Matrix const& Second) {
        if ((First.size1() != Second.size1()) ||
            (First.size2() != Second.size2()))
            return false;
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
        const TDataType* __restrict second_data = TheMatrix._data;
        TDataType* __restrict result_data = result._data;
        for (std::size_t i = 0; i < TheMatrix.size(); ++i)
            *result_data++ = TheScalar * (*second_data++);

        return result;
    }

    friend Matrix operator*(
        Matrix const& TheMatrix, TDataType const& TheScalar) {
        return TheScalar * TheMatrix;
    }

    Matrix& noalias() { return *this; }

    TransposeMatrix<TDataType, 0, 0> transpose() {  // Eigen benchmark
        return TransposeMatrix<TDataType, 0, 0>(*this);
    }

    TransposeMatrix<TDataType, 0, 0> Transpose() {
        return TransposeMatrix<TDataType, 0, 0>(*this);
    }

    TDataType* data() { return _data; }

    TDataType const* data() const { return _data; }
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

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
Matrix<TDataType, TSize1, TSize2> operator+(
    Matrix<TDataType, TSize1, TSize2> const& First,
    Matrix<TDataType, TSize1, TSize2> const& Second) {
    Matrix<TDataType, TSize1, TSize2> result;
    for (std::size_t i = 0; i < First.size1(); i++)
        for (std::size_t j = 0; j < First.size2(); j++)
            result(i, j) = First(i, j) + Second(i, j);

    return result;
}

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
Matrix<TDataType, TSize1, TSize2> operator-(
    Matrix<TDataType, TSize1, TSize2> const& First,
    Matrix<TDataType, TSize1, TSize2> const& Second) {
    Matrix<TDataType, TSize1, TSize2> result;
    for (std::size_t i = 0; i < First.size1(); i++)
        for (std::size_t j = 0; j < First.size2(); j++)
            result(i, j) = First(i, j) - Second(i, j);

    return result;
}

template <typename TDataType>
Matrix<TDataType, 0, 0> operator+(Matrix<TDataType, 0, 0> const& First,
    Matrix<TDataType, 0, 0> const& Second) {
    Matrix<TDataType, 0, 0> result(First.size1(), First.size2());
    for (std::size_t i = 0; i < First.size1(); i++)
        for (std::size_t j = 0; j < First.size2(); j++)
            result(i, j) = First(i, j) + Second(i, j);

    return result;
}

template <typename TDataType>
Matrix<TDataType, 0, 0> operator-(Matrix<TDataType, 0, 0> const& First,
    Matrix<TDataType, 0, 0> const& Second) {
    Matrix<TDataType, 0, 0> result(First.size1(), First.size2());
    for (std::size_t i = 0; i < First.size1(); i++)
        for (std::size_t j = 0; j < First.size2(); j++)
            result(i, j) = First(i, j) - Second(i, j);

    return result;
}

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

template <typename TMatrixType1, typename TMatrixType2>
inline Matrix<typename TMatrixType1::value_type, TMatrixType1::size1(),
    TMatrixType2::size2()>
operator*(TMatrixType1 const& First, TMatrixType2 const& Second) {
    Matrix<typename TMatrixType1::value_type, TMatrixType1::size1(),
        TMatrixType2::size2()>
        result;
    for (std::size_t i = 0; i < TMatrixType1::size1(); i++)
        for (std::size_t j = 0; j < TMatrixType2::size2(); j++) {
            typename TMatrixType1::value_type temp =
                typename TMatrixType1::value_type();
            for (std::size_t k = 0; k < TMatrixType1::size2(); k++)
                temp += First(i, k) * Second(k, j);

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
