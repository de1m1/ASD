#include <gtest/gtest.h>
#include "algorithms.h"
#include "list.h"


// Тесты скобки Stack
TEST(BracketsTest, CorrectSequence) {
    EXPECT_TRUE(check_brackets("({[]})"));
}

TEST(BracketsTest, IncorrectSequence) {
    EXPECT_FALSE(check_brackets("({[}])"));
}

TEST(BracketsTest, EmptyString) {
    EXPECT_TRUE(check_brackets(""));
}

// Тесты задача DSU
TEST(IslandCounterTest, ExampleFromTask) {

	vector<vector<int>> grid = {
		{0, 1, 0, 0, 1},
		{0, 1, 1, 0, 1},
		{1, 1, 0, 1, 1},
		{0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1}
	};

	EXPECT_EQ(countIslands(grid), 3);
}

TEST(IslandCounterTest, EmptyGrid) {

	vector<vector<int>> emptyGrid;
	EXPECT_EQ(countIslands(emptyGrid), 0);
}

TEST(IslandCounterTest, SingleLargeIsland) {

	vector<vector<int>> grid = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};

	EXPECT_EQ(countIslands(grid), 1);
}

TEST(IslandCounterTest, NoDiagonalConnection) {

	vector<vector<int>> grid = {
		{1, 0, 1},
		{0, 0, 0},
		{1, 0, 1}
	};

	EXPECT_EQ(countIslands(grid), 4);
}

TEST(IslandCounterTest, ComplexShapedIsland) {

	vector<vector<int>> grid = {
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	};

	EXPECT_EQ(countIslands(grid), 1);
}

// Тесты для методов нахождения цикла в списке
// 1 - метод Флойда

TEST(CycleTest, EmptyList) {
	List<int> list;
	EXPECT_FALSE(CheckListCycleFloyd(list));
}

TEST(CycleTest, SingleElementNoCycle) {
	List<int> list;
	list.push_back(42);
	EXPECT_FALSE(CheckListCycleFloyd(list));
}

TEST(CycleTest, ManyElementsNoCycle) {
	List<int> list;
	for (int i = 0; i < 10; i++) {
		list.push_back(i);
	}
	EXPECT_FALSE(CheckListCycleFloyd(list));
}

TEST(CycleFloydTest, WithCycleUsingTestMethods) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	list.TEST_CreateCycle(2);

	EXPECT_TRUE(CheckListCycleFloyd(list));

	list.TEST_BreakCycle();

	EXPECT_FALSE(CheckListCycleFloyd(list));
}


// 2 - метод разворота указателей

TEST(CycleReverseTest, EmptyList) {
	List<int> list;
	EXPECT_FALSE(CheckListCycleReverse(list));
}

TEST(CycleReverseTest, SingleElementNoCycle) {
	List<int> list;
	list.push_back(42);
	EXPECT_FALSE(CheckListCycleReverse(list));
}

TEST(CycleReverseTest, ElementsNoCycle) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_FALSE(CheckListCycleReverse(list));
}

TEST(CycleReverseTest, WithCycleUsingTestMethods) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	list.TEST_CreateCycle(2);

	EXPECT_TRUE(CheckListCycleReverse(list));

	list.TEST_BreakCycle();

	EXPECT_FALSE(CheckListCycleReverse(list));
}

// 3 - метод зайца и черепахи + вовращение начала цикла

TEST(CycleFindStartTest, NoCycle) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	auto result = FindCycleStartFloyd(list);
	EXPECT_FALSE(result.first);
	EXPECT_EQ(result.second, list.end());
}

TEST(CycleFindStartTest, CycleToHead) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);

	list.TEST_CreateCycle(0);

	auto result = FindCycleStartFloyd(list);
	EXPECT_TRUE(result.first);

	EXPECT_NE(result.second, list.end());
	EXPECT_EQ(*result.second, 1);

	list.TEST_BreakCycle();
}

TEST(CycleFindStartTest, CycleToMiddle) {
	List<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	list.push_back(50);

	list.TEST_CreateCycle(2);

	auto result = FindCycleStartFloyd(list);
	EXPECT_TRUE(result.first);

	EXPECT_NE(result.second, list.end());

	auto it = list.begin();
	++it; 
	++it;
	EXPECT_EQ(result.second, it);
	EXPECT_EQ(*result.second, 30);

	list.TEST_BreakCycle();
}