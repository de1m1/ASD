#pragma once
#include "itable.h"
#include "tvector.h"

template<typename TKey, typename TVal>
class UnsortedTableOnVec: public ITable{
private:
	TVector<std::pair<TKey, TVal>>_rows;
public:
	~UnsortedTableOnVec() {}
	UnsortedTableOnVec() {}

	void insert(const TKey& Key, const TVal& Val) override;
	TVal find(TKey& Key) override;
	void erase(const TKey& Key) override;
	ostream& print(ostream& out) const noexcept override;
	bool is_empty() const noexcept override;
	bool consirt(const TKey& Key) const noexcept override;
	void replace(const TKey& Key, const TVal& Val) override;

};

template<typename TKey, typename TVal>
inline void UnsortedTableOnVec<TKey, TVal>::insert(const TKey& Key, const TVal& Val){
}

template<typename TKey, typename TVal>
inline TVal UnsortedTableOnVec<TKey, TVal>::find(TKey& Key){
	return TVal();
}

template<typename TKey, typename TVal>
inline void UnsortedTableOnVec<TKey, TVal>::erase(const TKey& Key){
}

template<typename TKey, typename TVal>
inline ostream& UnsortedTableOnVec<TKey, TVal>::print(ostream& out) const noexcept{

}

template<typename TKey, typename TVal>
inline bool UnsortedTableOnVec<TKey, TVal>::is_empty() const noexcept{
	return false;
}

template<typename TKey, typename TVal>
inline bool UnsortedTableOnVec<TKey, TVal>::consirt(const TKey& Key) const noexcept{
	return false;
}

template<typename TKey, typename TVal>
inline void UnsortedTableOnVec<TKey, TVal>::replace(const TKey& Key, const TVal& Val){

}
