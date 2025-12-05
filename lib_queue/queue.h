#pragma once

template <class T>
class Queue {
    T* _data;
    int _head;
    int _count;
    int _capacity;

public:
    // Конструкторы
    Queue(int size);
    Queue(const Queue& other);

    // Деструктор
    ~Queue();

    // Оператор присваивания
    Queue& operator=(const Queue& other);

    // Добавление элемента в конец очереди
    void push(const T& val);

    // Удаление элемента из начала очереди
    void pop();

    // Получение элемента из начала очереди
    inline T front() const;

    // Получение элемента из конца очереди
    inline T back() const;

    // Проверка на пустоту
    inline bool is_empty() const noexcept;

    // Проверка на полноту
    inline bool is_full() const noexcept;

    // Очистка очереди
    void clear() noexcept;

    // Геттеры
    int size() const;
    int head() const;
    int count() const;
};

// Конструктор с параметром размера
template <class T>
Queue<T>::Queue(int size): _data(new T[size]), _head(0),_count(0), _capacity(size){}

// Конструктор копирования
template <class T>
Queue<T>::Queue(const Queue& other)
    : _data(new T[other._capacity]),
    _head(other._head),
    _count(other._count),
    _capacity(other._capacity)
{
    for (int i = 0; i < _capacity; ++i) {
        _data[i] = other._data[i];
    }
}

// Деструктор
template <class T>
Queue<T>::~Queue() {
    delete[] _data;
}

// Оператор присваивания
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        delete[] _data;

        _capacity = other._capacity;
        _data = new T[_capacity];
        _head = other._head;
        _count = other._count;

        for (int i = 0; i < _capacity; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

// Добавление элемента в конец очереди
template <class T>
void Queue<T>::push(const T& val) {
    if (is_full()) {
        throw std::overflow_error("Queue::push: Queue is full");
    }
    int tail = (_head + _count) % _capacity;
    _data[tail] = val;
    _count++;
}

// Удаление элемента из начала очереди
template <class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::overflow_error("Queue::push: Queue is empty");
    }
    _head = (_head + 1) % _capacity;
    _count--;
}

// Получение элемента из начала очереди
template <class T>
T Queue<T>::front() const {
    if (is_empty()) throw std::underflow_error("Queue is empty");
    return _data[_head];
}

template <class T>
T Queue<T>::back() const {
    if (is_empty()) throw std::underflow_error("Queue is empty");
    int tail = (_head + _count - 1) % _capacity;
    return _data[tail];
}

// Проверка на пустоту
template <class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

// Проверка на полноту
template <class T>
bool Queue<T>::is_full() const noexcept {
    return _count == _capacity;
}

// Очистка очереди
template <class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _count = 0;
}

// Геттеры
template <class T>
int Queue<T>::size() const {
    return _count;
}

template <class T>
int Queue<T>::head() const {
    return _head;
}

