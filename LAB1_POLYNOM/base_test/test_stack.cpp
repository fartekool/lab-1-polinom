#include "gtest.h"
#include "../polynomial_algebra/stack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_stack_with_zero_length) {
	ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, cant_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_create_stack_with_dynamic_size) {
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_push_elements_to_stack_with_fixed_size) {
	TStack<int> st(3);
	ASSERT_NO_THROW(st.Push(1));
	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Push(3));
}

TEST(TStack, cant_push_to_full_stack_with_fixed_size) {
	TStack<int> st(3);
	st.Push(1); st.Push(2); st.Push(3);
	ASSERT_ANY_THROW(st.Push(4));
}

TEST(TStack, can_push_to_dynamic_stack) {
	TStack<int> st;
	for (int i = 0; i < MaxStackSize; i++) {
		ASSERT_NO_THROW(st.Push(i));
	}
}

TEST(TStack, cant_push_to_full_dynamic_stack) {
	TStack<int> st;
	for (int i = 0; i < MaxStackSize; i++) {
		st.Push(i);
	}
	ASSERT_ANY_THROW(st.Push(100));
}

TEST(TStack, can_pop_elements_from_stack) {
	TStack<int> st(3);
	st.Push(1); st.Push(2); st.Push(3);
	ASSERT_NO_THROW(st.Pop());
	ASSERT_NO_THROW(st.Pop());
	ASSERT_NO_THROW(st.Pop());
	EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, cant_pop_from_empty_stack) {
	TStack<int> st(3);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_peek_top_element) {
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	ASSERT_EQ(st.Top(), 3);
}

TEST(TStack, cant_peek_from_empty_stack) {
	TStack<int> st(3);
	ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, is_empty_after_creation) {
	TStack<int> st(3);
	EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, is_full_after_filling) {
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_TRUE(st.IsFull());
}

TEST(TStack, size_is_correct_after_operations) {
	TStack<int> st(5);
	EXPECT_EQ(st.Size(), 0);
	st.Push(1);
	EXPECT_EQ(st.Size(), 1);
	st.Push(2);
	EXPECT_EQ(st.Size(), 2);
	st.Pop();
	EXPECT_EQ(st.Size(), 1);
	st.Pop();
	EXPECT_EQ(st.Size(), 0);
}

TEST(TStack, clear_empties_the_stack) {
	TStack<int> st(5);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	st.Clear();
	EXPECT_TRUE(st.IsEmpty());
	EXPECT_EQ(st.Size(), 0);
}

TEST(TStack, stack_is_not_copy_constructible) {
	static_assert(!std::is_copy_constructible<TStack<int>>::value,
		"TStack should not be copy constructible");
}

TEST(TStack, stack_is_not_copy_assignable) {
	static_assert(!std::is_copy_assignable<TStack<int>>::value,
		"TStack should not be copy assignable");
}

TEST(TStack, dynamic_stack_expands_up_to_max_size) {
	TStack<int> st;
	for (int i = 0; i < MaxStackSize; ++i) {
		st.Push(i);
	}
	EXPECT_EQ(st.Size(), MaxStackSize);
}


TEST(TStack, fixed_size_stack_does_not_expand) {
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	ASSERT_ANY_THROW(st.Push(4));
	EXPECT_EQ(st.Size(), 3);
}