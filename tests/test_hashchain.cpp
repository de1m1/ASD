#include "gtest/gtest.h"
#include "hashchain.h"

TEST(HashTableChain, InsertAndFind)
{
    HashTableChain<int> table(10);

    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    EXPECT_EQ(table.find("a"), 1);
    EXPECT_EQ(table.find("b"), 2);
    EXPECT_EQ(table.find("c"), 3);
}

TEST(HashTableChain, Contains)
{
    HashTableChain<int> table(10);

    table.insert("key", 100);

    EXPECT_TRUE(table.contains("key"));
    EXPECT_FALSE(table.contains("no_key"));
}

TEST(HashTableChain, Replace)
{
    HashTableChain<int> table(10);

    table.insert("x", 10);
    table.replace("x", 999);

    EXPECT_EQ(table.find("x"), 999);
}

TEST(HashTableChain, Erase)
{
    HashTableChain<int> table(10);

    table.insert("a", 1);
    table.insert("b", 2);

    table.erase("a");

    EXPECT_FALSE(table.contains("a"));
    EXPECT_TRUE(table.contains("b"));
}

TEST(HashTableChain, FindThrows)
{
    HashTableChain<int> table(10);

    EXPECT_THROW(table.find("missing"), std::logic_error);
}

TEST(HashTableChain, InsertDuplicateThrows)
{
    HashTableChain<int> table(10);

    table.insert("a", 1);

    EXPECT_THROW(table.insert("a", 2), std::logic_error);
}

TEST(HashTableChain, Clear)
{
    HashTableChain<int> table(10);

    table.insert("a", 1);
    table.insert("b", 2);

    EXPECT_FALSE(table.is_empty());

    table.clear();

    EXPECT_TRUE(table.is_empty());
    EXPECT_FALSE(table.contains("a"));
    EXPECT_FALSE(table.contains("b"));
}

TEST(HashTableChain, Size)
{
    HashTableChain<int> table(10);

    EXPECT_EQ(table.getsize(), 0);

    table.insert("a", 1);
    table.insert("b", 2);

    EXPECT_EQ(table.getsize(), 2);

    table.erase("a");

    EXPECT_EQ(table.getsize(), 1);
}