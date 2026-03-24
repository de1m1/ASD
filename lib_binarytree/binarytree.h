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

    void print_D1_rec(Node* cur); //CLR
    void print_D2_rec(Node* cur); // LNR
    void print_D3_rec(Node* cur); // LRN
    void clear_tree(Node* cur);

    template<typename Func>
    void bfs(Func f) const;


public:

    Tree() : _root(nullptr) {}
    ~Tree() { clear_tree(_root);}

    void insert(const TKey& key, const TVal& val);
    void erase(const TKey& key);
    bool find(const TKey& key, TVal& val);
    bool empty() const { return _root == nullptr; }

    void print_D1() { print_D1_rec(_root);}
    void print_D2() { print_D2_rec(_root);}
    void print_D3() { print_D3_rec(_root);}
    void print_W();

    TVal* find_ptr(const TKey& key) const;
};


template<typename TKey, typename TVal>
template<typename Func>
void Tree<TKey, TVal>::bfs(Func f) const{

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
inline void Tree<TKey, TVal>::insert(const TKey& key, const TVal& val){
    Node* node = new Node({ key, val });

    if (!_root) {
        _root = node;
        return;
    }

    Queue<Node*> q;
    q.push(_root);

    while (1) {

        Node* cur = q.front();
        q.pop();

        if (!cur->left) {
            cur->left = node;
            break;
        }
        else {
            q.push(cur->left);
        }

        if (!cur->right) {
            cur->right = node;
            break;
        }
        else {
            q.push(cur->right);
        }
    }
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::erase(const TKey& key){
    if (!_root) return;

    Node* node_to_delete = nullptr;
    Node* last_node = nullptr;
    Node* parent_of_last = nullptr;

    Queue<Node*> q;
    q.push(_root);

    while (!q.is_empty()) {

        Node* cur = q.front();
        q.pop();

        if (cur->val.first == key)
            node_to_delete = cur;

        if (cur->left) {
            parent_of_last = cur;
            last_node = cur->left;
            q.push(cur->left);
        }

        if (cur->right) {
            parent_of_last = cur;
            last_node = cur->right;
            q.push(cur->right);
        }
    }

    if (!node_to_delete)
        return;

    if (last_node == _root) {
        delete _root;
        _root = nullptr;
        return;
    }

    node_to_delete->val = last_node->val;

    if (parent_of_last->right == last_node)
        parent_of_last->right = nullptr;
    else
        parent_of_last->left = nullptr;

    delete last_node;
}

template<typename TKey, typename TVal>
void Tree<TKey, TVal>::print_W() {

    bfs([](Node* cur) {
        std::cout << cur->val.first << " ";
        });
}

template<typename TKey, typename TVal>
inline TVal* Tree<TKey, TVal>::find_ptr(const TKey& key) const{
    TVal* result = nullptr;

    bfs([&](Node* cur) {
        if (cur->val.first == key)
            result = &cur->val.second;
        });

    return result;
}

template<typename TKey, typename TVal>
bool Tree<TKey, TVal>::find(const TKey& key, TVal& val) {

    bool found = false;

    bfs([&](Node* cur) {

        if (cur->val.first == key) {
            val = cur->val.second;
            found = true;
        }

        });

    return found;
}