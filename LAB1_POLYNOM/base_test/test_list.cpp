#include "gtest.h"
#include "../polynom/list.h"

TEST(ListTest, can_create_empty_list) {
    ASSERT_NO_THROW(List<int> lst);
}

TEST(ListTest, size_of_new_list_is_zero) {
    List<int> lst;
    EXPECT_EQ(lst.size(), 0);
}

TEST(ListTest, is_empty_returns_true_for_new_list) {
    List<int> lst;
    EXPECT_TRUE(lst.isEmpty());
}

TEST(ListTest, can_push_front) {
    List<int> lst;
    ASSERT_NO_THROW(lst.PushFront(1));
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst.Front(), 1);
}

TEST(ListTest, can_pop_front) {
    List<int> lst;
    lst.PushFront(1);
    ASSERT_NO_THROW(lst.PopFront());
    EXPECT_EQ(lst.size(), 0);
    EXPECT_TRUE(lst.isEmpty());
}

TEST(ListTest, can_push_after) {
    List<int> lst;
    lst.PushFront(1);
    ASSERT_NO_THROW(lst.PushAfter(0, 2));
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst[1], 2);
}

TEST(ListTest, can_erase_after) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    ASSERT_NO_THROW(lst.EraseAfter(0));
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst[0], 1);
}

TEST(ListTest, can_access_elements_using_subscript_operator) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    EXPECT_EQ(lst[0], 1);
    EXPECT_EQ(lst[1], 2);
}

TEST(ListTest, out_of_range_throws_exception) {
    List<int> lst;
    lst.PushFront(1);
    ASSERT_THROW(lst[1], std::out_of_range);
}

TEST(ListTest, can_create_list_from_vector) {
    std::vector<int> vec = { 1, 2, 3 };
    ASSERT_NO_THROW(List<int> lst(vec));
    List<int> lst(vec);
    EXPECT_EQ(lst.size(), 3);
    EXPECT_EQ(lst[0], 1);
    EXPECT_EQ(lst[1], 2);
    EXPECT_EQ(lst[2], 3);
}

TEST(ListTest, can_copy_construct) {
    List<int> lst1;
    lst1.PushFront(1);
    lst1.PushAfter(0, 2);
    ASSERT_NO_THROW(List<int> lst2(lst1));
    List<int> lst2(lst1);
    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2[0], 1);
    EXPECT_EQ(lst2[1], 2);
}

TEST(ListTest, can_copy_assign) {
    List<int> lst1;
    lst1.PushFront(1);
    lst1.PushAfter(0, 2);
    List<int> lst2;
    ASSERT_NO_THROW(lst2 = lst1);
    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2[0], 1);
    EXPECT_EQ(lst2[1], 2);
}

TEST(ListTest, can_move_construct) {
    List<int> lst1;
    lst1.PushFront(1);
    lst1.PushAfter(0, 2);
    List<int> lst3(lst1);
    ASSERT_NO_THROW(List<int> lst2(std::move(lst1)));
    List<int> lst2(std::move(lst3));
    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2[0], 1);
    EXPECT_EQ(lst2[1], 2);
}

TEST(ListTest, can_move_assign) {
    List<int> lst1;
    lst1.PushFront(1);
    lst1.PushAfter(0, 2);
    List<int> lst2;
    ASSERT_NO_THROW(lst2 = std::move(lst1));
    EXPECT_EQ(lst2.size(), 2);
    EXPECT_EQ(lst2[0], 1);
    EXPECT_EQ(lst2[1], 2);
}

TEST(ListTest, can_access_front) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    EXPECT_EQ(lst.Front(), 1);
}

TEST(ListTest, can_handle_multiple_push_fronts) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushFront(2);
    lst.PushFront(3);
    EXPECT_EQ(lst.size(), 3);
    EXPECT_EQ(lst[0], 3);
    EXPECT_EQ(lst[1], 2);
    EXPECT_EQ(lst[2], 1);
}

