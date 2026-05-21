#pragma once
#include "tvector.h"
#include "itable.h"
#include "list.h"
#include <iostream>
#include <stdexcept>
#include <string>

template<typename TVal>
class HashTableChain : public ITable<std::string, TVal> {

private:

    TVector<List<std::pair<std::string, TVal>>> _rows;
    size_t _size;

    size_t h(const std::string& key) const noexcept;

public:

	HashTableChain(size_t capacity = 10) : _rows(capacity), _size(0) {}
    ~HashTableChain() {}

    void insert(const std::string& key, const TVal& val) override;
    void erase(const std::string& key) override;
    TVal& find(const std::string& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override { return _size == 0; }
    bool contains(const std::string& key) const noexcept override;
    void replace(const std::string& key, const TVal& val) override;

    size_t getsize() const noexcept {  return _size; }
    void clear();
};

template<typename TVal>
size_t HashTableChain<TVal>::h(const std::string& key) const noexcept {
    size_t hash = 0;
    for (auto sym : key) {
        hash += sym;
    }
    return hash % _rows.size();
}

template<typename TVal>
void HashTableChain<TVal>::insert(const std::string& key, const TVal& val) {
    size_t ind = h(key);

    for (auto it = _rows[ind].begin(); it != _rows[ind].end(); ++it) {
        if (it->first == key) {
            throw std::logic_error("Key already exists");
        }
    }
    _rows[ind].push_back({ key, val });
    _size++;
}

template<typename TVal>
void HashTableChain<TVal>::erase(const std::string& key) {
    size_t ind = h(key);

    for (auto it = _rows[ind].begin(); it != _rows[ind].end(); ++it) {
        if (it->first == key) {
            _rows[ind].erase(it);
            _size--;
            return;
        }
    }
    throw std::logic_error("Key not found");
}

template<typename TVal>
TVal& HashTableChain<TVal>::find(const std::string& key) {
    size_t ind = h(key);

    for (auto it = _rows[ind].begin(); it != _rows[ind].end(); ++it) {
        if (it->first == key) {
            return it->second;
        }
    }

    throw std::logic_error("Key not found");
}

template<typename TVal>
std::ostream& HashTableChain<TVal>::print(std::ostream& out) const noexcept {
    for (size_t i = 0; i < _rows.size(); i++) {
        out << "Bucket " << i << ": ";
        for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
            out << "[" << it->first << ":" << it->second << "] -> ";
        }
        out << "null\n";
    }
    return out;
}

template<typename TVal>
bool HashTableChain<TVal>::contains(const std::string& key) const noexcept {
    size_t ind = h(key);

    for (auto it = _rows[ind].begin(); it != _rows[ind].end(); ++it) {
        if (it->first == key) {
            return true;
        }
    }
    return false;
}

template<typename TVal>
void HashTableChain<TVal>::replace(const std::string& key, const TVal& val) {
    size_t ind = h(key);

    for (auto it = _rows[ind].begin(); it != _rows[ind].end(); ++it) {
        if (it->first == key) {
            it->second = val;
            return;
        }
    }

    throw std::logic_error("Key not found");
}

template<typename TVal>
void HashTableChain<TVal>::clear() {
    for (size_t i = 0; i < _rows.size(); i++) {
        _rows[i].clear();
    }
    _size = 0;
}