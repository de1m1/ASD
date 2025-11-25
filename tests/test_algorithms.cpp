#include <gtest/gtest.h>
#include "algorithms.h"

TEST(BracketsTest, CorrectSequence) {
    EXPECT_TRUE(check_breckets("({[]})"));
}

TEST(BracketsTest, IncorrectSequence) {
    EXPECT_FALSE(check_breckets("({[}])"));
}

TEST(BracketsTest, EmptyString) {
    EXPECT_TRUE(check_breckets(""));
}
