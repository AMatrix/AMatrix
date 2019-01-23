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
    TDataType _zero;
    static constexpr std::size_t _reserve_size = 1024;

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

    TDataType& operator()(std::size_t i, std::size_t j) { return at(i, j); }

    TDataType const& operator()(std::size_t i, std::size_t j) const { return at(i, j); }

    TDataType& at(std::size_t i, std::size_t j) {
        std::size_t next_row_index = _row_indices[i + 1];
        for (std::size_t index = _row_indices[i]; index < next_row_index; index++)
            if (_column_indices[index] == j)
                return _values[index];

        return insert_new_item(i, j, TDataType());
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

    class non_zero_iterator {
        CSRMatrixStorage& _storage;
        std::size_t _index;
        std::size_t _row_index;
		void step_front() {
            _index++;
            while ((_storage._row_indices[_row_index + 1]) < _index && (_row_index < _storage.size1()))
                _row_index++;
            return *this;
        }
       public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = TDataType;
        using difference_type = std::size_t;
        using pointer = TDataType*;
        using reference = TDataType&;

		non_zero_iterator(CSRMatrixStorage& TheStorage, std::size_t TheRowIndex, std::size_t TheIndex)
            : _storage(TheStorage), _index(TheIndex), _row_index(TheRowIndex) {}

        non_zero_iterator& operator++() { step_front(); }
        non_zero_iterator operator++(int) { step_front(); }
        bool operator==(non_zero_iterator const& other) const { return _index == other._index; }
        bool operator!=(non_zero_iterator other) const { return !(*this == other); }
        reference operator*() const { return _storage[_index]; }
	
    };

   private:
    TDataType& insert_new_item(std::size_t I, std::size_t J, TDataType const& Value) {

        const std::size_t position = _row_indices[I + 1]; // Inserting at the end of the row to move less

        for (std::size_t index = I + 1; index < _size1 + 1; index++)
            _row_indices[index]++;

		insert_in_position(_column_indices, position, J);
        insert_in_position(_values, position, Value);

        return _values[_row_indices[I + 1] - 1];
    }

	template <typename TVectorType>
    void insert_in_position(TVectorType& TheVector, std::size_t Position, TDataType const& Value) {
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