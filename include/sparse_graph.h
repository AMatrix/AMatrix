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

    std::size_t size1() const { return _size1; }

    std::size_t size2() const { return _size2; }

    std::size_t non_zeros_size() const {
        std::size_t result = 0;

        for (std::size_t i = 0; i < _size1; i++) {
            result += row_size(i);
        }
        return result;
    }

	std::unordered_set<std::size_t> const& row_connectivities(std::size_t I) const { return _connectivities[I]; }
};
}  // namespace AMatrix
