#include <gtest/gtest.h>
#include "sortedtableonsearchtree.h"

TEST(SortedTableOnSearchTree, InsertAndFind)
{
    SortedTableOnSearchTree<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST(SortedTableOnSearchTree, Contains)
{
    SortedTableOnSearchTree<int, int> table;

    table.insert(10, 100);
    table.insert(20, 200);

    EXPECT_TRUE(table.contains(10));
    EXPECT_TRUE(table.contains(20));
    EXPECT_FALSE(table.contains(30));
}

TEST(SortedTableOnSearchTree, Erase)
{
    SortedTableOnSearchTree<int, int> table;

    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    table.erase(3);

    EXPECT_FALSE(table.contains(3));
    EXPECT_TRUE(table.contains(5));
    EXPECT_TRUE(table.contains(7));
}

TEST(SortedTableOnSearchTree, Replace)
{
    SortedTableOnSearchTree<int, std::string> table;

    table.insert(1, "one");

    table.replace(1, "ONE");

    EXPECT_EQ(table.find(1), "ONE");
}

TEST(SortedTableOnSearchTree, IsEmpty)
{
    SortedTableOnSearchTree<int, int> table;

    EXPECT_TRUE(table.is_empty());

    table.insert(1, 10);

    EXPECT_FALSE(table.is_empty());

    table.erase(1);

    EXPECT_TRUE(table.is_empty());
}