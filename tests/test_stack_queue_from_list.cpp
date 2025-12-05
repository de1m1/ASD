#include <gtest/gtest.h>
#include "liststack.h"
#include "listqueue.h"

// Тесты для Stack

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

TEST(StackTest, PopEmptyThrows) {
    lststack<int> s;
    EXPECT_THROW(s.pop(), std::logic_error);
}

TEST(StackTest, TopEmptyThrows) {
    lststack<int> s;
    EXPECT_THROW(s.top(), std::logic_error);
}

TEST(StackTest, AssignmentOperator) {
    lststack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    lststack<int> s2;
    s2.push(99);

    s2 = s1;

    EXPECT_EQ(s2.size(), 3); 
    EXPECT_EQ(s2.top(), 30);

    EXPECT_EQ(s2.top(), 30);
    s2.pop();
    EXPECT_EQ(s2.top(), 20);
    s2.pop();
    EXPECT_EQ(s2.top(), 10);

    s1.pop();
    EXPECT_EQ(s1.top(), 20);
    EXPECT_EQ(s2.top(), 10);
}

// Тесты для Queue

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

TEST(QueueTest, FrontEmptyThrows) {
    lstqueue<int> q;
    EXPECT_THROW(q.front(), std::logic_error); 
}

TEST(QueueTest, BackEmptyThrows) {
    lstqueue<int> q;
    EXPECT_THROW(q.back(), std::logic_error); 
}

TEST(QueueTest, AssignmentOperator) {
    lstqueue<int> q1;
    q1.push(10);
    q1.push(20);

    lstqueue<int> q2;
    q2.push(99);

    q2 = q1;

    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 10);

    q1.pop();
    EXPECT_EQ(q1.front(), 20);
    EXPECT_EQ(q2.front(), 10);
}