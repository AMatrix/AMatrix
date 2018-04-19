#include <iterator>

namespace AMatrix {

template <typename TDataType>
class random_access_iterator
    : public std::iterator<std::random_access_iterator_tag, TDataType> {
    TDataType* _p_data;

   public:
    random_access_iterator() = default;
    random_access_iterator(random_access_iterator const& Other) = default;
    random_access_iterator(random_access_iterator&& Other) = default;
    random_access_iterator(TDataType* pData) : _p_data(pData) {}

    random_access_iterator& operator=(
        random_access_iterator const& Other) = default;

    bool operator==(const random_access_iterator& Other) const {
        return _p_data == Other._p_data;
    }

    bool operator!=(const random_access_iterator& Other) const {
        return _p_data != Other._p_data;
    }

    TDataType const& operator*() const { return *_p_data; }

    TDataType& operator*() { return *_p_data; }

    TDataType* const operator->() const { return _p_data; }

    TDataType* operator->() { return _p_data; }

    random_access_iterator& operator++() {
        ++_p_data;
        return *this;
    }

    random_access_iterator operator++(int) {
        random_access_iterator temp(*this);
        ++_p_data;
        return temp;
    }

    random_access_iterator& operator--() {
        --_p_data;
        return *this;
    }

    random_access_iterator operator--(int) {
        random_access_iterator temp(*this);
        --_p_data;
        return temp;
    }

    random_access_iterator& operator+=(std::size_t Offset) {
        _p_data += Offset;
        return *this;
    }

    random_access_iterator& operator-=(std::size_t Offset) {
        _p_data -= Offset;
        return *this;
    }
};

}  // namespace AMatrix