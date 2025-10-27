#pragma once

template <class T>
class Queue {
    T* _data;        // Указатель на массив элементов очереди
    int _head;       // Индекс начала очереди
    int _count;      // Количество элементов в очереди
    int _capacity;   // Вместимость очереди

public:
    // Конструктор с параметром размера
    Queue(int size);

    // Конструктор копирования
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
    inline T top() const;

    // Проверка на пустоту
    inline bool is_empty() const noexcept;

    // Проверка на полноту
    inline bool is_full() const noexcept;

    // Очистка очереди
    void clear() noexcept;

    // Получение количества элементов
    int size() const;

    // Получение индекса головы (для отладки)
    int head() const;

    // Получение количества элементов (дублирует size())
    int count() const;
};

// Реализация методов вне класса

// Конструктор с параметром размера
template <class T>
Queue<T>::Queue(int size)
    : _data(new T[size]),  // Выделяем память под массив
    _head(0),           // Начинаем с индекса 0
    _count(0),          // Очередь пуста
    _capacity(size)     // Запоминаем вместимость
{}

// Конструктор копирования
template <class T>
Queue<T>::Queue(const Queue& other)
    : _data(new T[other._capacity]),  // Выделяем новую память
    _head(other._head),
    _count(other._count),
    _capacity(other._capacity)
{
    // Копируем все элементы из исходного массива
    for (int i = 0; i < _capacity; ++i) {
        _data[i] = other._data[i];
    }
}

// Деструктор
template <class T>
Queue<T>::~Queue() {
    delete[] _data;  // Освобождаем память
}

// Оператор присваивания
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {  // Защита от самоприсваивания
        delete[] _data;    // Освобождаем старую память

        // Выделяем новую память и копируем данные
        _capacity = other._capacity;
        _data = new T[_capacity];
        _head = other._head;
        _count = other._count;

        // Копируем элементы
        for (int i = 0; i < _capacity; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

// Добавление элемента в конец очереди
template <class T>
void Queue<T>::push(const T& val) {
    // Вычисляем индекс хвоста: (голова + количество) % вместимость
    int tail = (_head + _count) % _capacity;
    _data[tail] = val;  // Записываем значение в хвост
    _count++;           // Увеличиваем счетчик элементов
}

// Удаление элемента из начала очереди
template <class T>
void Queue<T>::pop() {
    // Сдвигаем голову по кругу: (текущая голова + 1) % вместимость
    _head = (_head + 1) % _capacity;
    _count--;  // Уменьшаем счетчик элементов
}

// Получение элемента из начала очереди
template <class T>
T Queue<T>::top() const {
    return _data[_head];  // Возвращаем элемент в позиции головы
}

// Проверка на пустоту
template <class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;  // Очередь пуста, если счетчик равен 0
}

// Проверка на полноту
template <class T>
bool Queue<T>::is_full() const noexcept {
    return _count == _capacity;  // Очередь полна, если счетчик равен вместимости
}

// Очистка очереди
template <class T>
void Queue<T>::clear() noexcept {
    _head = 0;   // Сбрасываем голову в начало
    _count = 0;  // Обнуляем счетчик элементов
}

// Получение количества элементов
template <class T>
int Queue<T>::size() const {
    return _count;  // Возвращаем текущее количество элементов
}

// Получение индекса головы (для отладки)
template <class T>
int Queue<T>::head() const {
    return _head;  // Возвращаем индекс головы
}

// Получение количества элементов (дублирует size())
template <class T>
int Queue<T>::count() const {
    return _count;  // Возвращаем текущее количество элементов
}