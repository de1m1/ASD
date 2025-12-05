#include <gtest/gtest.h>
#include "queue.h"

TEST(TestQueue, CreateQueue) {
    ASSERT_NO_THROW(Queue<int> q(5));
}

TEST(TestQueue, CreateQueueEmpty) {
    Queue<int> q(5);

    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, PushElem) {
    Queue<int> q(2);

    q.push(10);

    ASSERT_NO_THROW(q.push(10));
    EXPECT_EQ(q.size(), 2);
}

TEST(TestQueue, PopElem) {
    Queue<int> q(1);
    q.push(10);

    ASSERT_NO_THROW(q.pop());

    q.push(20);

    q.pop();

    EXPECT_EQ(q.size(), 0);
}

TEST(TestQueue, ElemCorrect) {
    Queue<int> q(5);
    q.push(10);
    q.push(20);

    int actual = q.front();

    int expected = 10;
    EXPECT_EQ(expected, actual);
}

TEST(TestQueue, FIFO) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
}

TEST(TestQueue, ClearQueue) {
    Queue<int> q(5);
    q.push(10);
    q.push(20);

    q.clear();

    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(TestQueue, FullQueue) {
    Queue<int> q(2);
    q.push(10);
    q.push(20);

    EXPECT_TRUE(q.is_full());
}

TEST(TestQueue, CircularWorkCorrect) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    q.pop();
    q.pop();

    q.push(4);
    q.push(5);

    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_EQ(q.front(), 4);
    q.pop();
    EXPECT_EQ(q.front(), 5);
}

TEST(TestQueue, ThrowPush) {
    Queue<int> q(2);
    q.push(10);
    q.push(20);

    ASSERT_THROW(q.push(30), std::overflow_error);
}

TEST(TestQueue, ThrowPop) {
    Queue<int> q(5);

    ASSERT_THROW(q.pop(), std::overflow_error);
}

TEST(TestQueue, ThrowFront) {
    Queue<int> q(5);

    ASSERT_THROW(q.front(), std::underflow_error);
}

TEST(TestQueue, CopyConstructor) {
    Queue<int> q1(5);
    q1.push(1);
    q1.push(2);
    q1.push(3);

    Queue<int> q2 = q1;

    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 1);
    q2.pop();
    EXPECT_EQ(q2.front(), 2);
}

TEST(TestQueue, AssigmentOperator) {
    Queue<int> q1(5), q2(3);
    q1.push(10);
    q1.push(20);
    q1.push(30);

    q2 = q1;

    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 10);
}