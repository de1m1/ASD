#include"gtest/gtest.h"
#include"avltree.h"

TEST(AVLTree, InsertAndFind) {
    AVLTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    EXPECT_EQ(tree.find(5), "five");
    EXPECT_EQ(tree.find(3), "three");
    EXPECT_EQ(tree.find(7), "seven");
}

TEST(AVLTree, InsertOtherKey) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "old");
    tree.insert(10, "new");

    EXPECT_EQ(tree.find(10), "new");
}

TEST(AVLTree, Contains) {
    AVLTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(10, "ten");

    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_FALSE(tree.contains(100));
}

TEST(AVLTree, FindThrows) {
    AVLTree<int, std::string> tree;

    tree.insert(1, "one");

    EXPECT_THROW(tree.find(100), std::runtime_error);
}

TEST(AVLTree, Erase) {
    AVLTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    tree.erase(3);

    EXPECT_FALSE(tree.contains(3));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(7));
}

TEST(AVLTree, EraseOneChild) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(3, "three");

    tree.erase(5);

    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(10));
}

TEST(AVLTree, EraseTwoChildren) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    tree.erase(5);

    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(15));
}

TEST(AVLTree, EraseRoot) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");

    tree.erase(10);

    EXPECT_FALSE(tree.contains(10));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(15));
}

TEST(AVLTree, Empty) {
    AVLTree<int, std::string> tree;

    EXPECT_TRUE(tree.empty());

    tree.insert(1, "one");

    EXPECT_FALSE(tree.empty());
}