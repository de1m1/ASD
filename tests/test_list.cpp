#include <gtest/gtest.h>
#include "list.h"

TEST(ListTest, DefaultConstructor) {
    list<int> lst;
    EXPECT_TRUE(lst.is_empty());
    EXPECT_EQ(lst.size(), 0);
    EXPECT_EQ(lst.begin(), nullptr);
}

TEST(ListTest, PushFrontAndFront) {
    list<int> lst;

    lst.push_front(10);
    EXPECT_FALSE(lst.is_empty());
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.front(), 10);

    lst.push_front(20);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.front(), 20);
}

TEST(ListTest, PushBackAndBack) {
    list<int> lst;

    lst.push_back(5);
    EXPECT_FALSE(lst.is_empty());
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.back(), 5);

    lst.push_back(15);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.back(), 15);
}

TEST(ListTest, PopFront) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    lst.pop_front();
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.front(), 2);

    lst.pop_front();
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.front(), 3);

    lst.pop_front();
    EXPECT_TRUE(lst.is_empty());
}

TEST(ListTest, PopBack) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    lst.pop_back();
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.back(), 2);

    lst.pop_back();
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.back(), 1);

    lst.pop_back();
    EXPECT_TRUE(lst.is_empty());
}

TEST(ListTest, InsertByPosition) {
    list<int> lst;

    // Вставка в пустой список
    lst.insert(0, 100);
    EXPECT_EQ(lst.front(), 100);

    // Вставка в начало
    lst.insert(0, 200);
    EXPECT_EQ(lst.front(), 200);

    // Вставка в конец
    lst.insert(2, 300);
    EXPECT_EQ(lst.back(), 300);

    // Вставка в середину
    lst.insert(1, 400);
    EXPECT_EQ(lst.size(), 4);
}

TEST(ListTest, EraseByPosition) {
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);

    // Удаление из середины
    lst.erase(1);
    EXPECT_EQ(lst.size(), 3);

    // Удаление из начала
    lst.erase(0);
    EXPECT_EQ(lst.front(), 3);

    // Удаление из конца
    lst.erase(1);
    EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, CopyConstructor) {
    list<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    list<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.front(), copy.front());
    EXPECT_EQ(original.back(), copy.back());
}

TEST(ListTest, AssignmentOperator) {
    list<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    list<int> copy;
    copy = original;

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.front(), copy.front());
    EXPECT_EQ(original.back(), copy.back());
}

TEST(ListTest, MixedOperations) {
    list<int> lst;

    // Смешанные операции
    lst.push_front(1);
    lst.push_back(2);
    lst.push_front(0);
    lst.push_back(3);

    EXPECT_EQ(lst.size(), 4);
    EXPECT_EQ(lst.front(), 0);
    EXPECT_EQ(lst.back(), 3);

    lst.pop_front();
    lst.pop_back();

    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.front(), 1);
    EXPECT_EQ(lst.back(), 2);
}


TEST(ListTest, can_read) {
    list<int>mlist;
    for (int i = 0; i < 10; i++) { 
        mlist.push_back(i+1); 
    }

    int expected_val = 1;
    for (list<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }

}

TEST(ListTest, can_write) {

    list<int>mlist;
    int expected_val = 1;
    for (list<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }

}

TEST(ListTest, is_empty) {
    list<int>mlist;

    for (list<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        *it = 0;
    }

}