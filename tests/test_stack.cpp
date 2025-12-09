#include <gtest/gtest.h>
#include "Stack.h"

TEST(TestStack, default_constructor_has_correct_capacity) {
    stack<int> s;

    EXPECT_EQ(s.capacity(), 16);
}

TEST(TestStack, CreateStackEmpty) {
    stack<int> s(5);

    EXPECT_TRUE(s.is_empty());
}

TEST(TestStack, PushElem) {
    stack<int> s(5);

    ASSERT_NO_THROW(s.push(10));
    EXPECT_EQ(s.size(), 1);
}

TEST(TestStack, PopElem) {
    stack<int> s(1);
    s.push(10);

    ASSERT_NO_THROW(s.pop());
    s.push(20);

    s.pop();

    EXPECT_EQ(s.size(), 0);
}

TEST(TestStack, TopCorrect) {
    stack<int> s(5);
    s.push(10);
    s.push(20);

    int actual = s.top();

    int expected = 20;
    EXPECT_EQ(expected, actual);
}

TEST(TestStack, LIFO) {
    stack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(TestStack, ClearStack) {
    stack<int> s(5);
    s.push(10);
    s.push(20);

    s.clear();

    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(TestStack, FullStack) {
    stack<int> s(2);
    s.push(10);
    s.push(20);

    EXPECT_TRUE(s.is_full());
}
