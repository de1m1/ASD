#include "monom.h"
#include<gtest/gtest.h>
#include<sstream>

TEST(Monom, cancreate) {
    Monom m1;
    Monom m2(3, 2, 1, 0);
    Monom m3 = m2;
    EXPECT_EQ(m3, m2);
}

TEST(Monom, assignment) {
    Monom m1(4, 2, 3, 1);
    Monom m2;
    m2 = m1;

    EXPECT_EQ(m1, m2);
}

TEST(Monom, equal) {
    Monom m1(3, 1, 2, 0);
    Monom m2(5, 1, 2, 0);
    Monom m3(3, 2, 2, 0);

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m3);
}

TEST(Monom, add_sub_mult_div) {
    Monom m1(2, 1, 0, 0);
    Monom m2(3, 1, 0, 0);

    Monom result1 = m1 + m2;

    EXPECT_DOUBLE_EQ(result1.Calculate(1, 1, 1), 5);

    Monom m3(5, 2, 0, 0);
    Monom m4(3, 2, 0, 0);

    Monom result2 = m3 - m4;

    EXPECT_DOUBLE_EQ(result2.Calculate(1, 1, 1), 2);

    Monom m5(2, 1, 1, 0);
    Monom m6(3, 2, 0, 1);

    Monom result3 = m5 * m6;

    EXPECT_DOUBLE_EQ(result3.Calculate(1, 1, 1), 6);

    Monom m7(6, 3, 2, 1);
    Monom m8(2, 1, 1, 0);

    Monom result4 = m7 / m8;

    EXPECT_DOUBLE_EQ(result4.Calculate(1, 1, 1), 3);
}

TEST(Monom, divide_by_zero) {
    Monom m1(5, 1, 1, 1);
    Monom m2(0, 0, 0, 0);

    EXPECT_THROW(m1 / m2, std::logic_error);
}

TEST(Monom, mult_double) {
    Monom m(3, 2, 0, 0);
    Monom result = m * 2.0;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), 6);
}

TEST(Monom, unar_minus) {
    Monom m(5, 1, 0, 0);
    Monom result = -m;

    EXPECT_DOUBLE_EQ(result.Calculate(1, 1, 1), -5);
}

TEST(Monom, calculate_value) {
    Monom m(2, 2, 1, 0);

    double val = m.Calculate(2, 3, 1);

    EXPECT_DOUBLE_EQ(val, 2 * 4 * 3);
}

TEST(Monom, lexic) {
    Monom m1(1, 3, 0, 0);
    Monom m2(1, 2, 5, 0);

    EXPECT_TRUE(m1 < m2);
}

TEST(Monom, input_output) {
    std::stringstream ss;
    ss << "5 2 1 0";

    Monom m;
    ss >> m;

    EXPECT_DOUBLE_EQ(m.Calculate(1, 1, 1), 5);
}