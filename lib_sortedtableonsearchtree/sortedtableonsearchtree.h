#pragma once
#include "itable.h"
#include "binarysearchtree.h"
#include <utility>
#include <stdexcept>
#include <ostream>

template<typename TKey, typename TVal>
class SortedTableOnSearchTree : public ITable<TKey, TVal> {

    BSTree<TKey, TVal> _tree;

public:

    ~SortedTableOnSearchTree() {}
    SortedTableOnSearchTree() {}

    void insert(const TKey& Key, const TVal& Val) override;
    TVal& find(const TKey& Key) override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool contains(const TKey& Key) const noexcept override;
    void replace(const TKey& Key, const TVal& Val) override;
};

template<typename TKey, typename TVal>
void SortedTableOnSearchTree<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {
    _tree.insert(Key, Val);
}

template<typename TKey, typename TVal>
TVal& SortedTableOnSearchTree<TKey, TVal>::find(const TKey& Key) {
    return _tree.find(Key);
}

template<typename TKey, typename TVal>
void SortedTableOnSearchTree<TKey, TVal>::erase(const TKey& Key) {
    _tree.erase(Key);
}

template<typename TKey, typename TVal>
bool SortedTableOnSearchTree<TKey, TVal>::contains(const TKey& Key) const noexcept {
    return _tree.contains(Key);
}

template<typename TKey, typename TVal>
bool SortedTableOnSearchTree<TKey, TVal>::is_empty() const noexcept {
    return _tree.empty();
}

template<typename TKey, typename TVal>
void SortedTableOnSearchTree<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {
    _tree.find(Key) = Val;
}

template<typename TKey, typename TVal>
std::ostream& SortedTableOnSearchTree<TKey, TVal>::print(std::ostream& out) const noexcept {

    const_cast<BSTree<TKey, TVal>&>(_tree).print_D2();
    return out;
}