#pragma once

#include "stack.h"
#include "list.h"

bool check_breckets(const std::string& stk) {
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

namespace Algorithms {

    template<typename T>
    bool hasCycleFloyd(typename List<T>::Iterator begin, typename List<T>::Iterator end) {
        if (begin == end) return false;

        auto slow = begin;
        auto fast = begin;

        ++fast;
        if (fast == end) return false;

        while (fast != end) {
            ++slow;

            ++fast;
            if (fast == end) return false;

            ++fast;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }

}

