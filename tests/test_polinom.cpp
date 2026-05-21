#include "polinom.h"
#include <gtest/gtest.h>

TEST(Polynom, create) {

    Polynom p1;
    Monom m(3, 2, 0, 0);
    Polynom p2(m);
    Polynom p3 = p2;

    EXPECT_TRUE(p2 == p3);
}

TEST(Polynom, add) {

    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    Polynom result = p1 + p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 5);
}

TEST(Polynom, sub) {

    Polynom p1;
    p1.addMonom(Monom(5, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    Polynom result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 2);
}

TEST(Polynom, mul) {

    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 2, 0, 0));

    Polynom result = p1 * p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 6);
}

TEST(Polynom, add_eq) {

    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    p1 += p2;

    EXPECT_DOUBLE_EQ(p1.Calculate(1, 1, 1), 5);
}

TEST(Polynom, sub_eq) {

    Polynom p1;
    p1.addMonom(Monom(5, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(2, 1, 0, 0));

    p1 -= p2;

    EXPECT_DOUBLE_EQ(p1.Calculate(1, 1, 1), 3);
}

TEST(Polynom, mul_eq) {

    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(4, 1, 0, 0));

    p1 *= p2;

    EXPECT_DOUBLE_EQ(p1.Calculate(1, 1, 1), 8);
}

TEST(Polynom, removes_zero_after_sub) {

    Polynom p1;
    p1.addMonom(Monom(3, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    Polynom result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 0);
}

TEST(Polynom, calculate) {
    Polynom p;

    p.addMonom(Monom(2, 2, 0, 0));
    p.addMonom(Monom(3, 0, 1, 0));

    double val = p.Calculate(2, 3, 1);

    EXPECT_DOUBLE_EQ(val, 2 * 4 + 3 * 3);
}

TEST(Polynom, eq) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));
    p1.addMonom(Monom(3, 0, 1, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 0, 1, 0));
    p2.addMonom(Monom(2, 1, 0, 0));

    EXPECT_TRUE(p1 == p2);
}