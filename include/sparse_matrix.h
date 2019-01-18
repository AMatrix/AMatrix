#pragma once

#include "sparse_matrix_storage.h" 

namespace AMatrix {

template<typename TStorageType>
class SparseMatrix : public TStorageType {
   public:
    using base_type = TStorageType;
    using base_type::size;
    using base_type::size1;
    using base_type::size2;

    SparseMatrix(std::size_t TheSize1, std::size_t TheSize2)
        : base_type(TheSize1, TheSize2) {}

    SparseMatrix(std::size_t TheSize1, std::size_t TheSize2,
        std::size_t TheNumberOfNonZeros)
        : base_type(TheSize1, TheSize2, TheNumberOfNonZeros) {}
};
}
