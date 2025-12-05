#include <stdexcept>
#include "list.h" 

template <class T>
class lstqueue {
    List<T> _queue;

public:
    // Конструкторы и деструктор
    lstqueue();
    lstqueue(const lstqueue<T>& other);
    ~lstqueue();

    // Оператор присваивания
    lstqueue<T>& operator=(const lstqueue<T>& other);

    // Добавление элемента в конец очереди
    void push(const T& val) noexcept;

    // Удаление элемента из начала очереди
    void pop();

    // Получение первого элемента
    T& front();
    const T& front() const;

    // Получение последнего элемента 
    T& back();
    const T& back() const;

    // Проверка на пустоту
    bool empty() const noexcept;

    // Получение размера очереди
    size_t size() const noexcept;

    // Очистка очереди
    void clear() noexcept;
};

// Конструкторы и деструктор
template <class T>
lstqueue<T>::lstqueue() : _queue() {}

template <class T>
lstqueue<T>::lstqueue(const lstqueue<T>& other) : _queue(other._queue) {}

template <class T>
lstqueue<T>::~lstqueue() {}

// Оператор присваивания
template <class T>
lstqueue<T>& lstqueue<T>::operator=(const lstqueue<T>& other) {
    if (this != &other) {
        _queue = other._queue;
    }
    return *this;
}

// Добавление элемента в конец очереди
template <class T>
void lstqueue<T>::push(const T& val) noexcept {
    _queue.push_back(val);
}

// Удаление элемента из начала очереди
template <class T>
void lstqueue<T>::pop() {
    if (empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    _queue.pop_front();
}

// Получение первого элемента очереди
template <class T>
T& lstqueue<T>::front() {
    if (empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    return *_queue.begin();
}

template <class T>
const T& lstqueue<T>::front() const {
    if (empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    return *_queue.begin();
}

// Получение последнего элемента очереди
template <class T>
T& lstqueue<T>::back() {
    if (empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    return _queue.back();
}

template <class T>
const T& lstqueue<T>::back() const {
    if (empty()) {
        throw std::logic_error("lstqueue is empty");
    }
    return _queue.back();
}

// Проверка на пустоту очереди
template <class T>
bool lstqueue<T>::empty() const noexcept {
    return _queue.empty();
}

// Получение размера очереди
template <class T>
size_t lstqueue<T>::size() const noexcept {
    return _queue.size();
}

// Очистка очереди
template <class T>
void lstqueue<T>::clear() noexcept {
    _queue.clear();
}