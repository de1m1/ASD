#include <gtest/gtest.h>
#include "binarysearchtree.h"

TEST(BSTreeTest, InsertAndFind) {

    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    std::string val;

    EXPECT_TRUE(tree.find(5, val));
    EXPECT_EQ(val, "five");

    EXPECT_TRUE(tree.find(3, val));
    EXPECT_EQ(val, "three");

    EXPECT_TRUE(tree.find(7, val));
    EXPECT_EQ(val, "seven");
}

TEST(BSTreeTest, FindNonExisting) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 2);

    int val;

    EXPECT_FALSE(tree.find(10, val));
}

TEST(BSTreeTest, EraseLeaf) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(7, 1);

    tree.erase(3);

    int val;

    EXPECT_FALSE(tree.find(3, val));
    EXPECT_TRUE(tree.find(5, val));
    EXPECT_TRUE(tree.find(7, val));
}

TEST(BSTreeTest, EraseNodeWithOneChild) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(4, 1);

    tree.erase(3);

    int val;

    EXPECT_FALSE(tree.find(3, val));
    EXPECT_TRUE(tree.find(4, val));
}

TEST(BSTreeTest, EraseNodeWithTwoChildren) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(7, 1);
    tree.insert(2, 1);
    tree.insert(4, 1);

    tree.erase(3);

    int val;

    EXPECT_FALSE(tree.find(3, val));
    EXPECT_TRUE(tree.find(2, val));
    EXPECT_TRUE(tree.find(4, val));
}

TEST(BSTreeTest, EraseRoot) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(7, 1);

    tree.erase(5);

    int val;

    EXPECT_FALSE(tree.find(5, val));
    EXPECT_TRUE(tree.find(3, val));
    EXPECT_TRUE(tree.find(7, val));
}

TEST(BSTreeTest, EmptyTree) {

    BSTree<int, int> tree;

    EXPECT_TRUE(tree.empty());

    tree.insert(1, 1);

    EXPECT_FALSE(tree.empty());
}