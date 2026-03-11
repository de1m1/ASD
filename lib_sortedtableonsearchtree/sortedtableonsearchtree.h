#pragma once
#include "itable.h"
#include "binarysearchtree.h"
#include <utility>

template<typename TKey, typename TVal>
class SortedTableOnSearchTree : public ITable<TKey, TVal> {

    BSTree<TKey, TVal> _tree;

public:

    ~SortedTableOnSearchTree() {}
    SortedTableOnSearchTree() {}

    void insert(const TKey& Key, const TVal& Val) override;
    TVal find(const TKey& Key) override;
    void erase(const TKey& Key) override;
    ostream& print(ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool contains(const TKey& Key) const noexcept override;
    void replace(const TKey& Key, const TVal& Val) override;
};

template<typename TKey, typename TVal>
void SortedTableOnSearchTree<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {
    _tree.insert(Key, Val);
}

template<typename TKey, typename TVal>
TVal SortedTableOnSearchTree<TKey, TVal>::find(const TKey& Key) {

    TVal val;

    if (!_tree.find(Key, val))
        throw std::runtime_error("Key not found");

    return val;
}

template<typename TKey, typename TVal>
void SortedTableOnSearchTree<TKey, TVal>::erase(const TKey& Key) {
    _tree.erase(Key);
}

template<typename TKey, typename TVal>
bool SortedTableOnSearchTree<TKey, TVal>::contains(const TKey& Key) const noexcept {

    TVal val;
    return const_cast<BSTree<TKey, TVal>&>(_tree).find(Key, val);
}

template<typename TKey, typename TVal>
bool SortedTableOnSearchTree<TKey, TVal>::is_empty() const noexcept {
    return _tree.empty();
}

template<typename TKey, typename TVal>
void SortedTableOnSearchTree<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {
    _tree.insert(Key, Val);
}

template<typename TKey, typename TVal>
ostream& SortedTableOnSearchTree<TKey, TVal>::print(ostream& out) const noexcept {

    const_cast<BSTree<TKey, TVal>&>(_tree).print_D2();
    return out;
}