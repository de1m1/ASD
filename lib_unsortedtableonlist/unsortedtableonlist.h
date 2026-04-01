#pragma once

#include "itable.h"
#include "list.h"
#include <utility>
#include <stdexcept>

template<typename TKey, typename TVal>
class UnsortedTableOnList : public ITable<TKey, TVal> {
private:
    List<std::pair<TKey, TVal>> _list;

public:
    UnsortedTableOnList() {}
    ~UnsortedTableOnList() {}

    void insert(const TKey& Key, const TVal& Val) override;
    TVal& find(const TKey& Key) override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool contains(const TKey& Key) const noexcept override;
    void replace(const TKey& Key, const TVal& Val) override;
};

template<typename TKey, typename TVal>
void UnsortedTableOnList<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {
    _list.push_back(std::make_pair(Key, Val));
}

template<typename TKey, typename TVal>
TVal& UnsortedTableOnList<TKey, TVal>::find(const TKey& Key) {
    for (auto it = _list.begin(); it != _list.end(); ++it) {
        if (it->first == Key)
            return it->second;
    }
    throw std::runtime_error("Key not found");
}

template<typename TKey, typename TVal>
void UnsortedTableOnList<TKey, TVal>::erase(const TKey& Key) {
    for (auto it = _list.begin(); it != _list.end(); ++it) {
        if (it->first == Key) {
            _list.erase(it);
            return;
        }
    }
}

template<typename TKey, typename TVal>
bool UnsortedTableOnList<TKey, TVal>::contains(const TKey& Key) const noexcept {
    for (auto it = const_cast<List<std::pair<TKey, TVal>>&>(_list).begin();
        it != const_cast<List<std::pair<TKey, TVal>>&>(_list).end(); ++it) {

        if (it->first == Key)
            return true;
    }
    return false;
}

template<typename TKey, typename TVal>
void UnsortedTableOnList<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {
    for (auto it = _list.begin(); it != _list.end(); ++it) {
        if (it->first == Key) {
            it->second = Val;
            return;
        }
    }
    throw std::runtime_error("Key not found");
}

template<typename TKey, typename TVal>
bool UnsortedTableOnList<TKey, TVal>::is_empty() const noexcept {
    return _list.empty();
}

template<typename TKey, typename TVal>
std::ostream& UnsortedTableOnList<TKey, TVal>::print(std::ostream& out) const noexcept {

    for (auto it = const_cast<List<std::pair<TKey, TVal>>&>(_list).begin();
        it != const_cast<List<std::pair<TKey, TVal>>&>(_list).end(); ++it) {

        out << "Key: " << it->first
            << ", Value: " << it->second << std::endl;
    }

    return out;
}