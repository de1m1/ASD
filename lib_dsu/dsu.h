#pragma once

class DSU {

	int* _parent;
	int _size;
	int* _rank;

public:

	DSU(int _size);

	void united(int, int);

	int find(int);

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
void DSU::united(int x1, int x2) {

	x1 = find(x1);
	x2 = find(x2);

	if (_rank[x1] < _rank[x2]) {
		_parent[x1] = x2;
	}
	else if (_rank[x1] == _rank[x2]) {
		_rank[x1]++;
		_parent[x2] = x1;
	}
	else {
		_parent[x2] = x1;
	}
}

// Деструктор
DSU::~DSU() { delete[] _parent; delete[] _rank; }

// Поиск
int DSU::find(int x) {
	if (_parent[x] == x) return x;
	else return find(_parent[x]);
}

