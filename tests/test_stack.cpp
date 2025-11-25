#include <gtest/gtest.h>
#include "Stack.h"

TEST(TestStack, can_create_stack) {
    // Arrange & Act & Assert
    ASSERT_NO_THROW(stack<int> s(5));
}

TEST(TestStack, can_create_stack_with_default_size) {
    // Arrange & Act & Assert
    ASSERT_NO_THROW(stack<int> s);
}

TEST(TestStack, created_stack_is_empty) {
    // Arrange
    stack<int> s(5);

    // Act & Assert
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStack, can_push_element) {
    // Arrange
    stack<int> s(5);

    // Act & Assert
    ASSERT_NO_THROW(s.push(10));
}

TEST(TestStack, push_increases_size) {
    // Arrange
    stack<int> s(5);

    // Act
    s.push(10);

    // Assert
    EXPECT_EQ(s.size(), 1);
}

TEST(TestStack, can_pop_element) {
    // Arrange
    stack<int> s(5);
    s.push(10);

    // Act & Assert
    ASSERT_NO_THROW(s.pop());
}

TEST(TestStack, pop_decreases_size) {
    // Arrange
    stack<int> s(5);
    s.push(10);
    s.push(20);

    // Act
    s.pop();

    // Assert
    EXPECT_EQ(s.size(), 1);
}

TEST(TestStack, top_returns_correct_element) {
    // Arrange
    stack<int> s(5);
    s.push(10);
    s.push(20);

    // Act
    int actual_result = s.top();

    // Assert
    int expected_result = 20;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestStack, lifo_behavior) {
    // Arrange
    stack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    // Act & Assert
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(TestStack, can_clear_stack) {
    // Arrange
    stack<int> s(5);
    s.push(10);
    s.push(20);

    // Act
    s.clear();

    // Assert
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(TestStack, becomes_full_when_capacity_reached) {
    // Arrange
    stack<int> s(2);
    s.push(10);
    s.push(20);

    // Act & Assert
    EXPECT_TRUE(s.is_full());
}

TEST(TestStack, throw_when_pop_from_empty_stack) {
    // Arrange
    stack<int> s(5);

    // Act & Assert
    ASSERT_ANY_THROW(s.pop());
}

TEST(TestStack, throw_when_top_from_empty_stack) {
    // Arrange
    stack<int> s(5);

    // Act & Assert
    ASSERT_ANY_THROW(s.top());
}

TEST(TestStack, throw_when_push_to_full_stack) {
    // Arrange
    stack<int> s(2);
    s.push(10);
    s.push(20);

    // Act & Assert
    ASSERT_ANY_THROW(s.push(30));
}

TEST(TestStack, works_with_different_data_types) {
    // Arrange
    stack<double> s(3);

    // Act
    s.push(1.5);
    s.push(2.7);

    // Assert
    EXPECT_DOUBLE_EQ(s.top(), 2.7);
    s.pop();
    EXPECT_DOUBLE_EQ(s.top(), 1.5);
}

TEST(TestStack, default_constructor_has_correct_capacity) {
    // Arrange
    stack<int> s;

    // Act & Assert
    EXPECT_EQ(s.capacity(), 100);
}