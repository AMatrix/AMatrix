#pragma once

#include <vector>
#include <unordered_set>

namespace AMatrix {

class SparseGraph {
    std::size_t _size1;
    std::size_t _size2;
    std::vector<std::unordered_set<std::size_t>> _connectivities;

   public:
    SparseGraph(std::size_t TheSize1, std::size_t TheSize2)
        : _size1(TheSize1), _size2(TheSize2), _connectivities(TheSize1) {}

    void insert(std::size_t I, std::size_t J) { _connectivities[I].insert(J); }

    std::size_t row_size(std::size_t I) const { return _connectivities[I].size(); }
};
}  // namespace AMatrix
