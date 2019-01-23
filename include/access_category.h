#pragma once

#include <cstddef>

namespace AMatrix {
constexpr std::size_t dynamic = 0;
constexpr std::size_t row_major_access = 1;
constexpr std::size_t column_major_access = 2;
constexpr std::size_t unordered_access = 3;

template <std::size_t TCategory1, std::size_t TCategory2>
class AccessTrait {
   public:
    static constexpr std::size_t category = unordered_access;
};

template <>
class AccessTrait<row_major_access, row_major_access> {
   public:
    static constexpr std::size_t category = row_major_access;
};

}