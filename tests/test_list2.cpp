#include "list2.h"
#include <gtest/gtest.h>

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