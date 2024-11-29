#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lists.h>
// Тест конструктора List():
//cpp
TEST(ListTest, ConstructorTest) {
    List<int> l;
    EXPECT_EQ(l.getSize(), 0);
}
//Тест конструктора List(std::initializer_list<int> lst):
//cpp
TEST(ListTest, InitializerListConstructorTest) {
    List<int> l = {1, 2, 3};
    EXPECT_EQ(l.getSize(), 3);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 2);
    EXPECT_EQ(l[2], 3);
}
// Тест метода append(int elem):
//cpp
TEST(ListTest, AppendTest) {
    List<int> l;
    l.append(42);
    EXPECT_EQ(l.getSize(), 1);
    EXPECT_EQ(l[0], 42);
}
// Тест метода remove(size_t index):
//cpp
TEST(ListTest, RemoveTest) {
    List<int> l = {1, 2, 3};
    l.remove(1);
    EXPECT_EQ(l.getSize(), 2);
    EXPECT_EQ(l[0], 1);
    EXPECT_EQ(l[1], 3);
}
// Тест оператора присваивания и конструктора копирования:
//cpp
TEST(ListTest, CopyConstructorAndAssignmentOperatorTest) {
    List<int> l1 = {1, 2, 3};
    List<int> l2(l1);
    EXPECT_EQ(l2.getSize(), l1.getSize());
    EXPECT_EQ(l2[0], l1[0]);
    EXPECT_EQ(l2[1], l1[1]);
    EXPECT_EQ(l2[2], l1[2]);
    List<int> l3 = {4, 5, 6};
    l3 = l1;
    EXPECT_EQ(l3.getSize(), l1.getSize());
    EXPECT_EQ(l3[0], l1[0]);
    EXPECT_EQ(l3[1], l1[1]);
    EXPECT_EQ(l3[2], l1[2]);
}
