#include <gtest/gtest.h>
#include "Queue.h"

TEST(TestQueue, can_create_queue) {
    // Arrange & Act & Assert
    ASSERT_NO_THROW(Queue<int> q(5));
}

TEST(TestQueue, created_queue_is_empty) {
    // Arrange
    Queue<int> q(5);

    // Act & Assert
    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueue, can_push_element) {
    // Arrange
    Queue<int> q(5);

    // Act & Assert
    ASSERT_NO_THROW(q.push(10));
}

TEST(TestQueue, push_increases_size) {
    // Arrange
    Queue<int> q(5);

    // Act
    q.push(10);

    // Assert
    EXPECT_EQ(q.size(), 1);
}

TEST(TestQueue, can_pop_element) {
    // Arrange
    Queue<int> q(5);
    q.push(10);

    // Act & Assert
    ASSERT_NO_THROW(q.pop());
}

TEST(TestQueue, pop_decreases_size) {
    // Arrange
    Queue<int> q(5);
    q.push(10);
    q.push(20);

    // Act
    q.pop();

    // Assert
    EXPECT_EQ(q.size(), 1);
}

TEST(TestQueue, top_returns_correct_element) {
    // Arrange
    Queue<int> q(5);
    q.push(10);
    q.push(20);

    // Act
    int actual_result = q.top();

    // Assert
    int expected_result = 10;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestQueue, fifo_behavior) {
    // Arrange
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    // Act & Assert
    EXPECT_EQ(q.top(), 1);
    q.pop();
    EXPECT_EQ(q.top(), 2);
    q.pop();
    EXPECT_EQ(q.top(), 3);
}

TEST(TestQueue, can_clear_queue) {
    // Arrange
    Queue<int> q(5);
    q.push(10);
    q.push(20);

    // Act
    q.clear();

    // Assert
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(TestQueue, becomes_full_when_capacity_reached) {
    // Arrange
    Queue<int> q(2);
    q.push(10);
    q.push(20);

    // Act & Assert
    EXPECT_TRUE(q.is_full());
}

TEST(TestQueue, circular_buffer_works_correctly) {
    // Arrange
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    q.pop(); // remove 1
    q.pop(); // remove 2

    // Act
    q.push(4);
    q.push(5);

    // Assert
    EXPECT_EQ(q.top(), 3);
    q.pop();
    EXPECT_EQ(q.top(), 4);
    q.pop();
    EXPECT_EQ(q.top(), 5);
}