#include <gtest/gtest.h>
#include "binarysearchtree.h"

TEST(BSTreeTest, InsertAndFind) {

    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    EXPECT_EQ(tree.find(5), "five");
    EXPECT_EQ(tree.find(3), "three");
    EXPECT_EQ(tree.find(7), "seven");
}

TEST(BSTreeTest, FindNonExisting) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 2);

    EXPECT_THROW(tree.find(10), std::runtime_error);
}

TEST(BSTreeTest, EraseLeaf) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(7, 1);

    tree.erase(3);

    EXPECT_THROW(tree.find(3), std::runtime_error);
    EXPECT_EQ(tree.find(5), 1);
    EXPECT_EQ(tree.find(7), 1);
}

TEST(BSTreeTest, EraseNodeWithOneChild) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(4, 1);

    tree.erase(3);

    EXPECT_THROW(tree.find(3), std::runtime_error);
    EXPECT_EQ(tree.find(4), 1);
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

    EXPECT_THROW(tree.find(3), std::runtime_error);
    EXPECT_EQ(tree.find(2), 1);
    EXPECT_EQ(tree.find(4), 1);
}

TEST(BSTreeTest, EraseRoot) {

    BSTree<int, int> tree;

    tree.insert(5, 1);
    tree.insert(3, 1);
    tree.insert(7, 1);

    tree.erase(5);

    EXPECT_THROW(tree.find(5), std::runtime_error);
    EXPECT_EQ(tree.find(3), 1);
    EXPECT_EQ(tree.find(7), 1);
}

TEST(BSTreeTest, EmptyTree) {

    BSTree<int, int> tree;

    EXPECT_TRUE(tree.empty());

    tree.insert(1, 1);

    EXPECT_FALSE(tree.empty());
}