#include "gtest/gtest.h"
#include "binarytree.h"

TEST(TestTree, create) {
    Tree<int, int> t;
}

TEST(TestTree, insert_root) {
    Tree<int, int> t;
    t.insert(10, 1);

    testing::internal::CaptureStdout();
    t.print_W();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 ");
}

TEST(TestTree, insert_three_nodes_level_order) {
    Tree<int, int> t;

    t.insert(1, 1);
    t.insert(2, 2);
    t.insert(3, 3);

    testing::internal::CaptureStdout();
    t.print_W();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 ");
}

TEST(TestTree, preorder_print_D1) {
    Tree<int, int> t;

    t.insert(1, 1);
    t.insert(2, 2);
    t.insert(3, 3);

    testing::internal::CaptureStdout();
    t.print_D1();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 ");
}

TEST(TestTree, erase_leaf) {
    Tree<int, int> t;

    t.insert(1, 1);
    t.insert(2, 2);
    t.insert(3, 3);

    t.erase(3);

    testing::internal::CaptureStdout();
    t.print_W();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 ");
}

TEST(TestTree, erase_root) {
    Tree<int, int> t;

    t.insert(1, 1);
    t.insert(2, 2);
    t.insert(3, 3);

    t.erase(1);

    testing::internal::CaptureStdout();
    t.print_W();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output, "1 2 3 ");
}