#pragma once
#include<iostream>
using namespace std;

template <typename TKey, typename TVal>
class ITable {
public:
	~ITable(){}

	virtual void insert(const TKey& Key, const TVal& Val) = 0;
	virtual TVal find(const TKey& Key) = 0;
	virtual void erase(const TKey& Key) = 0;
	virtual ostream& print(ostream& out) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool contains(const TKey& Key) const noexcept = 0;
	virtual void replace(const TKey& Key, const TVal& Val) = 0;

};