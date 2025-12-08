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

// Вставка в конец
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

// Деструктор
template<typename T>
List<T>::~List() {
    clear();
}

// Очистка
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

// Вставка в начало
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

// Удаление с конца
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

// Удаление с начала
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

// Доступ к 1 элементу
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

// Доступ к последнему элементу
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

// Оператор присваивания
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

// Вставка по позиции
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

// Удаление по позиции
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