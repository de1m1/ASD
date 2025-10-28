template <class T>
struct Node {
    T val;
    Node<T>* next;
    Node(T val_, Node<T>* next_ = nullptr) : val(val_), next(next_) {}
};

template <class T>
class list {
    Node<T>* _head, * _tail;
    int _count;
public:
    list() : _head(nullptr), _tail(nullptr), _count(0) {}
    list(const list& other);
    ~list();

    list& operator=(const list& other);

    void pop_front() noexcept;
    void push_front(const T& val) noexcept;
    void pop_back() noexcept;
    void push_back(const T& val) noexcept;
    void erase(int pos);
    void insert(int pos, const T& val);
    void erase(Node<T>* node);
    void insert(Node<T>* node, const T& val);
    bool is_empty();

    int size() const;
    T& front();
    T& back();
    Node<T>* begin() const;
    Node<T>* end() const;
};

// ���������� ������������ �����������
template <class T>
list<T>::list(const list& other) : _head(nullptr), _tail(nullptr), _count(0) {
    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->val);
        current = current->next;
    }
}

// ���������� �����������
template <class T>
list<T>::~list() {
    while (_head != nullptr) {
        Node<T>* temp = _head;
        _head = _head->next;
        delete temp;
    }
}

// ���������� ��������� ������������
template <class T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        while (_head != nullptr) {
            Node<T>* temp = _head;
            _head = _head->next;
            delete temp;
        }
        _tail = nullptr;
        _count = 0;

        Node<T>* current = other._head;
        while (current != nullptr) {
            push_back(current->val);
            current = current->next;
        }
    }
    return *this;
}

// ���������� pop_front
template <class T>
void list<T>::pop_front() noexcept {
    if (_head == nullptr) return;

    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
    _count--;

    if (_head == nullptr) {
        _tail = nullptr;
    }
}

// ���������� push_front
template <class T>
void list<T>::push_front(const T& val) noexcept {
    Node<T>* new_node = new Node<T>(val, _head);
    _head = new_node;

    if (_tail == nullptr) {
        _tail = _head;
    }
    _count++;
}

// ���������� pop_back
template <class T>
void list<T>::pop_back() noexcept {
    if (_head == nullptr) return;

    if (_head == _tail) {
        delete _head;
        _head = _tail = nullptr;
    }
    else {
        Node<T>* current = _head;
        while (current->next != _tail) {
            current = current->next;
        }
        delete _tail;
        _tail = current;
        _tail->next = nullptr;
    }
    _count--;
}

// ���������� push_back
template <class T>
void list<T>::push_back(const T& val) noexcept {
    Node<T>* new_node = new Node<T>(val);

    if (_tail == nullptr) {
        _head = _tail = new_node;
    }
    else {
        _tail->next = new_node;
        _tail = new_node;
    }
    _count++;
}

// ���������� erase �� �������
template <class T>
void list<T>::erase(int pos) {
    if (pos < 0 || pos >= _count) return;

    if (pos == 0) {
        pop_front();
        return;
    }

    Node<T>* current = _head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }

    Node<T>* to_delete = current->next;
    current->next = to_delete->next;

    if (to_delete == _tail) {
        _tail = current;
    }

    delete to_delete;
    _count--;
}

// ���������� insert �� �������
template <class T>
void list<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > _count) return;

    if (pos == 0) {
        push_front(val);
        return;
    }

    if (pos == _count) {
        push_back(val);
        return;
    }

    Node<T>* current = _head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->next;
    }

    Node<T>* new_node = new Node<T>(val, current->next);
    current->next = new_node;
    _count++;
}

// ���������� erase �� ����
template <class T>
void list<T>::erase(Node<T>* node) {
    if (node == nullptr || _head == nullptr) return;

    if (node == _head) {
        pop_front();
        return;
    }

    Node<T>* current = _head;
    while (current->next != node && current->next != nullptr) {
        current = current->next;
    }

    if (current->next == node) {
        current->next = node->next;

        if (node == _tail) {
            _tail = current;
        }

        delete node;
        _count--;
    }
}

// ���������� insert ����� ����
template <class T>
void list<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr) {
        push_back(val);
        return;
    }

    Node<T>* new_node = new Node<T>(val, node->next);
    node->next = new_node;

    if (node == _tail) {
        _tail = new_node;
    }
    _count++;
}

// ���������� is_empty
template <class T>
bool list<T>::is_empty() {
    return _head == nullptr;
}

// ���������� size
template <class T>
int list<T>::size() const {
    return _count;
}

// ���������� front
template <class T>
T& list<T>::front() {
    return _head->val;
}

// ���������� back
template <class T>
T& list<T>::back() {
    return _tail->val;
}

// ���������� begin
template <class T>
Node<T>* list<T>::begin() const {
    return _head;
}

// ���������� end
template <class T>
Node<T>* list<T>::end() const {
    return nullptr;
}