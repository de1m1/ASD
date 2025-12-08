#include <gtest/gtest.h>
#include "tvector.h"

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