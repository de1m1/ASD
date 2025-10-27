#pragma once
#include <iostream>
#include <math.h>
#include <stdexcept>

template <class T>
class stack {
    T* _data;     // Указатель на массив элементов стека
    int _size;    // Вместимость стека
    int _top;     // Индекс верхнего элемента (-1 если стек пуст)
    int _count;   // Количество элементов в стеке

public:
    // Конструктор с параметром по умолчанию
    stack(int size = 100);

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

// Реализация методов вне класса

// Конструктор с параметром по умолчанию
template <class T>
stack<T>::stack(int size)
    : _size(size),    // Инициализируем вместимость
    _top(-1),       // Стек пуст, верхний элемент отсутствует
    _count(0)       // Начальное количество элементов - 0
{
    _data = new T[_size];  // Выделяем память под массив элементов
}

// Деструктор
template <class T>
stack<T>::~stack() {
    delete[] _data;  // Освобождаем память, занятую массивом
}

// Добавление элемента в стек
template <class T>
void stack<T>::push(const T& val) {
    if (is_full()) {
        throw std::logic_error("Stack is full");  // Нельзя добавить в полный стек
    }
    _data[++_top] = val;  // Увеличиваем _top и записываем значение
    _count++;             // Увеличиваем счетчик элементов
}

// Удаление верхнего элемента из стека
template <class T>
void stack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");  // Нельзя удалить из пустого стека
    }
    --_top;    // Уменьшаем индекс верхнего элемента
    --_count;  // Уменьшаем счетчик элементов
}

// Получение верхнего элемента стека
template <class T>
T stack<T>::top() const {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");  // Нельзя получить элемент из пустого стека
    }
    return _data[_top];  // Возвращаем элемент на вершине стека
}

// Проверка на пустоту
template <class T>
bool stack<T>::is_empty() const noexcept {
    return _top == -1;  // Стек пуст, если верхний элемент отсутствует
}

// Проверка на полноту
template <class T>
bool stack<T>::is_full() const noexcept {
    return _top == _size - 1;  // Стек полон, если верхний элемент на последней позиции
}

// Очистка стека
template <class T>
void stack<T>::clear() noexcept {
    _top = -1;   // Сбрасываем индекс верхнего элемента
    _count = 0;  // Обнуляем счетчик элементов
}

// Получение количества элементов в стеке
template <class T>
int stack<T>::size() const noexcept {
    return _count;  // Возвращаем текущее количество элементов
}

// Получение вместимости стека
template <class T>
int stack<T>::capacity() const noexcept {
    return _size;  // Возвращаем максимальную вместимость стека
}