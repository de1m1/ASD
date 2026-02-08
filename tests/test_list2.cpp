#include "list2.h"
#include <gtest/gtest.h>

TEST(DoublyLinkedListIterator, EmptyListIteration) {
    ListDouble<int> empty_list;

    auto it_begin = empty_list.begin();
    auto it_end = empty_list.end();

    EXPECT_EQ(it_begin, it_end);

    int count = 0;
    for (auto it = empty_list.begin(); it != empty_list.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 0);
}

TEST(DoublyLinkedListIterator, WriteOperation) {
    ListDouble<int> my_list;
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);

    auto it = my_list.begin();
    *it = 10;
    ++it;
    *it = 20;
    ++it;
    *it = 30;

    it = my_list.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

TEST(DoublyLinkedListIterator, ReadOperation) {
    ListDouble<int> my_list;
    my_list.push_back(5);
    my_list.push_back(10);
    my_list.push_back(15);


    auto it = my_list.begin();
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 15);
    ++it;
    EXPECT_EQ(it, my_list.end());
}

TEST(DoublyLinkedListIterator, Iterator) {
    ListDouble<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);

    int i = 1;

    for (auto it = list.rbegin(); it != list.rend(); it--) {
        EXPECT_EQ(*it, i);
        i++;
    }
}

TEST(DoublyLinkedList, PushBack) {
    ListDouble<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DoublyLinkedList, PushFront) {
    ListDouble<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DoublyLinkedList, PopBack) {
    ListDouble<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);

    list.pop_back();
    EXPECT_EQ(list.back(), 1);

    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedList, PopFront) {
    ListDouble<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);

    list.pop_front();
    EXPECT_EQ(list.front(), 3);

    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedList, CopyConstructor) {
    ListDouble<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    ListDouble<int> copy(original);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);

    original.pop_front();
    EXPECT_EQ(copy.front(), 1);
}

TEST(DoublyLinkedList, AssignmentOperator) {
    ListDouble<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    ListDouble<int> list2;
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);

    list2 = list1;

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
}

TEST(DoublyLinkedList, Clear) {
    ListDouble<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();

    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}