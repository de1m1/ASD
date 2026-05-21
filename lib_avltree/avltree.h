#pragma once
#include <utility>
#include "queue.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

template<typename TKey, typename TVal>
class AVLTree {
private:

    struct Node {
        std::pair<TKey, TVal> _data;
        Node* left;
        Node* right;
        Node* _parent;
        int _height;

        Node(const TKey& key, const TVal& val,Node* parent = nullptr):_data({ key, val }), left(nullptr),right(nullptr),_parent(parent), _height(1) {}
    };

    Node* _root;

private:

	void right_rotate(Node*& node);
	void left_rotate(Node*& node);

    void print_D1_rec(Node* cur); // CLR
    void print_D2_rec(Node* cur); // LNR
    void print_D3_rec(Node* cur); // LRN

	void RR(Node*& node);
	void LL(Node*& node);
	void LR(Node*& node);
	void RL(Node*& node);

	int calculate_balance(Node* node);
	void recover_balance(Node*& node);
	void recalculate_height(Node* node);

    void clear(Node* node){ 
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
	}

    Node* find_pos(const TKey& key) const noexcept {

        Node* cur = _root;

        while (cur && cur->_data.first != key) {

            if (key < cur->_data.first)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return cur;
    }

public:

    AVLTree() : _root(nullptr) {}
	~AVLTree() { clear(_root); }

    void insert(const TKey& key, const TVal& val);
    TVal& find(const TKey& key);
    void erase(const TKey& key);
    bool empty() const noexcept { return _root == nullptr; }
    bool contains(const TKey& key) const noexcept { return find_pos(key) != nullptr; }

    void print_D1() { print_D1_rec(_root); }
    void print_D2() { print_D2_rec(_root); }
    void print_D3() { print_D3_rec(_root); }
    void print_W();
};

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::print_D1_rec(Node* cur) {
    if (!cur) return;

    std::cout << cur->_data.first << " ";
    print_D1_rec(cur->left);
    print_D1_rec(cur->right);
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::print_D2_rec(Node* cur) {
    if (!cur) return;

    print_D2_rec(cur->left);
    std::cout << cur->_data.first << " ";
    print_D2_rec(cur->right);
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::print_D3_rec(Node* cur) {
    if (!cur) return;

    print_D3_rec(cur->left);
    print_D3_rec(cur->right);
    std::cout << cur->_data.first << " ";
}

template<typename TKey, typename TVal>
TVal& AVLTree<TKey, TVal>::find(const TKey& key) {

    Node* cur = _root;

    while (cur && cur->_data.first != key) {
        if (key < cur->_data.first)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (!cur)
        throw std::runtime_error("Key not found");

    return cur->_data.second;
}

template<typename TKey, typename TVal>
int AVLTree<TKey, TVal>::calculate_balance(Node* node) {
    int balance = 0;

    if (node->right) balance += node->right->_height;
	if (node->left) balance -= node->left->_height;

	return balance;
} 

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::recalculate_height(Node* node) {

    int left_height = 0;
    int right_height = 0;

    if (node->left)
        left_height = node->left->_height;

    if (node->right)
        right_height = node->right->_height;

    node->_height = std::max(left_height, right_height) + 1;
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::right_rotate(Node*& node) {
    /*
             G
            /
           P
          /
         C
        / \ 
       A   B
  
         после:
             G
            /
           C
          / \
         A   P
            /         
           B
   */
    if (!node || !node->left) return;

    Node* G = node->_parent;   // папа папы
    Node* P = node;            // папа
    Node* C = P->left;         // не папа

    P->left = C->right;
    if (C->right) {
        C->right->_parent = P;
    }

    C->right = P;
    P->_parent = C;
    C->_parent = G;

    if (G) {
        if (G->left == P) {
            G->left = C;
        }
        else {
            G->right = C;
        }
    }
    else {
        _root = C;
    }

    recalculate_height(P);
    recalculate_height(C);
    if (G) {
        recalculate_height(G);
    }

    node = C;
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::left_rotate(Node*& node) {
    /*
            G
             \
              P
               \
                C
               / \
              B   A

           после:

             G
              \
               C            
              / \
             P   A
              \
               B
    */
    if (!node || !node->right) return;

    Node* G = node->_parent;   // папа папы
    Node* P = node;            // папа
    Node* C = P->right;        // не папа

    P->right = C->left;
    if (C->left)
        C->left->_parent = P;

    C->left = P;
    P->_parent = C;
    C->_parent = G;

    if (G) {
        if (G->left == P)
            G->left = C;
        else
            G->right = C;
    }
    else {
        _root = C;
    }

    recalculate_height(P);
    recalculate_height(C);
    if (G)
        recalculate_height(G);

    node = C;
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::LL(Node*& node) {
    /*
          G
         /       
        P
       / 
      C   
      после:
        P
       / \
      C   G

    */
    right_rotate(node);
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::RR(Node*& node) {
    /*
       G
        \
         P
          \
           C
      после:
        P
       / \
      G   C

    */
    left_rotate(node);
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::LR(Node*& node) {
    /*
       G
      /       
     P
      \ 
	   C
     после 1:
         G
        /
       C
      /
     P
    после 2:
        С
       / \
      P   G
    */
    left_rotate(node->left);
    right_rotate(node);
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::RL(Node*& node) {
    /*
       G
        \
         P
        /
       C
     после 1:
     G
      \
       C
        \
         P
    после 2:
        С
       / \
      G   P
    */
    right_rotate(node->right);
    left_rotate(node);
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::recover_balance(Node*& node) {

    recalculate_height(node);

    int balance = calculate_balance(node);

    if (balance < -1) {

        if (calculate_balance(node->left) <= 0)
            LL(node);
        else
            LR(node);
    }

    else if (balance > 1) {

        if (calculate_balance(node->right) >= 0)
            RR(node);
        else
            RL(node);
    }
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::insert(const TKey& key, const TVal& val) {

    Node* node = new Node(key, val);

    if (!_root) {
        _root = node;
        return;
    }

    Node* cur = _root;
    Node* P = nullptr;

    while (cur) {
        P = cur;

        if (key < cur->_data.first)
            cur = cur->left;
        else if (key > cur->_data.first)
            cur = cur->right;
        else {
            cur->_data.second = val;
            delete node;
            return;
        }
    }

    node->_parent = P;

    if (key < P->_data.first)
        P->left = node;
    else
        P->right = node;

    while (P) {
        recover_balance(P);

        P = P->_parent;
    }
}

template<typename TKey, typename TVal>
void AVLTree<TKey, TVal>::erase(const TKey& key) {

    Node* P = nullptr;
    Node* cur = _root;

    while (cur && cur->_data.first != key) {

        P = cur;

        if (key < cur->_data.first)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (!cur)
        return;

	Node* pos_recover_balance = nullptr; // отсюдава пойдёт восстановление баланса

    // 2 ребёнка
    if (cur->left && cur->right) {

        Node* G = cur;
        Node* pred = cur->left;

        while (pred->right) {
            G = pred;
            pred = pred->right;
        }

        cur->_data = pred->_data;

        pos_recover_balance = G;

        if (G == cur)
            G->left = pred->left;
        else
            G->right = pred->left;

        if (pred->left)
            pred->left->_parent = G;

        delete pred;
    }

    // 0 или 1 ребёнок
    else {

        Node* C = nullptr;

        if (cur->left)
            C = cur->left;
        else
            C = cur->right;

        pos_recover_balance = P;

        if (!P)
            _root = C;

        else if (P->left == cur)
            P->left = C;
        else
            P->right = C;

        if (C)
            C->_parent = P;

        delete cur;
    }

    // восстановление
    cur = pos_recover_balance;

    while (cur) {

        int old_height = cur->_height;

        int balance = calculate_balance(cur);

        if (abs(balance) > 1)
            recover_balance(cur);

        recalculate_height(cur);

        if (old_height == cur->_height)
            break;

        cur = cur->_parent;
    }
}