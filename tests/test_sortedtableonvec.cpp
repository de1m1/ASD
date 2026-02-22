#include "SortedTableOnVec.h"
#include <gtest/gtest.h>

TEST(SortedTableOnVec, can_create) {
    SortedTableOnVec<int, float> table;
    table.insert(10, 3.14);
}

TEST(SortedTableOnVec, insert_adds_element) {
    SortedTableOnVec<int, int> table;
    table.insert(1, 100);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.contains(1));
}

TEST(SortedTableOnVec, insert_keeps_order) {
    SortedTableOnVec<int, int> table;
    table.insert(5, 50);
    table.insert(1, 10);
    table.insert(3, 30);

    int k1 = 1, k2 = 3, k3 = 5;

    EXPECT_EQ(table.find(k1), 10);
    EXPECT_EQ(table.find(k2), 30);
    EXPECT_EQ(table.find(k3), 50);
}

TEST(SortedTableOnVec, insert_throws_if_duplicate) {
    SortedTableOnVec<int, int> table;
    table.insert(1, 10);
    EXPECT_THROW(table.insert(1, 20), runtime_error);
}

TEST(SortedTableOnVec, find_returns_value) {
    SortedTableOnVec<int, string> table;
    table.insert(1, "one");
    int key = 1;
    EXPECT_EQ(table.find(key), "one");
}

TEST(SortedTableOnVec, find_throws_if_not_found) {
    SortedTableOnVec<int, double> table;
    table.insert(1, 1.1);
    int key = 5;
    EXPECT_THROW(table.find(key), runtime_error);
}

TEST(SortedTableOnVec, erase_removes_element) {
    SortedTableOnVec<int, char> table;
    table.insert(1, 'a');
    table.erase(1);
    EXPECT_FALSE(table.contains(1));
}

TEST(SortedTableOnVec, erase_does_nothing_if_not_found) {
    SortedTableOnVec<int, int> table;
    table.insert(1, 10);
    table.erase(5);
    EXPECT_TRUE(table.contains(1));
}

TEST(SortedTableOnVec, replace_updates_value) {
    SortedTableOnVec<int, string> table;
    table.insert(1, "hello");
    table.replace(1, "hi");
    int key = 1;
    EXPECT_EQ(table.find(key), "hi");
}

TEST(SortedTableOnVec, replace_throws_if_not_found) {
    SortedTableOnVec<int, double> table;
    table.insert(1, 1.1);
    EXPECT_THROW(table.replace(10, 10.10), runtime_error);
}

TEST(SortedTableOnVec, is_empty_true_for_new_table) {
    SortedTableOnVec<int, int> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(SortedTableOnVec, is_empty_false_after_insert) {
    SortedTableOnVec<int, int> table;
    table.insert(1, 10);
    EXPECT_FALSE(table.is_empty());
}

TEST(SortedTableOnVec, contains_true_if_key_exists) {
    SortedTableOnVec<int, int> table;
    table.insert(42, 100);
    EXPECT_TRUE(table.contains(42));
}

TEST(SortedTableOnVec, contains_false_if_key_not_exists) {
    SortedTableOnVec<int, int> table;
    table.insert(42, 100);
    EXPECT_FALSE(table.contains(99));
}

TEST(SortedTableOnVec, works_with_string_keys) {
    SortedTableOnVec<string, int> table;
    table.insert("apple", 5);
    string key = "apple";
    EXPECT_EQ(table.find(key), 5);
}