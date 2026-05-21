#pragma once
#include "tvector.h"
#include "itable.h"
#include <string>
#include <stdexcept>

enum class Status{
	empty, occupied, deleted
};

template<typename TVal>
struct HashData {
    std::string key;
    TVal val;
    Status state;

    HashData() : key(""), val(), state(Status::empty) {}
    HashData(const std::string& k, const TVal& v): key(k), val(v), state(Status::occupied) {}
};

template <typename TVal>
class HashTableDouble : public ITable<std::string, TVal> {

private:

	TVector<HashData<TVal>> _rows;
    size_t _size;
    size_t _shift;

    size_t h(const std::string& key) const;
    size_t hh(size_t hash) const;

    void rehash();

public:

    HashTableDouble(size_t capacity = 10) : _rows(capacity), _size(0), _shift(1) {}
    ~HashTableDouble() override {}

    void insert(const std::string& key, const TVal& val) override;
    void erase(const std::string& key) override;
    TVal& find(const std::string& key) override;
    bool contains(const std::string& key) const noexcept override;
    void replace(const std::string& key, const TVal& val) override;
    bool is_empty() const noexcept override { return _size == 0; }
    std::ostream& print(std::ostream& out) const noexcept override;

    size_t getsize() const noexcept { return _size;}
    size_t capacity() const noexcept { return _rows.getsize(); }
    size_t get_shift() const noexcept { return _shift; }


};

template<typename TVal>
void HashTableDouble<TVal>::rehash(){
    TVector<HashData<TVal>> old_rows = _rows;

    size_t new_capacity = _rows.size() * 2;

    _rows = TVector<HashData<TVal>>(new_capacity);

    _size = 0;

    for (size_t i = 0; i < old_rows.size(); i++){
        if (old_rows[i].state == Status::occupied) {
            insert(old_rows[i].key, old_rows[i].val);
        }
    }
}

template <typename TVal>
size_t HashTableDouble<TVal>::h(const std::string& key) const {
    size_t hash = 0;
    for (char c : key)
        hash += c;
    return hash % _rows.size();
}

template <typename TVal>
size_t HashTableDouble<TVal>::hh(size_t hash) const {
    return _shift + (hash % (_rows.size() - 1));
}

template<typename TVal>
void HashTableDouble<TVal>::insert(const std::string& key, const TVal& val) {
    if (_size == _rows.size()) {
        rehash();
    }

    size_t ind = h(key);

    while (true) {
        if (_rows[ind].state == Status::empty || _rows[ind].state == Status::deleted) {
            _rows[ind] = HashData<TVal>(key, val);
            _size++;
            return;
        }

        if (_rows[ind].key == key) {
            throw std::logic_error("Key already exists");
        }
        ind = hh(ind);
    }
}

template<typename TVal>
void HashTableDouble<TVal>::erase(const std::string& key) {
    size_t ind = h(key);
    size_t start_ind = ind; // чтобы не зациклиться

    while (_rows[ind].state != Status::empty) {
        if (_rows[ind].state == Status::occupied && _rows[ind].key == key) {
            _rows[ind].state = Status::deleted;
            _size--;
            return;
        }

        ind = hh(ind);

        if (ind == start_ind) {
            break;
        }
    }

    throw std::logic_error("Key not found");
}

template<typename TVal>
TVal& HashTableDouble<TVal>::find(const std::string& key){
    size_t ind = h(key);
    size_t start_ind = ind;

    while (_rows[ind].state != Status::empty) {
        if (_rows[ind].state == Status::occupied && _rows[ind].key == key) {
            return _rows[ind].val;
        }

        ind = hh(ind);

        if (ind == start_ind) {
            break;
        }
    }

    throw std::logic_error("Key not found");
}

template<typename TVal>
std::ostream& HashTableDouble<TVal>::print(std::ostream& out) const noexcept {
    out << "Capacity: " << _rows.size() << ", Size: " << _size << ", Shift: " << _shift << "\n\n";

    for (size_t i = 0; i < _rows.size(); i++) {
        out << "[" << i << "] ";
        if (_rows[i].state == Status::occupied) {
            out << _rows[i].key << " : " << _rows[i].val;
        }
        else if (_rows[i].state == Status::deleted) {
            out << "DELETED";
        }
        else {
            out << "EMPTY";
        }
        out << "\n";
    }

    return out;
}

template<typename TVal>
bool HashTableDouble<TVal>::contains(
    const std::string& key) const noexcept
{
    size_t ind = h(key);
    size_t start_ind = ind;

    while (_rows[ind].state != Status::empty){
        if (_rows[ind].state == Status::occupied && _rows[ind].key == key){
            return true;
        }

        ind = hh(ind);

        if (ind == start_ind){
            break;
        }
    }

    return false;
}

template<typename TVal>
void HashTableDouble<TVal>::replace(const std::string& key, const TVal& val) {
    size_t ind = h(key);
    size_t start_ind = ind;

    while (_rows[ind].state != Status::empty) {
        if (_rows[ind].state == Status::occupied && _rows[ind].key == key) {
            _rows[ind].val = val;
            return;
        }

        ind = hh(ind);

        if (ind == start_ind) {
            break;
        }
    }
    throw std::logic_error("Key not found for replacement");
}
