#pragma once
#include <iostream>
#include <math.h>
#include <stdexcept>

template <class T>
class stack {
    T* _data;     // ��������� �� ������ ��������� �����
    int _size;    // ����������� �����
    int _top;     // ������ �������� �������� (-1 ���� ���� ����)
    int _count;   // ���������� ��������� � �����

public:
    // ����������� � ���������� �� ���������
    stack(int size = 100);

    // ����������
    ~stack();

    // ���������� �������� � ����
    void push(const T& val);

    // �������� �������� �������� �� �����
    void pop();

    // ��������� �������� �������� �����
    inline T top() const;

    // �������� �� �������
    inline bool is_empty() const noexcept;

    // �������� �� �������
    inline bool is_full() const noexcept;

    // ������� �����
    void clear() noexcept;

    // ��������� ���������� ��������� � �����
    inline int size() const noexcept;

    // ��������� ����������� �����
    inline int capacity() const noexcept;
};

// ���������� ������� ��� ������

// ����������� � ���������� �� ���������
template <class T>
stack<T>::stack(int size)
    : _size(size),    // �������������� �����������
    _top(-1),       // ���� ����, ������� ������� �����������
    _count(0)       // ��������� ���������� ��������� - 0
{
    _data = new T[_size];  // �������� ������ ��� ������ ���������
}

// ����������
template <class T>
stack<T>::~stack() {
    delete[] _data;  // ����������� ������, ������� ��������
}

// ���������� �������� � ����
template <class T>
void stack<T>::push(const T& val) {
    if (is_full()) {
        throw std::logic_error("Stack is full");  // ������ �������� � ������ ����
    }
    _data[++_top] = val;  // ����������� _top � ���������� ��������
    _count++;             // ����������� ������� ���������
}

// �������� �������� �������� �� �����
template <class T>
void stack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");  // ������ ������� �� ������� �����
    }
    --_top;    // ��������� ������ �������� ��������
    --_count;  // ��������� ������� ���������
}

// ��������� �������� �������� �����
template <class T>
T stack<T>::top() const {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");  // ������ �������� ������� �� ������� �����
    }
    return _data[_top];  // ���������� ������� �� ������� �����
}

// �������� �� �������
template <class T>
bool stack<T>::is_empty() const noexcept {
    return _top == -1;  // ���� ����, ���� ������� ������� �����������
}

// �������� �� �������
template <class T>
bool stack<T>::is_full() const noexcept {
    return _top == _size - 1;  // ���� �����, ���� ������� ������� �� ��������� �������
}

// ������� �����
template <class T>
void stack<T>::clear() noexcept {
    _top = -1;   // ���������� ������ �������� ��������
    _count = 0;  // �������� ������� ���������
}

// ��������� ���������� ��������� � �����
template <class T>
int stack<T>::size() const noexcept {
    return _count;  // ���������� ������� ���������� ���������
}

// ��������� ����������� �����
template <class T>
int stack<T>::capacity() const noexcept {
    return _size;  // ���������� ������������ ����������� �����
}