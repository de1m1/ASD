#pragma once
#include "itable.h"
#include "tvector.h"
#include <utility>

template<typename TKey, typename TVal>
class SortedTableOnVec : public ITable<TKey, TVal> {
	TVector<std::pair<TKey, TVal>>_rows;
	int binary_search(const TKey& key) const;
public:
	~SortedTableOnVec() {}
	SortedTableOnVec() {}

    void insert(const TKey& Key, const TVal& Val) override;
    TVal find(const TKey& Key) override;
    void erase(const TKey& Key) override;
    ostream& print(ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool contains(const TKey& Key) const noexcept override;
    void replace(const TKey& Key, const TVal& Val) override;
};

template<typename TKey, typename TVal>
int SortedTableOnVec<TKey, TVal>::binary_search(const TKey& key) const {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (_rows[mid].first == key)
            return mid;

        if (_rows[mid].first < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

template<typename TKey, typename TVal>
void SortedTableOnVec<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {

    if (contains(Key))
        throw std::runtime_error("Key already exists");

    size_t pos = 0;

    while (pos < _rows.size() && _rows[pos].first < Key)
        ++pos;

    _rows.push_back(std::make_pair(Key, Val));

    for (size_t i = _rows.size() - 1; i > pos; --i) {
        _rows[i] = _rows[i - 1];
    }

    _rows[pos] = std::make_pair(Key, Val);
}

template<typename TKey, typename TVal>
TVal SortedTableOnVec<TKey, TVal>::find(const TKey& Key) {
    int index = binary_search(Key);
    if (index == -1)
        throw std::runtime_error("Key not found");

    return _rows[index].second;
}

template<typename TKey, typename TVal>
void SortedTableOnVec<TKey, TVal>::erase(const TKey& Key) {

    int index = binary_search(Key);
    if (index == -1)
        return;

    for (size_t i = index; i < _rows.size() - 1; ++i) {
        _rows[i] = _rows[i + 1];
    }

    _rows.pop_back();
}

template<typename TKey, typename TVal>
void SortedTableOnVec<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {

    int index = binary_search(Key);
    if (index == -1)
        throw std::runtime_error("Key not found");

    _rows[index].second = Val;
}

template<typename TKey, typename TVal>
bool SortedTableOnVec<TKey, TVal>::contains(const TKey& Key) const noexcept {
    return binary_search(Key) != -1;
}

template<typename TKey, typename TVal>
ostream& SortedTableOnVec<TKey, TVal>::print(ostream& out) const noexcept {
    for (size_t i = 0; i < _rows.size(); ++i) {
        out << "Key: " << _rows[i].first
            << ", Value: " << _rows[i].second << endl;
    }
    return out;
}

template<typename TKey, typename TVal>
bool SortedTableOnVec<TKey, TVal>::is_empty() const noexcept {
    return _rows.size() == 0;
}