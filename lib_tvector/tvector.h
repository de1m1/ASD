#pragma once
#include <cstddef>
#include <stdexcept>
using namespace std;

template<typename T>
class TVector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity);

public:

    class Iterator {
        T* _ptr;
    public:
        // Конструктор
        Iterator(T* pos = nullptr) : _ptr(pos) {}

        // Разыменование
        T& operator*() { return *_ptr; }

        // Операторы равенства/неравенства
        bool operator==(const Iterator& other) const { return _ptr == other._ptr; }
        bool operator!=(const Iterator& other) const { return _ptr != other._ptr; }

        // Префиксный ++
        Iterator& operator++() {
            _ptr++;
            return *this;
        }

        // Постфиксный ++
        Iterator operator++(int) {
            Iterator temp = *this;
            _ptr++;
            return temp;
        }
    };
    // Доступ к 1 и последнему элементам
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }

    // Конструкторы
    TVector();
    TVector(size_t count, const T& value = T());

    // Деструктор
    ~TVector();

    // Конструктор копирования
    TVector(const TVector& other);

    // Оператор присваивания
    TVector& operator=(const TVector& other);

    // Вставки
    void push_back(const T& value);
    void pop_back();

    // Оператор []
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Вставки
    T& at(size_t index);
    const T& at(size_t index) const;

    // Доступ к элементам
    T& front();
    T& back();
    size_t size() const;
    size_t capacity() const;

    // Проверка на пустоту
    bool empty() const;

    // Очистка
    void clear();
};

// 
template<typename T>
void TVector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
}

// Конструкторы
template<typename T>
TVector<T>::TVector() : data(nullptr), size_(0), capacity_(0) {}

template<typename T>
TVector<T>::TVector(size_t count, const T& value) : data(nullptr), size_(0), capacity_(0) {
    resize(count);
    size_ = count;
    for (size_t i = 0; i < size_; ++i) {
        data[i] = value;
    }
}

template<typename T>
TVector<T>::TVector(const TVector& other) : data(nullptr), size_(0), capacity_(0) {
    resize(other.capacity_);
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
        data[i] = other.data[i];
    }
}

// Деструктор
template<typename T>
TVector<T>::~TVector() {
    delete[] data;
}

// Оператор присваивания
template<typename T>
TVector<T>& TVector<T>::operator=(const TVector& other) {
    if (this != &other) {
        delete[] data;
        data = nullptr;
        size_ = 0;
        capacity_ = 0;

        resize(other.capacity_);
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Вставки
template<typename T>
void TVector<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        resize(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data[size_++] = value;
}

template<typename T>
void TVector<T>::pop_back() {
    if (empty()) {
        throw runtime_error("TVector is empty!");
    }
    --size_;
}

template<typename T>
T& TVector<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
const T& TVector<T>::operator[](size_t index) const {
    return data[index];
}

template<typename T>
T& TVector<T>::at(size_t index) {
    if (index >= size_) {
        throw out_of_range("Index out of range!");
    }
    return data[index];
}

template<typename T>
const T& TVector<T>::at(size_t index) const {
    if (index >= size_) {
        throw out_of_range("Index out of range!");
    }
    return data[index];
}

// Доступы к данным
template<typename T>
T& TVector<T>::front() {
    if (empty()) {
        throw runtime_error("TVector is empty!");
    }
    return data[0];
}

template<typename T>
T& TVector<T>::back() {
    if (empty()) {
        throw runtime_error("TVector is empty!");
    }
    return data[size_ - 1];
}

template<typename T>
size_t TVector<T>::size() const { return size_; }

template<typename T>
size_t TVector<T>::capacity() const { return capacity_; }

// Проверка на пустоту
template<typename T>
bool TVector<T>::empty() const { return size_ == 0; }

// Очистка
template<typename T>
void TVector<T>::clear() {
    size_ = 0;
}

// Явные инстанцирования
template class TVector<int>;
template class TVector<double>;
