#pragma once
#include <stdexcept>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        // Конструктор узла
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
        // Конструктор итератора
        Iterator(Node* node);

        // Оператор разыменования - получение данных текущего узла
        T& operator*();

        // Оператор доступа к членам через указатель
        T* operator->();

        // Префиксный инкремент (++it)
        Iterator& operator++();

        // Постфиксный инкремент (it++)
        Iterator operator++(int);

        // Операторы сравнения
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;

        // Дружественный класс для доступа к приватным членам
        friend class List<T>;

    };
    
    // Конструкторы и деструктор
    List();
    List(const List& other);
    ~List();

    // Основные методы работы со списком
    void push_back(const T& value); 
    void push_front(const T& value); 
    void pop_back();                 
    void pop_front(); 
    void clear();                   

    // Методы доступа к элементам
    T& front();                   
    const T& front() const;      
    T& back();                   
    const T& back() const;       

    // Оператор присваивания
    List& operator=(const List& other);

    // Методы работы с итераторами
    void insert(const Iterator& pos, const T& value);  
    void erase(const Iterator& pos);                   

    // Методы получения информации о списке
    size_t size() const;
    bool empty() const;

    // Методы для получения итераторов
    Iterator begin();  // Итератор на первый элемент
    Iterator end();    // Итератор на позицию после последнего элемента

    // Метод Флойда для нахождения цикла
    template<typename T>
    friend bool CheckListCycleFloyd(const List<T>& list);

    // Метод разворота указателей для нахождения цикла
    template<typename T>
    friend bool CheckListCycleReverse(List<T>& list);

    // Метод Флойда + возврат начала цикла
    template<typename T>
    friend std::pair<bool, typename List<T>::Iterator>
        FindCycleStartFloyd(const List<T>& list);

    // Модификации для тестов

    void TEST_CreateCycle(int targetIndex) {
        if (empty() || targetIndex < 0 || targetIndex >= (int)size_) return;

        Node* target = head;
        for (int i = 0; i < targetIndex; i++) {
            target = target->next;
        }

        if (tail) {
            tail->next = target;
        }
    }

    void TEST_BreakCycle() {
        if (tail) {
            tail->next = nullptr;
        }
    }
};

// Iterator

// Конструктор итератора
template<typename T>
List<T>::Iterator::Iterator(Node* node) : current(node) {}

// Оператор разыменования
template<typename T>
T& List<T>::Iterator::operator*() { return current->data; }

// Оператор доступа к членам
template<typename T>
T* List<T>::Iterator::operator->() { return &current->data; }

// Префиксный инкремент (++it)
template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

// Постфиксный инкремент (it++)
template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    current = current->next;
    return temp;
}

// Оператор неравенства
template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const { return current != other.current; }

// Оператор равенства
template<typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const { return current == other.current; }

// List

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

// Добавление элемента в конец списка
template<typename T>
void List<T>::push_back(const T& value) {

    Node* newNode = new Node(value);

    if (empty()) head = tail = newNode;

    else { tail->next = newNode; tail = newNode; }

    size_++;
}

// Добавление элемента в начало списка
template<typename T>
void List<T>::push_front(const T& value) {

    Node* newNode = new Node(value);

    if (empty()) head = tail = newNode;

    else { newNode->next = head; head = newNode; }

    size_++;
}

// Удаление с начала списка
template<typename T>
void List<T>::pop_front() {

    if (empty()) throw std::runtime_error("List is empty!");

    Node* oldHead = head;
    head = head->next;

    if (!head) tail = nullptr;

    delete oldHead;
    size_--;
}


// Удаление с конца списка
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

// Очистка всего списка
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

// Получение первого элемента списка
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

// Получение последнего элемента списка
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

// Оператор присваивания
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

// Вставка элемента перед указанной позицией
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

        // Находим узел, предшествующий pos
        Node* current = head;
        while (current && current->next != pos.current) {
            current = current->next;
        }

        if (!current) {
            delete newNode;
            throw std::runtime_error("Invalid iterator!");
        }

        // Вставляем новый узел между current и pos.current
        newNode->next = current->next;
        current->next = newNode;

        size_++;
    }
}

// Удаление элемента на указанной позиции
template<typename T>
void List<T>::erase(const Iterator& pos) {
    if (pos == end() || empty()) {
        throw std::runtime_error("Invalid iterator!");
    }

    if (pos.current == head) {
        pop_front();
        return;
    }

    else if (pos.current == tail) {
        pop_back();
        return;
    }
    else {
        // Находим узел, предшествующий pos
        Node* current = head;
        while (current && current->next != pos.current) {
            current = current->next;
        }

        if (!current || !current->next) {
            throw std::runtime_error("Invalid iterator!");
        }

        Node* toDelete = current->next;

        // Перестраиваем связи
        current->next = toDelete->next;

        if (toDelete == tail) {
            tail = current;
        }
    
    delete toDelete;
    size_--;
    }
}

// Получение текущего размера списка
template<typename T>
size_t List<T>::size() const { return size_; }

// Проверка, пуст ли список
template<typename T>
bool List<T>::empty() const { return size_ == 0; }

// Получение итератора на первый элемент
template<typename T>
typename List<T>::Iterator List<T>::begin() { return Iterator(head); }

// Получение итератора на позицию после последнего элемента
template<typename T>
typename List<T>::Iterator List<T>::end() { return Iterator(nullptr); }
