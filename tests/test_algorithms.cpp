#include <gtest/gtest.h>
#include "algorithms.h"
#include "list.h"

TEST(BracketsTest, CorrectSequence) {
    EXPECT_TRUE(check_breckets("({[]})"));
}

TEST(BracketsTest, IncorrectSequence) {
    EXPECT_FALSE(check_breckets("({[}])"));
}

TEST(BracketsTest, EmptyString) {
    EXPECT_TRUE(check_breckets(""));
}

//// Тест 1: Пустой список
//TEST(FloydTest, EmptyList) {
//    List<int> list;
//    bool result = Algorithms::hasCycleFloyd<int>(list.begin(), list.end());
//    EXPECT_FALSE(result);
//}
//
//// Тест 2: Список 1-2-3 без цикла
//TEST(FloydTest, NoCycle) {
//    List<int> list;
//    list.push_back(1);
//    list.push_back(2);
//    list.push_back(3);
//
//    bool result = Algorithms::hasCycleFloyd<int>(list.begin(), list.end());
//    EXPECT_FALSE(result);
//}
//
//// Тест 3: Список 1-2-3-1 с циклом
////TEST(FloydTest, HasCycle) {
////    List<int> list;
////    list.push_back(1);
////    list.push_back(2);
////    list.push_back(3);
////
////    // Создаем цикл
////    auto it = list.begin();
////    auto* n1 = it.current;
////    auto* n3 = n1->next->next;
////    n3->next = n1;
////
////    bool result = Algorithms::hasCycleFloyd<int>(list.begin(), list.end());
////    EXPECT_TRUE(result);
////
////    // Чистим
////    n3->next = nullptr;
////}