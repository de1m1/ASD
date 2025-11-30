#pragma once
#include <cstddef>
#include <stdexcept>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size_;

public:
    // Итератор для прохода по списку
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        // Доступ к данным
        T& operator*() { return current->data; }
        T* operator->() { return &current->data; }

        // Префиксные инкременты
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        // Постфиксные инкременты  
        Iterator operator++(int) {
            Iterator temp = *this;
            current = current->next;
            return temp;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            current = current->prev;
            return temp;
        }

        // Операторы сравнения
        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }

        friend class List<T>;

    };

    // Конструкторы
    List() : head(nullptr), tail(nullptr), size_(0) {}

    List(const List& other) : head(nullptr), tail(nullptr), size_(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Деструктор
    ~List();

    // Основные методы
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void clear();

    // Доступы к элементам
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    // Оператор присваивания 
    List& operator=(const List& other);

    // Вставка и удаление по позиции
    void insert(const Iterator& pos, const T& value);
    void erase(const Iterator& pos);

    // Методы доступа
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Итераторы
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);

    if (empty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size_++;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size_ = 0;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* newNode = new Node(value);

    if (empty()) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    size_++;
}

template<typename T>
void List<T>::pop_back() {
    if (empty()) {
        throw std::runtime_error("List is empty!");
    }

    if (head == tail) {
        delete tail;
        head = tail = nullptr;
    }
    else {
        Node* newTail = tail->prev;
        newTail->next = nullptr;
        delete tail;
        tail = newTail;
    }

    size_--;
}

template<typename T>
void List<T>::pop_front() {
    if (empty()) {
        throw std::runtime_error("List is empty!");
    }

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* newHead = head->next;
        newHead->prev = nullptr;
        delete head;
        head = newHead;
    }

    size_--;
}

template<typename T>
T& List<T>::front() {
    if (empty()) {
        throw std::runtime_error("List is empty!");
    }
    return head->data;
}

template<typename T>
const T& List<T>::front() const {
    if (empty()) {
        throw std::runtime_error("List is empty!");
    }
    return head->data;
}

template<typename T>
T& List<T>::back() {
    if (empty()) {
        throw std::runtime_error("List is empty!");
    }
    return tail->data;
}

template<typename T>
const T& List<T>::back() const {
    if (empty()) {
        throw std::runtime_error("List is empty!");
    }
    return tail->data;
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void List<T>::insert(const Iterator& pos, const T& value) {
    if (pos == begin()) {
        push_front(value);
    }
    else if (pos == end()) {
        push_back(value);
    }
    else {
        Node* newNode = new Node(value);
        Node* current = pos.current;
        Node* prevNode = current->prev;

        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = current;
        current->prev = newNode;

        size_++;
    }
}

template<typename T>
void List<T>::erase(const Iterator& pos) {
    if (pos == end() || empty()) {
        throw std::runtime_error("Invalid iterator!");
    }

    Node* toDelete = pos.current;

    if (toDelete == head) {
        pop_front();
    }
    else if (toDelete == tail) {
        pop_back();
    }
    else {
        Node* prevNode = toDelete->prev;
        Node* nextNode = toDelete->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete toDelete;
        size_--;
    }
}

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
        Iterator(T* pos = nullptr) : _ptr(pos) {}

        T& operator*() { return *_ptr; }

        bool operator==(const Iterator& other) const { return _ptr == other._ptr; }
        bool operator!=(const Iterator& other) const { return _ptr != other._ptr; }

        Iterator& operator++() {
            _ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            _ptr++;
            return temp;
        }
    };
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size_); }

    // Конструкторы
    TVector();
    TVector(size_t count, const T& value = T());

    // Деструктор
    ~TVector();

    // Копирование
    TVector(const TVector& other);
    TVector& operator=(const TVector& other);

    // Основные методы
    void push_back(const T& value);
    void pop_back();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front();
    T& back();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
};

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
TVector<T>::~TVector() {
    delete[] data;
}

template<typename T>
TVector<T>::TVector(const TVector& other) : data(nullptr), size_(0), capacity_(0) {
    resize(other.capacity_);
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
        data[i] = other.data[i];
    }
}

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
        throw std::runtime_error("TVector is empty!");
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
        throw std::out_of_range("Index out of range!");
    }
    return data[index];
}

template<typename T>
const T& TVector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range!");
    }
    return data[index];
}

template<typename T>
T& TVector<T>::front() {
    if (empty()) {
        throw std::runtime_error("TVector is empty!");
    }
    return data[0];
}

template<typename T>
T& TVector<T>::back() {
    if (empty()) {
        throw std::runtime_error("TVector is empty!");
    }
    return data[size_ - 1];
}

template<typename T>
size_t TVector<T>::size() const { return size_; }

template<typename T>
size_t TVector<T>::capacity() const { return capacity_; }

template<typename T>
bool TVector<T>::empty() const { return size_ == 0; }

template<typename T>
void TVector<T>::clear() {
    size_ = 0;
}

// Явные инстанцирования
template class TVector<int>;
template class TVector<double>;
