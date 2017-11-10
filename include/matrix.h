#pragma once

#include <algorithm>
#include <array>

// A matrix Library to be simple and fast
// By Pooyan

namespace AMatrix {
template <typename DataType, std::size_t NumberOfRows, std::size_t NumberOfColumns>
class Matrix {
    DataType _data[NumberOfRows * NumberOfColumns];

   public:
    Matrix() {}
    explicit Matrix(DataType const& InitialValue) {
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

    Matrix& operator=(Matrix const& Other) {
        for (std::size_t i = 0; i < size(); i++)
            _data[i] = Other._data[i];
        return *this;
    }

    Matrix& operator=(Matrix && Other) = default;

    DataType& operator()(std::size_t i, std::size_t j) { return at(i, j); }

    DataType const& operator()(std::size_t i, std::size_t j) const { return at(i, j); }

    DataType& at(std::size_t i, std::size_t j) { return _data[i * NumberOfColumns + j]; }

    DataType const& at(std::size_t i, std::size_t j) const {
        return _data[i * NumberOfColumns + j];
    }

    constexpr std::size_t size1() const { return NumberOfRows; }

    constexpr std::size_t size2() const { return NumberOfColumns; }

    constexpr std::size_t size() const { return NumberOfRows * NumberOfColumns; }

    friend bool operator==(Matrix const& First, Matrix const& Second) {
        for (std::size_t i = 0; i < First.size(); i++)
            if (First._data[i] != Second._data[i])
                return false;
        return true;
    }

    Matrix& operator+=(Matrix const& Other) {

        for(int i = 0 ; i < size1() ; i++)
            for(int j = 0 ; j < size2() ; j++)
                at(i,j) += Other(i,j);

        return *this;
    }

    friend Matrix operator+(Matrix const& First, Matrix const& Second) {
        Matrix result;
        for(int i = 0 ; i < First.size1() ; i++)
            for(int j = 0 ; j < First.size2() ; j++)
                result(i,j) = First(i,j) + Second(i,j);

        return result;
    }

    friend Matrix operator-(Matrix const& First, Matrix const& Second) {
        Matrix result;
        const DataType* __restrict first_data = First._data;
        const DataType* __restrict second_data = Second._data;
        DataType* __restrict result_data = result._data;
        for (std::size_t i = 0; i < First.size(); ++i)
            *result_data++ = *first_data++ - *second_data++;

        return result;
    }

    template <std::size_t SecondNumberOfColumns>
    friend inline Matrix<DataType, NumberOfRows, SecondNumberOfColumns>
    operator*(Matrix const& First, Matrix<DataType, NumberOfColumns,
                                       SecondNumberOfColumns> const& Second) {
        Matrix<DataType, NumberOfRows, SecondNumberOfColumns> result;
        for (std::size_t i = 0; i < NumberOfRows; i++)
            for (std::size_t j = 0; j < SecondNumberOfColumns; j++) {
                DataType temp = DataType();
                for (std::size_t k = 0; k < NumberOfColumns; k++)
                    temp += First(i, k) * Second(k, j);

                result(i, j) = temp;
            }

        return result;
    }

    friend Matrix operator*(
        DataType const& TheScalar, Matrix const& TheMatrix) {
        Matrix result;
        const DataType* __restrict second_data = TheMatrix._data;
        DataType* __restrict result_data = result._data;
        for (std::size_t i = 0; i < TheMatrix.size(); ++i)
            *result_data++ = TheScalar * (*second_data++);

        return result;
    }

    friend Matrix operator*(
        Matrix const& TheMatrix, DataType const& TheScalar) {
        return TheScalar * TheMatrix;
    }

    Matrix& noalias() { return *this; }

    DataType* data() { return _data; }

    DataType const* data() const { return _data; }

   private:
    template <std::size_t TSize>
    inline static void ElementwiseMult(const DataType* __restrict A,
        const DataType* __restrict B, DataType* C) {
        for (std::size_t i = 0; i < TSize; ++i) {
            *(C++) += *(A++) * *(B++);
        }
    }
};

template <typename DataType, std::size_t NumberOfRows, std::size_t NumberOfColumns>
bool operator!=(Matrix<DataType, NumberOfRows, NumberOfColumns> const& First,
    Matrix<DataType, NumberOfRows, NumberOfColumns> const& Second) {
    return !(First == Second);
}

/// output stream function
template <typename DataType, std::size_t NumberOfRows, std::size_t NumberOfColumns>
inline std::ostream& operator<<(std::ostream& rOStream,
    Matrix<DataType, NumberOfRows, NumberOfColumns> const& TheMatrix) {
    rOStream << "{";
    for (std::size_t i = 0; i < NumberOfRows; i++) {
        for (std::size_t j = 0; j < NumberOfColumns; j++)
            rOStream << TheMatrix(i, j) << ",";
        rOStream << std::endl;
    }
    rOStream << "}";

    return rOStream;
}
}  // mamespace AMatrix
