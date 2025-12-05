#pragma once

class DSU {

	int* _parent;
	int _size;
	int* _rank;

public:
	// Конструктор
	DSU(int size);

	// Объединение двух множеств
	void united(int x, int y);

	// Найти корень множества
	int find(int x);

	// Находятся ли элементы в одном множестве
	bool connected(int x, int y);

	// Количество элементов
	size_t size() const;

	// Деструктор
	~DSU();

};

// Конструктор
DSU::DSU(int size) : _size(size) {
	_parent = new int[_size];
	_rank = new int[_size];
	for (int i = 0; i < _size; i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

// Объединение
void DSU::united(int x, int y) {

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
DSU::~DSU() { delete[] _parent; delete[] _rank; }

// Поиск
int DSU::find(int x) {
	if (_parent[x] == x) return x;
	else return _parent[x] = find(_parent[x]);
}

// Проверка связи между элементами
bool DSU::connected(int x, int y) {
	return find(x) == find(y);
}

// Получение размера
size_t DSU::size() const {
	return _size;
}