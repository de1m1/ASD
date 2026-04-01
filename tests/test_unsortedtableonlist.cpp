#include <gtest/gtest.h>
#include "unsortedtableonlist.h"

TEST(UnsortedTableOnList, canCreate) {
    UnsortedTableOnList<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(UnsortedTableOnList, insertAddsElement) {
    UnsortedTableOnList<int, int> table;
    table.insert(1, 100);

    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.contains(1));
}

TEST(UnsortedTableOnList, findReturnsValue) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");

    EXPECT_EQ(table.find(1), "one");
}

TEST(UnsortedTableOnList, findThrowsIfNotFound) {
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);

    EXPECT_THROW(table.find(5), std::runtime_error);
}

TEST(UnsortedTableOnList, eraseRemovesElement) {
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);

    table.erase(1);

    EXPECT_FALSE(table.contains(1));
}

TEST(UnsortedTableOnList, eraseDoesNothingIfNotFound) {
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);

    table.erase(5);

    EXPECT_TRUE(table.contains(1));
}

TEST(UnsortedTableOnList, replaceUpdatesValue) {
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "hello");

    table.replace(1, "hi");

    EXPECT_EQ(table.find(1), "hi");
}

TEST(UnsortedTableOnList, replaceThrowsIfNotFound) {
    UnsortedTableOnList<int, int> table;

    EXPECT_THROW(table.replace(5, 10), std::runtime_error);
}

TEST(UnsortedTableOnList, isEmptyAfterInsert) {
    UnsortedTableOnList<int, int> table;
    table.insert(1, 10);

    EXPECT_FALSE(table.is_empty());
}

TEST(UnsortedTableOnList, containsTrueIfExists) {
    UnsortedTableOnList<int, int> table;
    table.insert(42, 100);

    EXPECT_TRUE(table.contains(42));
}

TEST(UnsortedTableOnList, containsFalseIfNotExists) {
    UnsortedTableOnList<int, int> table;
    table.insert(42, 100);

    EXPECT_FALSE(table.contains(99));
}

TEST(UnsortedTableOnList, worksWithStringKeys) {
    UnsortedTableOnList<std::string, int> table;
    table.insert("apple", 5);

    EXPECT_EQ(table.find("apple"), 5);
}