TEST(ListTest, can_handle_multiple_push_afters) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    lst.PushAfter(1, 3);
    EXPECT_EQ(lst.size(), 3);
    EXPECT_EQ(lst[0], 1);
    EXPECT_EQ(lst[1], 2);
    EXPECT_EQ(lst[2], 3);
}

TEST(ListTest, can_handle_multiple_erase_afters) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    lst.PushAfter(1, 3);
    lst.EraseAfter(0);
    lst.EraseAfter(0);
    EXPECT_EQ(lst.size(), 1);
    EXPECT_EQ(lst[0], 1);
}

TEST(ListTest, can_pop_all_elements) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushFront(2);
    lst.PushFront(3);
    lst.PopFront();
    lst.PopFront();
    lst.PopFront();
    EXPECT_EQ(lst.size(), 0);
    EXPECT_TRUE(lst.isEmpty());
}

TEST(ListTest, can_push_and_erase_multiple_elements) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    lst.PushAfter(1, 3);
    lst.PushAfter(2, 4);
    lst.EraseAfter(1);
    lst.EraseAfter(0);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst[0], 1);
    EXPECT_EQ(lst[1], 4);
}

TEST(ListTest, can_handle_large_number_of_elements) {
    List<int> lst;
    for (int i = 0; i < 1000; i++) {
        lst.PushFront(i);
    }
    EXPECT_EQ(lst.size(), 1000);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(lst[i], 999 - i);
    }
}

TEST(ListTest, can_clear_list) {
    List<int> lst;
    for (int i = 0; i < 100; i++) {
        lst.PushFront(i);
    }
    while (!lst.isEmpty()) {
        lst.PopFront();
    }
    EXPECT_EQ(lst.size(), 0);
    EXPECT_TRUE(lst.isEmpty());
}

TEST(ListTest, can_handle_copying_large_list) {
    List<int> lst1;
    for (int i = 0; i < 1000; i++) {
        lst1.PushFront(i);
    }
    ASSERT_NO_THROW(List<int> lst2(lst1));
    List<int> lst2(lst1);
    EXPECT_EQ(lst2.size(), 1000);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(lst2[i], 999 - i);
    }
}

TEST(ListTest, can_handle_moving_large_list) {
    List<int> lst1;
    for (int i = 0; i < 1000; i++) {
        lst1.PushFront(i);
    }
    List<int> lst3(lst1);
    ASSERT_NO_THROW(List<int> lst2(std::move(lst1)));
    List<int> lst2(std::move(lst3));
    EXPECT_EQ(lst2.size(), 1000);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(lst2[i], 999 - i);
    }
}

TEST(ListTest, can_assign_large_list) {
    List<int> lst1;
    for (int i = 0; i < 1000; i++) {
        lst1.PushFront(i);
    }
    List<int> lst2;
    ASSERT_NO_THROW(lst2 = lst1);
    EXPECT_EQ(lst2.size(), 1000);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(lst2[i], 999 - i);
    }
}

TEST(ListTest, can_move_assign_large_list) {
    List<int> lst1;
    for (int i = 0; i < 1000; i++) {
        lst1.PushFront(i);
    }
    List<int> lst2;
    ASSERT_NO_THROW(lst2 = std::move(lst1));
    EXPECT_EQ(lst2.size(), 1000);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(lst2[i], 999 - i);
    }
}

TEST(ListTest, can_access_front_after_multiple_operations) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    lst.PopFront();
    lst.PushFront(3);
    EXPECT_EQ(lst.Front(), 3);
}

TEST(ListTest, handles_self_assignment_correctly) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    lst = lst;
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst[0], 1);
    EXPECT_EQ(lst[1], 2);
}

TEST(ListTest, handles_self_move_assignment_correctly) {
    List<int> lst;
    lst.PushFront(1);
    lst.PushAfter(0, 2);
    lst = std::move(lst);
    EXPECT_EQ(lst.size(), 2);
    EXPECT_EQ(lst[0], 1);
    EXPECT_EQ(lst[1], 2);
}

