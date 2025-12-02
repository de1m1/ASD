#pragma once
#include <stdexcept>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size_;

public:
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node);
        T& operator*();
        T* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        friend class List<T>;
    };

    List();
    List(const List& other);
    ~List();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void clear();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    List& operator=(const List& other);

    void insert(const Iterator& pos, const T& value);
    void erase(const Iterator& pos);

    size_t size() const;
    bool empty() const;

    Iterator begin();
    Iterator end();
};

// ----------------- Реализация -----------------

// Iterator
template<typename T>
List<T>::Iterator::Iterator(Node* node) : current(node) {}

template<typename T>
T& List<T>::Iterator::operator*() { return current->data; }

template<typename T>
T* List<T>::Iterator::operator->() { return &current->data; }

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    current = current->next;
    return temp;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const { return current != other.current; }

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const { return current == other.current; }

// Конструкторы/деструктор
template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0) {}

template<typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), size_(0) {
    Node* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
List<T>::~List() { clear(); }

// Методы
template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) head = tail = newNode;
    else { tail->next = newNode; tail = newNode; }
    size_++;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) head = tail = newNode;
    else { newNode->next = head; head = newNode; }
    size_++;
}

template<typename T>
void List<T>::pop_front() {
    if (empty()) throw std::runtime_error("List is empty!");
    Node* oldHead = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete oldHead;
    size_--;
}

template<typename T>
void List<T>::pop_back() {
    if (empty()) throw std::runtime_error("List is empty!");
    if (head == tail) { delete head; head = tail = nullptr; }
    else {
        Node* current = head;
        while (current->next != tail) current = current->next;
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size_--;
}

template<typename T>
void List<T>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
    size_ = 0;
}

template<typename T>
T& List<T>::front() {
    if (empty()) throw std::runtime_error("List is empty!");
    return head->data;
}

template<typename T>
const T& List<T>::front() const {
    if (empty()) throw std::runtime_error("List is empty!");
    return head->data;
}

template<typename T>
T& List<T>::back() {
    if (empty()) throw std::runtime_error("List is empty!");
    return tail->data;
}

template<typename T>
const T& List<T>::back() const {
    if (empty()) throw std::runtime_error("List is empty!");
    return tail->data;
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void List<T>::insert(const Iterator& pos, const T& value) {
    if (pos == begin()) push_front(value);
    else if (pos == end()) push_back(value);
    else {
        Node* newNode = new Node(value);
        Node* current = head;
        while (current && current->next != pos.current) current = current->next;
        if (!current) throw std::runtime_error("Invalid iterator!");
        newNode->next = current->next;
        current->next = newNode;
        size_++;
    }
}

template<typename T>
void List<T>::erase(const Iterator& pos) {
    if (pos == end() || empty()) throw std::runtime_error("Invalid iterator!");
    if (pos.current == head) { pop_front(); return; }
    Node* current = head;
    while (current && current->next != pos.current) current = current->next;
    if (!current || !current->next) throw std::runtime_error("Invalid iterator!");
    Node* toDelete = current->next;
    current->next = toDelete->next;
    if (toDelete == tail) tail = current;
    delete toDelete;
    size_--;
}

template<typename T>
size_t List<T>::size() const { return size_; }

template<typename T>
bool List<T>::empty() const { return size_ == 0; }

template<typename T>
typename List<T>::Iterator List<T>::begin() { return Iterator(head); }

template<typename T>
typename List<T>::Iterator List<T>::end() { return Iterator(nullptr); }
