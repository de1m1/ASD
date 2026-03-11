#pragma once
#include <iostream>
#include "queue.h"
#include <sstream>


template<typename TKey, typename TVal>
class BSTree {
private:

    struct Node {
        std::pair<TKey, TVal> val;
        Node* left;
        Node* right;

        Node(const std::pair<TKey, TVal>& v) : val(v), left(nullptr), right(nullptr) {}
    };

    Node* _root;

    void print_D1_rec(Node* cur);
    void print_D2_rec(Node* cur);
    void print_D3_rec(Node* cur);
    void clear_tree(Node* cur);
    void to_string_rec(Node* cur, std::stringstream& ss) const{
        if (!cur) return;
        ss << cur->val.first << ": " << cur->val.second << "\n";
        to_string_rec(cur->left, ss);
        to_string_rec(cur->right, ss);
	}

    template<typename Func>
    void bfs(Func f);

    Node* find_pos(const TKey& key) const noexcept {

        Node* cur = _root;

        while (cur && cur->val.first != key) {

            if (key < cur->val.first)
                cur = cur->left;
            else
                cur = cur->right;
        }

        return cur;
    }
public:

    BSTree() : _root(nullptr) {}
    ~BSTree() { clear_tree(_root); }

    void insert(const TKey& key, const TVal& val);
    TVal& find(const TKey& key);
    void erase(const TKey& key);
    bool empty() const noexcept { return _root == nullptr; }
	std::string to_string() const noexcept;

    void print_D1() { print_D1_rec(_root); }
    void print_D2() { print_D2_rec(_root); }
    void print_D3() { print_D3_rec(_root); }
    void print_W();
};


template<typename TKey, typename TVal>
template<typename Func>
void BSTree<TKey, TVal>::bfs(Func f) {

    if (!_root) return;

    Queue<Node*> q;
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
void BSTree<TKey, TVal>::print_D1_rec(Node* cur) {
    if (!cur) return;

    std::cout << cur->val.first << " ";
    print_D1_rec(cur->left);
    print_D1_rec(cur->right);
}

template<typename TKey, typename TVal>
void BSTree<TKey, TVal>::print_D2_rec(Node* cur) {
    if (!cur) return;

    print_D2_rec(cur->left);
    std::cout << cur->val.first << " ";
    print_D2_rec(cur->right);
}

template<typename TKey, typename TVal>
void BSTree<TKey, TVal>::print_D3_rec(Node* cur) {
    if (!cur) return;

    print_D3_rec(cur->left);
    print_D3_rec(cur->right);
    std::cout << cur->val.first << " ";
}

template<typename TKey, typename TVal>
inline void BSTree<TKey, TVal>::clear_tree(Node* cur) {
    if (!cur) return;

    clear_tree(cur->left);
    clear_tree(cur->right);
    delete cur;
}

template<typename TKey, typename TVal>
void BSTree<TKey, TVal>::insert(const TKey& key, const TVal& val) {

    Node* node = new Node({ key, val });

    if (empty()) {
        _root = node;
        return;
    }

    Node* cur = _root;

    while (true) {

        if (key < cur->val.first) {

            if (!cur->left) {
                cur->left = node;
                return;
            }

            cur = cur->left;
        }
        else if (key > cur->val.first) {

            if (!cur->right) {
                cur->right = node;
                return;
            }

            cur = cur->right;
        }
        else {
            cur->val.second = val;
            delete node;
            return;
        }
    }
}

template<typename TKey, typename TVal>
TVal& BSTree<TKey, TVal>::find(const TKey& key) {

    Node* cur = _root;

    while (cur && cur->val.first != key) {

        if (key < cur->val.first)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (!cur)
        throw std::runtime_error("Key not found");

    return cur->val.second;
}

template<typename TKey, typename TVal>
void BSTree<TKey, TVal>::erase(const TKey& key) {

    Node* parent = nullptr;
    Node* cur = _root;

    while (cur && cur->val.first != key) {

        parent = cur;

        if (key < cur->val.first)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (!cur)
        return;

    // два ребёнка
    if (cur->left && cur->right) {

        Node* pred_parent = cur;
        Node* pred = cur->left;

        while (pred->right) {
            pred_parent = pred;
            pred = pred->right;
        }

        cur->val = pred->val;

        if (pred_parent == cur)
            pred_parent->left = pred->left;
        else
            pred_parent->right = pred->left;

        delete pred;
        return;
    }

    Node* child = cur->left ? cur->left : cur->right;

    if (!parent)
        _root = child;
    else if (parent->left == cur)
        parent->left = child;
    else
        parent->right = child;

    delete cur;
}
template<typename TKey, typename TVal>
std::string BSTree<TKey, TVal>::to_string() const noexcept {

    std::stringstream ss;

    to_string_rec(_root, ss);

    return ss.str();
}

template<typename TKey, typename TVal>
void BSTree<TKey, TVal>::print_W() {

    bfs([](Node* cur) {
        std::cout << cur->val.first << " ";
        });
}




