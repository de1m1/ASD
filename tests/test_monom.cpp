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
    Monom m2(5, 2, 2, 0);
    Monom m3(3, 1, 2, 0);

    EXPECT_TRUE(m1 == m3);
    EXPECT_TRUE(m1 != m2);
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

	EXPECT_TRUE(m2 < m1); // Сортировка идёт по убыванию степеней, поэтому m2 < m1, так как 3 > 2
}

TEST(Monom, input_output) {
    std::stringstream ss;
    ss << "5 2 1 0";

    Monom m;
    ss >> m;

    EXPECT_DOUBLE_EQ(m.Calculate(1, 1, 1), 5);
}

TEST(Monom, add_different_throws) {
    Monom m1(2, 1, 0, 0);
    Monom m2(3, 2, 0, 0);

    EXPECT_THROW(m1 + m2, std::logic_error);
}

TEST(Monom, sub_different_throws) {
    Monom m1(2, 1, 0, 0);
    Monom m2(3, 2, 0, 0);

    EXPECT_THROW(m1 - m2, std::logic_error);
}