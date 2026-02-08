#pragma once

class DSU {

	int* _parent;
	int _size;
	int* _rank;

public:
	// Конструктор
	inline DSU(int size);

	// Объединение двух множеств
	inline void unite(int x, int y);

	// Найти корень множества
	inline int find(int x);

	// Находятся ли элементы в одном множестве
	inline bool is_connected(int x, int y);

	// Количество элементов
	inline size_t size() const;

	// Деструктор
	inline ~DSU();
};

// Конструктор
inline DSU::DSU(int size) : _size(size) {
	_parent = new int[_size];
	_rank = new int[_size];
	for (int i = 0; i < _size; i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

// Объединение
inline void DSU::unite(int x, int y) {

	x = find(x);
	y = find(y);

	if (x == y) return;

	if (_rank[x] < _rank[y]) {
		_parent[x] = y;
	}
	else if (_rank[x] == _rank[y]) {
		_rank[x]++;
		_parent[y] = x;
	}
	else {
		_parent[y] = x;
	}
}

// Деструктор
inline DSU::~DSU() { delete[] _parent; delete[] _rank; }

// Поиск
inline int DSU::find(int x) {
	if (_parent[x] == x) return x;
	else return _parent[x] = find(_parent[x]);
}

// Проверка связи между элементами
inline bool DSU::is_connected(int x, int y) {
	return find(x) == find(y);
}

// Получение размера
inline size_t DSU::size() const {
	return _size;
}