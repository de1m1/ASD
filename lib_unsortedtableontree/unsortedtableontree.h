#pragma once
#include "itable.h"
#include "binarytree.h"
#include <utility>

template<typename TKey, typename TVal>
class UnsortedTableOnTree : public ITable<TKey, TVal> {
private:
    Tree<TKey, TVal> _tree;
public:
    ~UnsortedTableOnTree() {}
    UnsortedTableOnTree() {}

    void insert(const TKey& Key, const TVal& Val) override;
    TVal& find(const TKey& Key) override;
    void erase(const TKey& Key) override;
    ostream& print(ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool contains(const TKey& Key) const noexcept override;
    void replace(const TKey& Key, const TVal& Val) override;

};

template<typename TKey, typename TVal>
void UnsortedTableOnTree<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {
    _tree.insert(Key, Val);
}

template<typename TKey, typename TVal>
TVal& UnsortedTableOnTree<TKey, TVal>::find(const TKey& Key) {
    TVal* ptr = _tree.find_ptr(Key);

    if (!ptr)
        throw std::runtime_error("Key not found");

    return *ptr;
}

template<typename TKey, typename TVal>
void UnsortedTableOnTree<TKey, TVal>::erase(const TKey& Key) {

    if (!contains(Key))
        throw std::runtime_error("Key not found");

    _tree.erase(Key);
}

template<typename TKey, typename TVal>
bool UnsortedTableOnTree<TKey, TVal>::contains(const TKey& Key) const noexcept {

    return _tree.find_ptr(Key) != nullptr;
}

template<typename TKey, typename TVal>
void UnsortedTableOnTree<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {

    find(Key) = Val;
}

template<typename TKey, typename TVal>
ostream& UnsortedTableOnTree<TKey, TVal>::print(ostream& out) const noexcept {

    const_cast<Tree<TKey, TVal>&>(_tree).print_W();

    return out;
}

template<typename TKey, typename TVal>
bool UnsortedTableOnTree<TKey, TVal>::is_empty() const noexcept {
    return _tree.empty();
}