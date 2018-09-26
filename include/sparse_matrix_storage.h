#pragma once

#include "matrix.h"

namespace AMatrix {

template <typename TDataType>
class CSRMatrixStorage {
    std::size_t _size1;
    std::size_t _size2;
    std::size_t _non_zeros_size;
    Matrix<std::size_t, dynamic, 1> _row_indices;
    Matrix<std::size_t, dynamic, 1> _column_indices;
    Matrix<TDataType, dynamic, 1> _values;

   public:
    using data_type = TDataType;
    using indices_vector = Matrix<std::size_t, dynamic, 1>;
    using values_vector = Matrix<data_type, dynamic, 1>;

    CSRMatrixStorage(std::size_t TheSize1, std::size_t TheSize2,
        std::size_t TheNonZerosSize = 0)
        : _size1(TheSize1),
          _size2(TheSize2),
          _non_zeros_size(TheNonZerosSize),
          _row_indices(TheSize1),
          _column_indices(TheNonZerosSize),
          _values(TheNonZerosSize) {
	}

    TDataType& operator()(std::size_t i, std::size_t j) { return at(i, j); }

    TDataType const& operator()(std::size_t i, std::size_t j) const {
        return at(i, j);
    }

    TDataType& at(std::size_t i, std::size_t j) {
        std::size_t row_index = _row_indices[i];
        return _values[row_index];
    }

    TDataType const& at(std::size_t i, std::size_t j) const {
        return _values[i * _size2 + j];
    }

    std::size_t size1() const { return _size1; }

    std::size_t size2() const { return _size2; }

    std::size_t size() const { return _size1 * _size2; }
};
}  // namespace AMatrix