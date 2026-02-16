#pragma once
#include "itable.h"
#include "tvector.h"
#include <utility>

template<typename TKey, typename TVal>
class SortedTableOnVec : public ITable<TKey, TVal> {
	TVector<std::pair<TKey, TVal>>_rows;
public:
	~SortedTableOnVec() {}
	SortedTableOnVec() {}
};