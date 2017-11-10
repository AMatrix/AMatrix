#pragma once

#include <algorithm>
#include <array>

// A matrix Library to be simple and fast
// By Pooyan

namespace AMatrix {

template <typename TDataType, std::size_t TSize1, std::size_t TSize2>
class Matrix {
    TDataType _data[TSize1 * TSize2];

   public:
    using value_type = TDataType;
    Matrix() {}
    explicit Matrix(TDataType const& InitialValue) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = InitialValue;
    }

    Matrix(Matrix const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
    }

    Matrix(Matrix&& Other) = default;

    template <typename TOtherMatrixType>
    explicit Matrix(TOtherMatrixType const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
    }

    template <typename TOtherMatrixType>
    Matrix& operator=(TOtherMatrixType const& Other) {
        for (std::size_t i = 0; i < size1(); i++)
            for (std::size_t j = 0; j < size2(); j++)
                at(i, j) = Other(i, j);
        return *this;
    }

    Matrix& operator=(Matrix const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
        return *this;
    }

    Matrix& operator=(Matrix&& Other) = default;

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

    constexpr std::size_t size1() const { return TSize1; }

    constexpr std::size_t size2() const { return TSize2; }

    constexpr std::size_t size() const { return TSize1 * TSize2; }

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

    TDataType* data() { return _data; }

    TDataType const* data() const { return _data; }
};

// Zero matrix
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

// Zero matrix
template <typename TMatrixType>
class TransposeMatrix {
    TMatrixType const& mOriginal;

   public:
    TransposeMatrix() = delete;

    TransposeMatrix(TMatrixType const& Original) : mOriginal(Original) {}

    inline typename TMatrixType::value_type operator()(
        std::size_t i, std::size_t j) const {
        return mOriginal(j, i);
    }

    inline std::size_t size1() const { return mOriginal.size2(); }
    inline std::size_t size2() const { return mOriginal.size1(); }
};

template <typename TMatrixType>
TransposeMatrix<TMatrixType> Transpose(TMatrixType const& OriginalMatrix) {
    return TransposeMatrix<TMatrixType>(OriginalMatrix);
}

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
