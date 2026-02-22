#include "polinom.h"
#include <gtest/gtest.h>

TEST(Polynom, can_create) {
    Polynom p1;
    Monom m(3, 2, 0, 0);
    Polynom p2(m);
    Polynom p3 = p2;

    EXPECT_TRUE(p2 == p3);
}

TEST(Polynom, assignment) {
    Monom m(4, 1, 0, 0);
    Polynom p1(m);
    Polynom p2;

    p2 = p1;

    EXPECT_TRUE(p1 == p2);
}

TEST(Polynom, add_polynoms) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    Polynom result = p1 + p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 5);
}

TEST(Polynom, subtract_polynoms) {
    Polynom p1;
    p1.addMonom(Monom(5, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    Polynom result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 2);
}

TEST(Polynom, multiply_polynoms) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 2, 0, 0));

    Polynom result = p1 * p2;

    // 2x * 3x^2 = 6x^3
    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 6);
}

TEST(Polynom, plus_equals) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    p1 += p2;

    EXPECT_DOUBLE_EQ(p1.Calculate(1, 1, 1), 5);
}

TEST(Polynom, minus_equals) {
    Polynom p1;
    p1.addMonom(Monom(5, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(2, 1, 0, 0));

    p1 -= p2;

    EXPECT_DOUBLE_EQ(p1.Calculate(1, 1, 1), 3);
}

TEST(Polynom, mult_equals) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(4, 1, 0, 0));

    p1 *= p2;

    EXPECT_DOUBLE_EQ(p1.Calculate(1, 1, 1), 8);
}

TEST(Polynom, combines_same_degrees) {
    Polynom p;
    p.addMonom(Monom(2, 1, 0, 0));
    p.addMonom(Monom(3, 1, 0, 0));

    EXPECT_DOUBLE_EQ(p.Calculate(1, 1, 1), 5);
}

TEST(Polynom, removes_zero_after_subtraction) {
    Polynom p1;
    p1.addMonom(Monom(3, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    Polynom result = p1 - p2;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 0);
}

TEST(Polynom, calculate_multiple_terms) {
    Polynom p;

    // 2x^2 + 3y
    p.addMonom(Monom(2, 2, 0, 0));
    p.addMonom(Monom(3, 0, 1, 0));

    double val = p.Calculate(2, 3, 1);

    EXPECT_DOUBLE_EQ(val, 2 * 4 + 3 * 3);
}

TEST(Polynom, equality) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));
    p1.addMonom(Monom(3, 0, 1, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 0, 1, 0));
    p2.addMonom(Monom(2, 1, 0, 0));

    EXPECT_TRUE(p1 == p2);
}

TEST(Polynom, inequality) {
    Polynom p1;
    p1.addMonom(Monom(2, 1, 0, 0));

    Polynom p2;
    p2.addMonom(Monom(3, 1, 0, 0));

    EXPECT_TRUE(p1 != p2);
}