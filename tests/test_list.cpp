#include <gtest/gtest.h>
#include "list.h"

TEST(ListTest, DefaultConstructor) {
    List<int> lst;
    EXPECT_TRUE(lst.is_empty());
    EXPECT_EQ(lst.size(), 0);

}

TEST(ListTest, PushFrontAndFront) {
    List<int> lst;

    lst.push_front(10);
    EXPECT_FALSE(lst.is_empty());
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.front(), 10);

    lst.push_front(20);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.front(), 20);
}

TEST(ListTest, PushBackAndBack) {
    List<int> lst;

    lst.push_back(5);
    EXPECT_FALSE(lst.is_empty());
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.back(), 5);

    lst.push_back(15);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst.back(), 15);
}

TEST(ListTest, PopFront) {
    List<int> lst;
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
    List<int> lst;
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
    List<int> lst;

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
    List<int> lst;
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
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.front(), copy.front());
    EXPECT_EQ(original.back(), copy.back());
}

TEST(ListTest, AssignmentOperator) {
    List<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    List<int> copy;
    copy = original;

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.front(), copy.front());
    EXPECT_EQ(original.back(), copy.back());
}

TEST(ListTest, MixedOperations) {
    List<int> lst;

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

TEST(ListTest, can_write) {
    List<int> mlist;
    for (int i = 0; i < 10; i++) {
        mlist.push_back(i + 1);
    }

    int expected_val = 1;
    for (List<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        *it = expected_val;
        expected_val++;
    }

    expected_val = 1;
    for (List<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }

}

TEST(ListTest, can_read) {
    List<int> mlist;
    for (int i = 0; i < 10; i++) {
        mlist.push_back(i + 1);
    }
    int expected_val = 1;
    for (List<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }

}

TEST(ListTest, is_empty) {
    List<int> mlist;

    for (List<int>::Iterator it = mlist.begin(); it != mlist.end(); it++) {
        *it = 0;
    }
}

TEST(DoublyLinkedListIterator, EmptyListIteration) {
    List<int> empty_list;

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
    List<int> my_list;
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
    List<int> my_list;
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

TEST(TVectorIterator, EmptyVectorIteration) {
    TVector<int> empty_vector;

    auto it_begin = empty_vector.begin();
    auto it_end = empty_vector.end();

    EXPECT_EQ(it_begin, it_end);

    int count = 0;
    for (auto it = empty_vector.begin(); it != empty_vector.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 0);
}

TEST(TVectorIterator, WriteOperation) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    auto it = vec.begin();
    *it = 100;
    ++it;
    *it = 200;
    ++it;
    *it = 300;

    EXPECT_EQ(vec[0], 100);
    EXPECT_EQ(vec[1], 200);
    EXPECT_EQ(vec[2], 300);
}

TEST(TVectorIterator, ReadOperation) {
    TVector<int> vec;
    vec.push_back(50);
    vec.push_back(60);
    vec.push_back(70);

    auto it = vec.begin();
    EXPECT_EQ(*it, 50);
    ++it;
    EXPECT_EQ(*it, 60);
    ++it;
    EXPECT_EQ(*it, 70);
    ++it;
    EXPECT_EQ(it, vec.end());
}