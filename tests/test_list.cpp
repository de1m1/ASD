#include <gtest/gtest.h>
#include <stdexcept>
#include "List.h"

TEST(ListTest, PushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, PushFront) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, PopBack) {
    List<int> list;
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

TEST(ListTest, PopFront) {
    List<int> list;
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

TEST(ListTest, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);

    original.pop_front();
    EXPECT_EQ(copy.front(), 1);
}

TEST(ListTest, AssignmentOperator) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);

    list2 = list1;

    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, Clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();

    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, Iterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int i = 1;

    for (auto it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, i);
        i++;
    }
}

TEST(ListTest, IteratorPostIncrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    auto old_it = it++;

    EXPECT_EQ(*old_it, 1);
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, IteratorEquality) {
    List<int> list;
    list.push_back(1);

    auto it1 = list.begin();
    auto it2 = list.begin();

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, InsertAtBeginning) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);

    list.insert(list.begin(), 1);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
}

TEST(ListTest, InsertAtEnd) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.insert(list.end(), 3);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, InsertInMiddle) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    list.insert(it, 2);

    EXPECT_EQ(list.size(), 3);

    it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(ListTest, EraseAtBeginning) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(list.begin());

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
}

TEST(ListTest, EraseAtEnd) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    ++it;
    list.erase(it);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, EraseInMiddle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    list.erase(it);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

//TEST(ListTest, FindonList) {
//    List<int> list;
//    list.push_back(1);
//    list.push_back(2);
//    list.push_back(3);
//    
//    const int a = 2;
//
//    auto it = list.find(a);
//
//    EXPECT_EQ(it, 2);
//
//}


