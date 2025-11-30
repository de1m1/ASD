#include "gtest/gtest.h"
#include "dsu.h"

TEST(DSUTest, EqualUnion) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(2, 3);

	EXPECT_EQ(dsu.find(0), dsu.find(1));
	EXPECT_EQ(dsu.find(2), dsu.find(3));
	EXPECT_EQ(dsu.find(4), 4);
}

TEST(DSUTest, NotEqualUnion) {
	DSU dsu(6);

	dsu.united(4, 5);
	dsu.united(1, 3);
	dsu.united(0, 2);

	EXPECT_NE(dsu.find(0), dsu.find(1));
	EXPECT_NE(dsu.find(2), dsu.find(4));
	EXPECT_NE(dsu.find(3), dsu.find(5));

}

TEST(DSUTest, Transitivnost) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(1, 2);

	EXPECT_EQ(dsu.find(0), dsu.find(1));
	EXPECT_EQ(dsu.find(1), dsu.find(2));
	EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(DSUTest, ChainStructure) {
	DSU dsu(3);

	dsu.united(1, 0);
	dsu.united(2, 1);

	int root = dsu.find(0);
	EXPECT_EQ(dsu.find(1), root);
	EXPECT_EQ(dsu.find(2), root);
}

TEST(DSUTest, FindAfterMultipleUnions) {
	DSU dsu(5);

	dsu.united(0, 1);
	dsu.united(2, 3);
	dsu.united(0, 2);

	EXPECT_EQ(dsu.find(0), dsu.find(1));
	EXPECT_EQ(dsu.find(0), dsu.find(2));
	EXPECT_EQ(dsu.find(0), dsu.find(3));
	EXPECT_EQ(dsu.find(4), 4);
}