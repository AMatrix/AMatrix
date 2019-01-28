#pragma once

#include "sparse_matrix_storage.h"

namespace AMatrix {

template <typename TStorageType>
class SparseMatrix : public TStorageType {
   public:
    using base_type = TStorageType;
    using base_type::size;
    using base_type::size1;
    using base_type::size2;

    SparseMatrix(std::size_t TheSize1, std::size_t TheSize2) : base_type(TheSize1, TheSize2) {}

    SparseMatrix(std::size_t TheSize1, std::size_t TheSize2, std::size_t TheNumberOfNonZeros)
        : base_type(TheSize1, TheSize2, TheNumberOfNonZeros) {}

    SparseMatrix(SparseGraph const& TheGraph)
        : base_type(TheGraph) {}
};

template <typename TDataType>
void Product(SparseMatrix<CSRMatrixStorage<TDataType>> const& A, Matrix<TDataType, dynamic, 1> const& X,
    Matrix<TDataType, dynamic, 1>& Result) {
    std::size_t index = 0;
    for (std::size_t i = 0; i < A.size1(); i++) {
        TDataType temp = TDataType();
        std::size_t next_row_index = A.row_indices()[i + 1];
        while (index < next_row_index) {
            temp += A.values()[index] * X[A.column_indices()[index]];
            index++;
		}
        Result[i] = temp;
	}
}
}  // namespace AMatrix
