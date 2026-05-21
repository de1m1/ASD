#pragma once
#include "itable.h"
#include "avltree.h"
#include <utility>
#include <stdexcept>
#include <ostream>

template<typename TKey, typename TVal>
class SortedTableOnAVLTree : public ITable<TKey, TVal> {

    AVLTree<TKey, TVal> _tree;

public:

    ~SortedTableOnAVLTree() {}
    SortedTableOnAVLTree() {}

    void insert(const TKey& Key, const TVal& Val) override;
    TVal& find(const TKey& Key) override;
    void erase(const TKey& Key) override;
    std::ostream& print(std::ostream& out) const noexcept;
    bool is_empty() const noexcept;
    bool contains(const TKey& Key) const noexcept;
    void replace(const TKey& Key, const TVal& Val);

};

template<typename TKey, typename TVal>
void SortedTableOnAVLTree<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {
    _tree.insert(Key, Val);
}

template<typename TKey, typename TVal>
TVal& SortedTableOnAVLTree<TKey, TVal>::find(const TKey& Key) {
    return _tree.find(Key);
}

template<typename TKey, typename TVal>
void SortedTableOnAVLTree<TKey, TVal>::erase(const TKey& Key) {
    _tree.erase(Key);
}

template<typename TKey, typename TVal>
bool SortedTableOnAVLTree<TKey, TVal>::contains(const TKey& Key) const noexcept {
    return _tree.contains(Key);
}

template<typename TKey, typename TVal>
bool SortedTableOnAVLTree<TKey, TVal>::is_empty() const noexcept {
    return _tree.empty();
}

template<typename TKey, typename TVal>
void SortedTableOnAVLTree<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {
    _tree.find(Key) = Val;
}

template<typename TKey, typename TVal>
std::ostream& SortedTableOnAVLTree<TKey, TVal>::print(std::ostream& out) const noexcept {

    const_cast<AVLTree<TKey, TVal>&>(_tree).print_D2();
    return out;
}