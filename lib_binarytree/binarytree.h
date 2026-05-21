#pragma once
#include <iostream>
#include "queue.h"

template<typename TKey, typename TVal>
class Tree{
private:

    struct Node {
        std::pair<TKey, TVal> val;
        Node* left;
        Node* right;

        Node(const std::pair<TKey, TVal>& v): val(v), left(nullptr), right(nullptr) {}
    };

    Node* _root;

    void print_D1_rec(Node* cur); // CLR
    void print_D2_rec(Node* cur); // LСR
    void print_D3_rec(Node* cur); // LRС
    void clear_tree(Node* cur);

    template<typename Func>
    void bfs(Func f) const;

    int count;

public:

    Tree() : _root(nullptr), count(0) {}
    ~Tree() { clear_tree(_root);}

    void insert(const TKey& key, const TVal& val);
    TVal* find(const TKey& key) const;
    void erase(const TKey& key);
    bool contains(const TKey& key, TVal& val);
    bool empty() const { return _root == nullptr; }

    void print_D1() { print_D1_rec(_root);}
    void print_D2() { print_D2_rec(_root);}
    void print_D3() { print_D3_rec(_root);}
    void print_W();
};


template<typename TKey, typename TVal>
template<typename Func>
void Tree<TKey, TVal>::bfs(Func f) const{

    if (!_root) return;

    Queue<Node*> q (1 + count/2);
    q.push(_root);

    while (!q.is_empty()) {

        Node* cur = q.front();
        q.pop();

        f(cur);

        if (cur->left)
            q.push(cur->left);

        if (cur->right)
            q.push(cur->right);
    }
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::print_D1_rec(Node* cur){
    if (!cur) return;

    std::cout << cur->val.first << " ";
    print_D1_rec(cur->left);
    print_D1_rec(cur->right);
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::print_D2_rec(Node* cur){
    if (!cur) return;

    print_D2_rec(cur->left);
    std::cout << cur->val.first << " ";
    print_D2_rec(cur->right);
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::print_D3_rec(Node* cur){
    if (!cur) return;

    print_D3_rec(cur->left);
    print_D3_rec(cur->right);
    std::cout << cur->val.first << " ";
}

template<typename TKey, typename TVal>
inline void Tree<TKey, TVal>::clear_tree(Node* cur){
    if (!cur) return;

    clear_tree(cur->left);
    clear_tree(cur->right);
    delete cur;
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::insert(const TKey& key, const TVal& val) {
    Node* node = new Node({ key, val });

    if (!_root) {
        _root = node;
        count++;
        return;
    }

    bool inserted = false;

    bfs([&](Node* cur) {

        if (inserted) return;

        if (!cur->left) {
            cur->left = node;
            inserted = true;
            return;
        }

        if (!cur->right) {
            cur->right = node;
            inserted = true;
            return;
        }
        });

    count++;
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::erase(const TKey& key) {
    if (!_root) return;

    Node* Del = nullptr;
    Node* L = nullptr;
    Node* P = nullptr;

    bfs([&](Node* cur) {

        if (cur->val.first == key)
            Del = cur;

        if (cur->left) {
            P = cur;
            L = cur->left;
        }

        if (cur->right) {
            P = cur;
            L = cur->right;
        }
        });

    if (!Del) return;

    if (L == _root) {
        delete _root;
        _root = nullptr;
        count--;
        return;
    }

    Del->val = L->val;

    if (P->right == L)
        P->right = nullptr;
    else
        P->left = nullptr;

    delete L;
    count--;
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::print_W() {

    bfs([](Node* cur) {
        std::cout << cur->val.second << " ";
        });
}

template<typename TKey, typename TVal>
inline TVal* Tree<TKey, TVal>::find(const TKey& key) const{
    TVal* result = nullptr;

	bfs([&](Node* cur) { // [&] - захват по ссылке, чтобы иметь доступ к result
        if (cur->val.first == key)
            result = &cur->val.second;
        });

    return result;
}

template<typename TKey, typename TVal>
bool Tree<TKey, TVal>::contains(const TKey& key, TVal& val) {

    bool found = false;

	bfs([&](Node* cur) { // [&] - захват по ссылке, чтобы иметь доступ к found и val

        if (cur->val.first == key) {
            val = cur->val.second;
            found = true;
        }

        });

    return found;
}