#pragma once

#include "matrix.h"
#include "sparse_graph.h"

namespace AMatrix {

template <typename TDataType>
class CSRMatrixStorage {
    std::size_t _size1;
    std::size_t _size2;
    std::size_t _non_zeros_size;
    Matrix<std::size_t, dynamic, 1> _row_indices;
    Matrix<std::size_t, dynamic, 1> _column_indices;
    Matrix<TDataType, dynamic, 1> _values;
    TDataType _zero;

   public:
    using data_type = TDataType;
    using indices_vector = Matrix<std::size_t, dynamic, 1>;
    using values_vector = Matrix<data_type, dynamic, 1>;

    CSRMatrixStorage(std::size_t TheSize1, std::size_t TheSize2, std::size_t TheNonZerosSize = 0)
        : _size1(TheSize1),
          _size2(TheSize2),
          _non_zeros_size(TheNonZerosSize),
          _row_indices(TheSize1 + 1),
          _column_indices(TheNonZerosSize),
          _values(TheNonZerosSize),
          _zero() {
        _row_indices.fill(std::size_t());
    }

    CSRMatrixStorage(SparseGraph const& TheGraph)
        : _size1(TheGraph.size1()),
          _size2(TheGraph.size2()),
          _non_zeros_size(TheGraph.non_zeros_size()),
          _row_indices(_size1 + 1),
          _column_indices(_non_zeros_size),
          _values(_non_zeros_size),
          _zero() {

        _row_indices[0] = 0;
        if (_size1 == 0)
            return;
        _values.fill(TDataType());
        std::size_t index = 0;

        for (std::size_t i = 0; i < _size1; i++) {
            _row_indices[i + 1] = _row_indices[i] + TheGraph.row_size(i);
            for (auto& j : TheGraph.row_connectivities(i)) {
                _column_indices[index++] = j;
            }
        }
    }

    TDataType const& operator()(std::size_t i, std::size_t j) const { return at(i, j); }

    TDataType& set(std::size_t i, std::size_t j, TDataType Value) {
        std::size_t next_row_index = _row_indices[i + 1];
        for (std::size_t index = _row_indices[i]; index < next_row_index; index++)
            if (_column_indices[index] == j) {
                _values[index] = Value;
                return _values[index];
            }

        return _zero;
    }

    TDataType& insert(std::size_t i, std::size_t j, TDataType Value) {
        std::size_t next_row_index = _row_indices[i + 1];
        for (std::size_t index = _row_indices[i]; index < next_row_index; index++)
            if (_column_indices[index] == j) {
                _values[index] = Value;
                return _values[index];
            }

        return insert_new_item(i, j, Value);
    }

    TDataType const& at(std::size_t i, std::size_t j) const {
        std::size_t next_row_index = _row_indices[i + 1];
        for (std::size_t index = _row_indices[i]; index < next_row_index; index++)
            if (_column_indices[index] == j)
                return _values[index];

        return _zero;
    }

    std::size_t size1() const { return _size1; }

    std::size_t size2() const { return _size2; }

    std::size_t size() const { return _size1 * _size2; }

    std::size_t non_zeros_size() const { return _non_zeros_size; }
    Matrix<std::size_t, dynamic, 1> const& row_indices() const { return _row_indices; };
    Matrix<std::size_t, dynamic, 1> const& column_indices() const { return _column_indices; };
    Matrix<TDataType, dynamic, 1> const& values() const { return _values; };

    class non_zero_iterator {
        CSRMatrixStorage& _storage;
        std::size_t _index;
        std::size_t _row_index;

       public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = TDataType;
        using difference_type = std::size_t;
        using pointer = TDataType*;
        using reference = TDataType&;

        non_zero_iterator(CSRMatrixStorage& TheStorage, std::size_t TheRowIndex, std::size_t TheIndex)
            : _storage(TheStorage), _index(TheIndex), _row_index(TheRowIndex) {}

        non_zero_iterator& operator++() {
            _index++;
            return *this;
        }
        non_zero_iterator operator++(int) {
            non_zero_iterator old = *this;
            ++(*this);
            return old;
        }
        bool operator==(non_zero_iterator const& other) const { return _index == other._index; }
        bool operator!=(non_zero_iterator other) const { return !(*this == other); }
        reference operator*() const { return _storage._values[_index]; }

        std::size_t index1() {
            while ((_storage._row_indices[_row_index + 1]) <= _index && (_row_index < _storage.size1()))
                _row_index++;
            return _row_index;
        }
        std::size_t index2() { return _storage._column_indices[_index]; }
    };

    non_zero_iterator begin() { return non_zero_iterator(*this, 0, 0); }
    non_zero_iterator end() { return non_zero_iterator(*this, size1(), _non_zeros_size); }

   private:
    TDataType& insert_new_item(std::size_t I, std::size_t J, TDataType const& Value) {
        const std::size_t position = _row_indices[I + 1];  // Inserting at the end of the row to move less

        for (std::size_t index = I + 1; index < _size1 + 1; index++)
            _row_indices[index]++;

        insert_in_position(_column_indices, position, J);
        insert_in_position(_values, position, Value);

        _non_zeros_size++;

        return _values[_row_indices[I + 1] - 1];
    }

    template <typename TVectorType, typename TValueType>
    void insert_in_position(TVectorType& TheVector, std::size_t Position, TValueType const& Value) {
        std::size_t new_size = _row_indices[_size1];

        if (new_size > TheVector.size()) {
            TVectorType temp_vector(new_size);

            for (std::size_t index = 0; index < Position; index++)
                temp_vector[index] = TheVector[index];

            temp_vector[Position] = Value;

            for (std::size_t index = Position + 1; index < new_size; index++)
                temp_vector[index] = TheVector[index - 1];

            TheVector.swap(temp_vector);
        } else {
            for (std::size_t index = new_size - 1; index >= Position; index--)
                TheVector[index] = TheVector[index - 1];

            TheVector[Position] = Value;
        }
    }
};
}  // namespace AMatrix