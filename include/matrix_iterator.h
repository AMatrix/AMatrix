#include <iterator>

namespace AMatrix {

template <typename TDataType>
class RandomAccessIterator
    : public std::iterator<std::random_access_iterator_tag, TDataType> {
    TDataType* _p_data;

   public:
    RandomAccessIterator() = default;
    RandomAccessIterator(RandomAccessIterator const& Other) = default;
    RandomAccessIterator(RandomAccessIterator&& Other) = default;
    RandomAccessIterator(TDataType* pData) : _p_data(pData) {}

    RandomAccessIterator& operator=(
        RandomAccessIterator const& Other) = default;

    bool operator==(const RandomAccessIterator& Other) const {
        return _p_data == Other._p_data;
    }

    bool operator!=(const RandomAccessIterator& Other) const {
        return _p_data != Other._p_data;
    }

    TDataType const& operator*() const { return *_p_data; }

    TDataType& operator*() { return *_p_data; }

    TDataType* const operator->() const { return _p_data; }

    TDataType* operator->() { return _p_data; }

    RandomAccessIterator& operator++() {
        ++_p_data;
        return *this;
    }

    RandomAccessIterator operator++(int) {
        RandomAccessIterator temp(*this);
        ++_p_data;
        return temp;
    }

    RandomAccessIterator& operator--() {
        --_p_data;
        return *this;
    }

    RandomAccessIterator operator--(int) {
        RandomAccessIterator temp(*this);
        --_p_data;
        return temp;
    }

    RandomAccessIterator& operator+=(std::size_t Offset) {
        _p_data += Offset;
        return *this;
    }

    RandomAccessIterator& operator-=(std::size_t Offset) {
        _p_data -= Offset;
        return *this;
    }


};

}  // namespace AMatrix