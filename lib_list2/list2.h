#pragma once
#include <cstddef>
#include <stdexcept>
using namespace std;

template<typename T>
class ListDouble {
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

        // Префиксные инкремент и декремент
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        // Постфиксные инкременты  и декремент
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // Операторы сравнения
        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }

        friend class ListDouble<T>;

    };

    // Конструкторы
    ListDouble() : head(nullptr), tail(nullptr), size_(0) {}

    ListDouble(const ListDouble& other) : head(nullptr), tail(nullptr), size_(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Деструктор
    ~ListDouble();

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
    ListDouble& operator=(const ListDouble& other);

    // Вставка и удаление по позиции
    void insert(const Iterator& pos, const T& value);
    void erase(const Iterator& pos);

    // Методы доступа
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Итераторы обратно
    Iterator rbegin() { return Iterator(tail); }
    Iterator rend() { return Iterator(nullptr); }

    // Итераторы
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

};

// Вставка в конец
template<typename T>
void ListDouble<T>::push_back(const T& value) {
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

// Деструктор
template<typename T>
ListDouble<T>::~ListDouble() {
    clear();
}

// Очистка
template<typename T>
void ListDouble<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size_ = 0;
}

// Вставка в начало
template<typename T>
void ListDouble<T>::push_front(const T& value) {
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

// Удаление с конца
template<typename T>
void ListDouble<T>::pop_back() {
    if (empty()) {
        throw runtime_error("List is empty!");
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

// Удаление с начала
template<typename T>
void ListDouble<T>::pop_front() {
    if (empty()) {
        throw runtime_error("List is empty!");
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

// Доступ к 1 элементу
template<typename T>
T& ListDouble<T>::front() {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    return head->data;
}

template<typename T>
const T& ListDouble<T>::front() const {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    return head->data;
}

// Доступ к последнему элементу
template<typename T>
T& ListDouble<T>::back() {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    return tail->data;
}

template<typename T>
const T& ListDouble<T>::back() const {
    if (empty()) {
        throw runtime_error("List is empty!");
    }
    return tail->data;
}

// Оператор присваивания
template<typename T>
ListDouble<T>& ListDouble<T>::operator=(const ListDouble& other) {
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

// Вставка по позиции
template<typename T>
void ListDouble<T>::insert(const Iterator& pos, const T& value) {
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

// Удаление по позиции
template<typename T>
void ListDouble<T>::erase(const Iterator& pos) {
    if (pos == end() || empty()) {
        throw runtime_error("Invalid iterator!");
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