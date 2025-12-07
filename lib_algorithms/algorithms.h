#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "stack.h"
#include "list.h"
#include "dsu.h"

using namespace std;

// Скобки через Stack

bool check_brackets(const std::string& stk) {
    stack<char> brackets;
    for (auto b : stk) {
        if (b == '(' || b == '{' || b == '[') {
            brackets.push(b);
        }
        else if (b == ')' || b == '}' || b == ']') {
            if (brackets.is_empty()) {
                return false;
            }
            char top = brackets.top();
            brackets.pop();
            if ((b == ')' && top != '(') || (b == '}' && top != '{') || (b == ']' && top != '[')) {
                return false;
            }
        }
    }
    return brackets.is_empty();
}

// Задача из DSU

inline int toIndex(int row, int col, int cols) {
    return row * cols + col;
}

int countIslands(const vector<vector<int>>& grid) {

    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    int totalCells = rows * cols;

    DSU dsu(totalCells);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if (grid[i][j] == 1) {

                int currentIdx = toIndex(i, j, cols);

                if (j + 1 < cols && grid[i][j + 1] == 1) {
                    int rightIdx = toIndex(i, j + 1, cols);
                    dsu.united(currentIdx, rightIdx);
                }

                if (i + 1 < rows && grid[i + 1][j] == 1) {
                    int downIdx = toIndex(i + 1, j, cols);
                    dsu.united(currentIdx, downIdx);
                }
            }
        }
    }
    unordered_set<int> uniqueRoots;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if (grid[i][j] == 1) {

                int idx = toIndex(i, j, cols);

                int root = dsu.find(idx);

                uniqueRoots.insert(root);
            }
        }
    }
    return uniqueRoots.size();
}

// Методы нахождения цикла в списке

template <typename T>
bool CheckListCycleFloyd(const List<T>& list){

    if (list.head == nullptr || list.head->next == nullptr) return false;
    
    typename List<T>::Node* rabbit = list.head;
    typename List<T>::Node* turtle = list.head;

    while (rabbit != nullptr && rabbit->next != nullptr) {
        turtle = turtle->next;
        rabbit = rabbit->next->next;

        if (rabbit == turtle) return true;

    }
    return false;
}

template bool CheckListCycleFloyd<int>(const List<int>&);

// 2 - метод разворота указателей

template <typename T>
bool CheckListCycleReverse(List<T>& list) {
    using Node = typename List<T>::Node;

    if (list.head == nullptr || list.head->next == nullptr) {
        return false;
    }

    Node* current = list.head;
    Node* prev = nullptr;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;

        if (next == list.head) {
            Node* restore_current = current;
            Node* restore_prev = nullptr;

            while (restore_current != nullptr) {
                Node* restore_next = restore_current->next;
                restore_current->next = restore_prev;
                restore_prev = restore_current;
                restore_current = restore_next;

                if (restore_prev == list.head) {
                    break;
                }
            }
            return true;
        }

        prev = current;
        current = next;
    }

    Node* restore_current = prev;
    Node* restore_prev = nullptr;

    while (restore_current != nullptr) {
        Node* restore_next = restore_current->next;
        restore_current->next = restore_prev;
        restore_prev = restore_current;
        restore_current = restore_next;

        if (restore_prev == list.head) {
            break;
        }
    }

    return false;
}

template bool CheckListCycleReverse<int>(List<int>&);

// 3 - метод зайца и черепахи + вовращение начала цикла

template <typename T>
pair<bool, typename List<T>::Iterator>
FindCycleStartFloyd(const List<T>& list) {
    using Iterator = typename List<T>::Iterator;

    if (list.head == nullptr) {
        return { false, Iterator(nullptr) };
    }

    typename List<T>::Node* turtle = list.head;
    typename List<T>::Node* rabbit = list.head;

    bool hasCycle = false;

    while (rabbit != nullptr && rabbit->next != nullptr) {
        turtle = turtle->next;
        rabbit = rabbit->next->next;

        if (rabbit == turtle) {
            hasCycle = true;
            break;
        }
    }

    if (!hasCycle) {
        return { false, Iterator(nullptr) };
    }

    typename List<T>::Node* ptr1 = list.head;
    typename List<T>::Node* ptr2 = turtle;

    while (ptr1 != ptr2) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return { true, Iterator(ptr1) };
}

template std::pair<bool, typename List<int>::Iterator>
FindCycleStartFloyd<int>(const List<int>&);