#include <gtest/gtest.h>
#include "sortedtableonavltree.h"

TEST(SortedTableOnAVLTree, InsertAndFind){
    SortedTableOnAVLTree<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST(SortedTableOnAVLTree, Contains){
    SortedTableOnAVLTree<int, int> table;

    table.insert(10, 100);
    table.insert(20, 200);

    EXPECT_TRUE(table.contains(10));
    EXPECT_TRUE(table.contains(20));
    EXPECT_FALSE(table.contains(30));
}

TEST(SortedTableOnAVLTree, Erase){
    SortedTableOnAVLTree<int, int> table;

    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    table.erase(3);

    EXPECT_FALSE(table.contains(3));
    EXPECT_TRUE(table.contains(5));
    EXPECT_TRUE(table.contains(7));
}

TEST(SortedTableOnAVLTree, Replace){
    SortedTableOnAVLTree<int, std::string> table;

    table.insert(1, "one");

    table.replace(1, "ONE");

    EXPECT_EQ(table.find(1), "ONE");
}

TEST(SortedTableOnAVLTree, IsEmpty){
    SortedTableOnAVLTree<int, int> table;

    EXPECT_TRUE(table.is_empty());

    table.insert(1, 10);

    EXPECT_FALSE(table.is_empty());

    table.erase(1);

    EXPECT_TRUE(table.is_empty());
}

TEST(SortedTableOnAVLTree, EraseTwoChildren){
    SortedTableOnAVLTree<int, int> table;

    table.insert(10, 100);
    table.insert(5, 50);
    table.insert(15, 150);
    table.insert(3, 30);
    table.insert(7, 70);

    table.erase(5);

    EXPECT_FALSE(table.contains(5));
    EXPECT_TRUE(table.contains(3));
    EXPECT_TRUE(table.contains(7));
    EXPECT_TRUE(table.contains(10));
    EXPECT_TRUE(table.contains(15));
}

TEST(SortedTableOnAVLTree, FindThrows){
    SortedTableOnAVLTree<int, int> table;

    table.insert(1, 10);

    EXPECT_THROW(table.find(100), std::runtime_error);
}