#include <gtest/gtest.h>
#include "liststack.h"
#include "listqueue.h"

TEST(StackTest, Empty) {
    lststack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, PushTop) {
    lststack<int> s;
    s.push(42);
    EXPECT_EQ(s.top(), 42);
    EXPECT_EQ(s.size(), 1);
}

TEST(StackTest, PushPop) {
    lststack<int> s;
    s.push(1);
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, LIFO) {
    lststack<int> s;
    s.push(1);
    s.push(2);
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(QueueTest, Empty) {
    lstqueue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PushFrontCheck) {
    lstqueue<int> q;
    q.push(42);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 42);
}

TEST(QueueTest, PushPop) {
    lstqueue<int> q;
    q.push(10);
    q.pop();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}
    
TEST(QueueTest, FIFO) {
    lstqueue<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
}