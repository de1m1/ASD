#pragma once
#include "itable.h"
#include "tvector.h"
#include <utility>

template<typename TKey, typename TVal>
class UnsortedTableOnVec: public ITable<TKey, TVal>{
private:
	TVector<std::pair<TKey, TVal>>_rows;
public:
	~UnsortedTableOnVec() {}
	UnsortedTableOnVec() {}

	void insert(const TKey& Key, const TVal& Val) override;
	TVal find( const TKey& Key) override;
	void erase(const TKey& Key) override;
	ostream& print(ostream& out) const noexcept override;
	bool is_empty() const noexcept override;
	bool contains(const TKey& Key) const noexcept override;
	void replace(const TKey& Key, const TVal& Val) override;

};

template<typename TKey, typename TVal>
void UnsortedTableOnVec<TKey, TVal>::insert(const TKey& Key, const TVal& Val) {
	_rows.push_back(make_pair(Key, Val));
}

template<typename TKey, typename TVal>
TVal UnsortedTableOnVec<TKey, TVal>::find(const TKey& Key) {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == Key) {
            return _rows[i].second;
        }
    }
    throw runtime_error("Key not found");
}

template<typename TKey, typename TVal>
void UnsortedTableOnVec<TKey, TVal>::erase(const TKey& Key) {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == Key) {
            for (size_t j = i; j < _rows.size() - 1; ++j) {
                _rows[j] = _rows[j + 1];
            }
            _rows.pop_back();
            return;
        }
    }
}

template<typename TKey, typename TVal>
ostream& UnsortedTableOnVec<TKey, TVal>::print(ostream& out) const noexcept {
    for (size_t i = 0; i < _rows.size(); ++i) {
        out << "Key: " << _rows[i].first << ", Value: " << _rows[i].second << endl;
    }
    return out;
}

template<typename TKey, typename TVal>
bool UnsortedTableOnVec<TKey, TVal>::is_empty() const noexcept {
    return _rows.size() == 0;
}

template<typename TKey, typename TVal>
bool UnsortedTableOnVec<TKey, TVal>::contains(const TKey& Key) const noexcept {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == Key) {
            return true;
        }
    }
    return false;
}

template<typename TKey, typename TVal>
void UnsortedTableOnVec<TKey, TVal>::replace(const TKey& Key, const TVal& Val) {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == Key) {
            _rows[i].second = Val;
            return;
        }
    }
    throw runtime_error("Key not found");
}