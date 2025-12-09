#pragma once

#include "list.h"
#include <stdexcept>
template<class T>
class lststack {

    List<T> _stack;
public:
    // Конструкторы и деструктор
    lststack();
    lststack(const lststack& other);
    ~lststack();

    // Оператор присваивания
    lststack<T>& operator=(const lststack<T>& other);

    // Добавление элемента на стек
    void push(const T& val);

    // Удаление элемента с вершины стека
    void pop();

    // Получение элемента на вершине
    T& top();
    const T& top() const;

    // Проверка на пустоту
    bool empty() const noexcept;

    // Получение размера стека
    size_t size() const noexcept;

    // Очистка стека
    void clear() noexcept;

};

// Конструкторы и деструктор
template <class T>
lststack<T>::lststack() : _stack() {}

template <class T>
lststack<T>::lststack(const lststack<T>& other) : _stack(other._stack) {}

template <class T>
lststack<T>::~lststack() {}

// Оператор присваивания
template <class T>
lststack<T>& lststack<T>::operator=(const lststack<T>& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

// Добавление элемента на стек
template <class T>
void lststack<T>::push(const T& val) {
    _stack.push_front(val);
}

// Удаление элемента с вершины стека
template <class T>
void lststack<T>::pop() {
    if (empty()) {
        throw logic_error("lststack is empty");
    }
    _stack.pop_front();
}

// Получение элемента на вершине
template <class T>
T& lststack<T>::top() {
    if (empty()) {
        throw logic_error("lststack is empty");
    }
    return *_stack.begin();
}

template <class T>
const T& lststack<T>::top() const {
    if (empty()) {
        throw logic_error("lststack is empty");
    }
    return *_stack.begin();
}

// Проверка на пустоту
template <class T>
bool lststack<T>::empty() const noexcept {
    return _stack.empty();
}

// Получение размера стека
template <class T>
size_t lststack<T>::size() const noexcept {
    return _stack.size();
}

// Очистка стека
template <class T>
void lststack<T>::clear() noexcept {
    _stack.clear();
}