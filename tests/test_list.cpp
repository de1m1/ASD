#include <gtest/gtest.h>
#include <stdexcept>
#include "List.h"

TEST(ListTest, DefaultConstructor) {
    List<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

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

TEST(ListTest, PopBackEmpty) {
    List<int> list;
    EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(ListTest, PopFrontEmpty) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST(ListTest, FrontBackEmpty) {
    List<int> list;
    EXPECT_THROW(list.front(), std::runtime_error);
    EXPECT_THROW(list.back(), std::runtime_error);
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

TEST(ListTest, SelfAssignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list = list;

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
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

TEST(ListTest, ClearEmpty) {
    List<int> list;
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, Iterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);

    ++it;
    EXPECT_EQ(it, list.end());
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

TEST(ListTest, RangeBasedFor) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int sum = 0;
    for (const auto& item : list) {
        sum += item;
    }

    EXPECT_EQ(sum, 6);
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

TEST(ListTest, EraseInvalidIterator) {
    List<int> list;
    auto it = list.end();

    EXPECT_THROW(list.erase(it), std::runtime_error);
}

TEST(ListTest, EraseEmptyList) {
    List<int> list;
    auto it = list.begin();

    EXPECT_THROW(list.erase(it), std::runtime_error);
}

TEST(ListTest, StringList) {
    List<std::string> list;
    list.push_back("hello");
    list.push_back("world");

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), "hello");
    EXPECT_EQ(list.back(), "world");
}

TEST(ListTest, DoubleList) {
    List<double> list;
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);

    EXPECT_DOUBLE_EQ(list.front(), 1.1);
    EXPECT_DOUBLE_EQ(list.back(), 3.3);
}

TEST(ListTest, LargeList) {
    List<int> list;
    const int COUNT = 1000;

    for (int i = 0; i < COUNT; ++i) {
        list.push_back(i);
    }

    EXPECT_EQ(list.size(), COUNT);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), COUNT - 1);
}

TEST(ListTest, IteratorArrowOperator) {
    struct TestStruct {
        int x;
        int y;
    };

    List<TestStruct> list;
    list.push_back(TestStruct{ 1, 2 });

    auto it = list.begin();
    EXPECT_EQ(it->x, 1);
    EXPECT_EQ(it->y, 2);
}