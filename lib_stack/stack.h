#pragma once
#include <stdexcept>
using namespace std;

template <class T>
class stack {
    T* _data;
    int _size;
    int _top;
    int _count;

public:
    // Конструктор с параметром по умолчанию
    stack(int size = 16);

    // Деструктор
    ~stack();

    // Добавление элемента в стек
    void push(const T& val);

    // Удаление верхнего элемента из стека
    void pop();

    // Получение верхнего элемента стека
    inline T top() const;

    // Проверка на пустоту
    inline bool is_empty() const noexcept;

    // Проверка на полноту
    inline bool is_full() const noexcept;

    // Очистка стека
    void clear() noexcept;

    // Получение количества элементов в стеке
    inline int size() const noexcept;

    // Получение вместимости стека
    inline int capacity() const noexcept;
};

// Конструктор с параметром по умолчанию
template <class T>
stack<T>::stack(int size): _size(size), _top(-1), _count(0) {
    _data = new T[_size];
}

// Деструктор
template <class T>
stack<T>::~stack() {
    delete[] _data;
}

// Добавление элемента в стек
template <class T>
void stack<T>::push(const T& val) {
    if (is_full()) {
        throw logic_error("Stack is full");
    }
    _data[++_top] = val;
    _count++;
}

// Удаление верхнего элемента из стека
template <class T>
void stack<T>::pop() {
    if (is_empty()) {
        throw logic_error("Stack is empty");
    }
    --_top;
    --_count;
}

// Получение верхнего элемента стека
template <class T>
T stack<T>::top() const {
    if (is_empty()) {
        throw logic_error("Stack is empty");
    }
    return _data[_top];
}

// Проверка на пустоту
template <class T>
bool stack<T>::is_empty() const noexcept {
    return _top == -1;
}

// Проверка на полноту
template <class T>
bool stack<T>::is_full() const noexcept {
    return _top == _size - 1;
}

// Очистка стека
template <class T>
void stack<T>::clear() noexcept {
    _top = -1;
    _count = 0;
}

// Получение количества элементов в стеке
template <class T>
int stack<T>::size() const noexcept {
    return _count;
}

// Получение вместимости стека
template <class T>
int stack<T>::capacity() const noexcept {
    return _size;
}