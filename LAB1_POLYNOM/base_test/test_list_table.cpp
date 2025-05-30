#include "gtest.h"
#include "../tables/list_table.h"

TEST(List_table, can_create_table)
{
	ASSERT_NO_THROW(decltype(List_table<string, int>()) tmp);
}

TEST(List_table, can_insert_elem)
{
	List_table<string, int> a;
	ASSERT_NO_THROW(a.insert("name", 4));
	EXPECT_TRUE(a.insert("name2", 10));
}

TEST(List_table, expected_false_when_insert_if_table_is_full)
{
	List_table<int, int> a;
	for (int i = 0; i < max_fill; i++)
		a.insert(i, 2*i);
	EXPECT_FALSE(a.insert(max_fill, max_fill*2));
}

TEST(List_table, expected_false_when_insert_existing_element)
{
	List_table<string, int> a;
	a.insert("name", 4);
	EXPECT_FALSE(a.insert("name", 5));
}

TEST(List_table, can_delete_elem)
{
	List_table<string, int> a;
	a.insert("a", 1);
	ASSERT_NO_THROW(a.delete_rec("a"));
	a.insert("b", 1);
	EXPECT_TRUE(a.delete_rec("b"));
}

TEST(List_table, expected_false_when_delete_if_table_is_empty)
{
	List_table<string, int> a;
	EXPECT_FALSE(a.delete_rec("anything"));
}

TEST(List_table, expected_false_when_delete_unexisting_element)
{
	List_table<string, int> a;
	a.insert("name1", 100);
	EXPECT_FALSE(a.delete_rec("anything"));
}

TEST(List_table, can_find_elem)
{
	List_table<string, int> a;
	string push;
	for (char i = 97; i < 123; i++)
	{
		push = i;
		a.insert(push, i);
	}
	EXPECT_EQ(97, a.find("a"));
	EXPECT_EQ(106, a.find("j"));
	EXPECT_EQ(113, a.find("q"));
}

TEST(List_table, throws_when_cant_find_elem)
{
	List_table<string, int> a;
	string push;
	for (char i = 97; i < 123; i++)//(a -> z)
	{
		push = i;
		a.insert(push, i);
	}
	ASSERT_ANY_THROW(a.find("A"));
}

TEST(List_table, can_insert_same_key_after_deletion)
{
	List_table<string, int> a;
	a.insert("a", 1);
	a.delete_rec("a");
	EXPECT_TRUE(a.insert("a", 1));
}

TEST(List_table, can_handle_large_number_of_deletions)
{
	List_table<int, int> a;
	for (int i = 0; i < max_fill; i++)
		a.insert(i, 2 * i);
	for (int i = 0; i < max_fill; i++)
		EXPECT_TRUE(a.delete_rec(i));
	EXPECT_TRUE(a.isEmpty());
}

TEST(List_table, can_handle_duplicate_insertions_with_different_values)
{
	List_table<string, int> a;
	a.insert("a", 1);
	EXPECT_FALSE(a.insert("a", 2));
	EXPECT_EQ(1, a.find("a"));
}

TEST(List_table, can_find_after_multiple_insertions_and_deletions)
{
	List_table<string, int> a;
	for (int i = 0; i < 100; i++)
		a.insert("name" + to_string(i), i);
	for (int i = 0; i < 50; i++)
		a.delete_rec("name" + to_string(i));
	for (int i = 50; i < 100; i++)
		EXPECT_EQ(i, a.find("name" + to_string(i)));
}

TEST(List_table, can_insert_multiple_elements_with_same_value)
{
	List_table<string, int> a;
	EXPECT_TRUE(a.insert("key1", 5));
	EXPECT_TRUE(a.insert("key2", 5));
	EXPECT_EQ(5, a.find("key1"));
	EXPECT_EQ(5, a.find("key2"));
}


TEST(List_table, can_insert_after_deleting_all_elements)
{
	List_table<string, int> a;
	for (int i = 0; i < 5; i++)
		a.insert("item" + to_string(i), i);
	for (int i = 0; i < 5; i++)
		a.delete_rec("item" + to_string(i));
	EXPECT_TRUE(a.insert("new_item", 10));
}