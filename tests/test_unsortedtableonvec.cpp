#include "UnsortedTableOnVec.h"
#include <gtest/gtest.h>

TEST(UnsortedTableOnVec, insert_adds_element) {
    UnsortedTableOnVec<int, int> table;
    table.insert(1, 100);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.contains(1));
}

TEST(UnsortedTableOnVec, find_throws_if_not_found) {
    UnsortedTableOnVec<int, double> table;
    table.insert(1, 1.1);
    int key = 5;
    EXPECT_THROW(table.find(key), runtime_error);
}

TEST(UnsortedTableOnVec, erase_removes_element) {
    UnsortedTableOnVec<int, char> table;
    table.insert(1, 'a');
    table.erase(1);
    EXPECT_FALSE(table.contains(1));
}

TEST(UnsortedTableOnVec, replace_updates_value) {
    UnsortedTableOnVec<int, string> table;
    table.insert(1, "hello");
    table.replace(1, "hi");
    int key = 1;
    EXPECT_EQ(table.find(key), "hi");
}

TEST(UnsortedTableOnVec, replace_throws_if_not_found) {
    UnsortedTableOnVec<int, double> table;
    table.insert(1, 1.1);
    EXPECT_THROW(table.replace(10, 10.10), runtime_error);
}

TEST(UnsortedTableOnVec, is_empty_true_for_new_table) {
    UnsortedTableOnVec<int, int> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(UnsortedTableOnVec, can_store_duplicate_keys) {
    UnsortedTableOnVec<int, string> table;
    table.insert(1, "first");
    EXPECT_ANY_THROW(table.insert(1, "second"));
}

TEST(UnsortedTableOnVec, works_with_string_keys) {
    UnsortedTableOnVec<string, int> table;
    table.insert("apple", 5);
    std::string key = "apple";
    EXPECT_EQ(table.find(key), 5);
}