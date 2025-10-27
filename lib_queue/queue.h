#pragma once

template <class T>
class Queue {
    T* _data;        // ��������� �� ������ ��������� �������
    int _head;       // ������ ������ �������
    int _count;      // ���������� ��������� � �������
    int _capacity;   // ����������� �������

public:
    // ����������� � ���������� �������
    Queue(int size);

    // ����������� �����������
    Queue(const Queue& other);

    // ����������
    ~Queue();

    // �������� ������������
    Queue& operator=(const Queue& other);

    // ���������� �������� � ����� �������
    void push(const T& val);

    // �������� �������� �� ������ �������
    void pop();

    // ��������� �������� �� ������ �������
    inline T top() const;

    // �������� �� �������
    inline bool is_empty() const noexcept;

    // �������� �� �������
    inline bool is_full() const noexcept;

    // ������� �������
    void clear() noexcept;

    // ��������� ���������� ���������
    int size() const;

    // ��������� ������� ������ (��� �������)
    int head() const;

    // ��������� ���������� ��������� (��������� size())
    int count() const;
};

// ���������� ������� ��� ������

// ����������� � ���������� �������
template <class T>
Queue<T>::Queue(int size)
    : _data(new T[size]),  // �������� ������ ��� ������
    _head(0),           // �������� � ������� 0
    _count(0),          // ������� �����
    _capacity(size)     // ���������� �����������
{}

// ����������� �����������
template <class T>
Queue<T>::Queue(const Queue& other)
    : _data(new T[other._capacity]),  // �������� ����� ������
    _head(other._head),
    _count(other._count),
    _capacity(other._capacity)
{
    // �������� ��� �������� �� ��������� �������
    for (int i = 0; i < _capacity; ++i) {
        _data[i] = other._data[i];
    }
}

// ����������
template <class T>
Queue<T>::~Queue() {
    delete[] _data;  // ����������� ������
}

// �������� ������������
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {  // ������ �� ����������������
        delete[] _data;    // ����������� ������ ������

        // �������� ����� ������ � �������� ������
        _capacity = other._capacity;
        _data = new T[_capacity];
        _head = other._head;
        _count = other._count;

        // �������� ��������
        for (int i = 0; i < _capacity; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

// ���������� �������� � ����� �������
template <class T>
void Queue<T>::push(const T& val) {
    // ��������� ������ ������: (������ + ����������) % �����������
    int tail = (_head + _count) % _capacity;
    _data[tail] = val;  // ���������� �������� � �����
    _count++;           // ����������� ������� ���������
}

// �������� �������� �� ������ �������
template <class T>
void Queue<T>::pop() {
    // �������� ������ �� �����: (������� ������ + 1) % �����������
    _head = (_head + 1) % _capacity;
    _count--;  // ��������� ������� ���������
}

// ��������� �������� �� ������ �������
template <class T>
T Queue<T>::top() const {
    return _data[_head];  // ���������� ������� � ������� ������
}

// �������� �� �������
template <class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;  // ������� �����, ���� ������� ����� 0
}

// �������� �� �������
template <class T>
bool Queue<T>::is_full() const noexcept {
    return _count == _capacity;  // ������� �����, ���� ������� ����� �����������
}

// ������� �������
template <class T>
void Queue<T>::clear() noexcept {
    _head = 0;   // ���������� ������ � ������
    _count = 0;  // �������� ������� ���������
}

// ��������� ���������� ���������
template <class T>
int Queue<T>::size() const {
    return _count;  // ���������� ������� ���������� ���������
}

// ��������� ������� ������ (��� �������)
template <class T>
int Queue<T>::head() const {
    return _head;  // ���������� ������ ������
}

// ��������� ���������� ��������� (��������� size())
template <class T>
int Queue<T>::count() const {
    return _count;  // ���������� ������� ���������� ���������
}