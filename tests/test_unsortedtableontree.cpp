#include "gtest/gtest.h"
#include "unsortedtableontree.h"

TEST(UnsortedTreeTable, create_empty) {
    UnsortedTableOnTree<int, int> t;

    EXPECT_TRUE(t.is_empty());
}

TEST(UnsortedTreeTable, insert_and_find) {
    UnsortedTableOnTree<int, int> t;

    t.insert(5, 10);

    EXPECT_EQ(t.find(5), 10);
}

TEST(UnsortedTreeTable, contains_true) {
    UnsortedTableOnTree<int, int> t;

    t.insert(1, 100);

    EXPECT_TRUE(t.contains(1));
}

TEST(UnsortedTreeTable, contains_false) {
    UnsortedTableOnTree<int, int> t;

    t.insert(1, 100);

    EXPECT_FALSE(t.contains(2));
}

TEST(UnsortedTreeTable, erase_element) {
    UnsortedTableOnTree<int, int> t;

    t.insert(5, 10);
    t.insert(2, 20);

    t.erase(5);

    EXPECT_FALSE(t.contains(5));
}

TEST(UnsortedTreeTable, replace_value) {
    UnsortedTableOnTree<int, int> t;

    t.insert(3, 30);

    t.replace(3, 100);

    EXPECT_EQ(t.find(3), 100);
}

TEST(UnsortedTreeTable, insert_duplicate_should_throw) {
    UnsortedTableOnTree<int, int> t;

    t.insert(5, 10);

    EXPECT_THROW(t.insert(5, 20), std::runtime_error);
}

TEST(UnsortedTreeTable, find_missing_should_throw) {
    UnsortedTableOnTree<int, int> t;

    EXPECT_THROW(t.find(1), std::runtime_error);
}