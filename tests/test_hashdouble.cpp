#include <gtest/gtest.h>
#include "hashdouble.h"

TEST(HashTableDouble, InsertAndFind)
{
    HashTableDouble<int> table;

    table.insert("a", 10);
    table.insert("b", 20);

    EXPECT_EQ(table.find("a"), 10);
    EXPECT_EQ(table.find("b"), 20);
}

TEST(HashTableDouble, Contains)
{
    HashTableDouble<int> table;

    table.insert("x", 100);

    EXPECT_TRUE(table.contains("x"));
    EXPECT_FALSE(table.contains("y"));
}

TEST(HashTableDouble, Replace)
{
    HashTableDouble<int> table;

    table.insert("key", 1);
    table.replace("key", 999);

    EXPECT_EQ(table.find("key"), 999);
}

TEST(HashTableDouble, Erase)
{
    HashTableDouble<int> table;

    table.insert("del", 5);
    table.erase("del");

    EXPECT_FALSE(table.contains("del"));
}

TEST(HashTableDouble, EraseThrows)
{
    HashTableDouble<int> table;

    EXPECT_THROW(table.erase("not_exist"), std::logic_error);
}

TEST(HashTableDouble, FindThrows)
{
    HashTableDouble<int> table;

    EXPECT_THROW(table.find("nope"), std::logic_error);
}

TEST(HashTableDouble, InsertDuplicateThrows)
{
    HashTableDouble<int> table;

    table.insert("dup", 1);

    EXPECT_THROW(table.insert("dup", 2), std::logic_error);
}

TEST(HashTableDouble, IsEmpty)
{
    HashTableDouble<int> table;

    EXPECT_TRUE(table.is_empty());

    table.insert("a", 1);

    EXPECT_FALSE(table.is_empty());
}

TEST(HashTableDouble, RehashWorks)
{
    HashTableDouble<int> table(2);

    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    EXPECT_EQ(table.find("a"), 1);
    EXPECT_EQ(table.find("b"), 2);
    EXPECT_EQ(table.find("c"), 3);
}

TEST(HashTableDouble, ReplaceThrows)
{
    HashTableDouble<int> table;

    EXPECT_THROW(table.replace("no_key", 10), std::logic_error);
}