#include "gtest/gtest.h"
#include "dsu.h"

// Teсты для DSU

TEST(DSUTest, InitialState) {
	DSU dsu(5);

	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(dsu.find(i), i);
	}
}

TEST(DSUTest, BasicUnionFind) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(2, 3);

	EXPECT_EQ(dsu.find(0), dsu.find(1)); 
	EXPECT_EQ(dsu.find(2), dsu.find(3));  
	EXPECT_NE(dsu.find(0), dsu.find(2)); 
	EXPECT_EQ(dsu.find(4), 4);  
}

TEST(DSUTest, Transitivnost) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(1, 2);

	EXPECT_EQ(dsu.find(0), dsu.find(1));
	EXPECT_EQ(dsu.find(1), dsu.find(2));
	EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(DSUTest, RepeatedUnion) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(0, 1);
	dsu.united(1, 0);

	EXPECT_EQ(dsu.find(0), dsu.find(1));
}

TEST(DSUTest, PathCompressionParentNew) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(1, 2);

	int root = dsu.find(2);

	EXPECT_EQ(dsu.find(0), root);
	EXPECT_EQ(dsu.find(1), root);
}

TEST(DSUTest, UnionALot) {
	DSU dsu(10);

	dsu.united(0, 1);
	dsu.united(2, 3);
	dsu.united(1, 2);

	dsu.united(4, 5);
	dsu.united(5, 6);

	dsu.united(0, 4);

	for (int i = 0; i <= 6; i++) {
		EXPECT_EQ(dsu.find(i), dsu.find(0));
	}

	EXPECT_NE(dsu.find(7), dsu.find(0));
}