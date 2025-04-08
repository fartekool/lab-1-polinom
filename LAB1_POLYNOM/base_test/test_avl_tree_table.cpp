#include "gtest.h"
#include "../tables/avl_tree_table.h"

TEST(Avl_tree_table, can_create_table)
{
	ASSERT_NO_THROW(decltype(Avl_tree_table<string, int>()) tmp);
}

TEST(Avl_tree_table, can_insert_elem)
{
	Avl_tree_table<string, int> a;
	ASSERT_NO_THROW(a.insert("name", 4));
	EXPECT_TRUE(a.insert("name2", 10));
}

TEST(Avl_tree_table, throws_when_insert_if_table_is_full)
{
	Avl_tree_table<int, int> a;
	for (int i = 0; i < max_fill; ++i)
		a.insert(i, 4);
	EXPECT_FALSE(a.insert(1000, 4));
}

TEST(Avl_tree_table, expected_false_when_insert_existing_element)
{
	Avl_tree_table<string, int> a;
	a.insert("name", 4);
	EXPECT_FALSE(a.insert("name", 5));
}

TEST(Avl_tree_table, can_delete_elem)
{
	Avl_tree_table<string, int> a;
	a.insert("a", 1);
	ASSERT_NO_THROW(a.delete_rec("a"));
	a.insert("b", 1);
	EXPECT_TRUE(a.delete_rec("b"));
}

TEST(Avl_tree_table, expected_false_when_delete_if_table_is_empty)
{
	Avl_tree_table<string, int> a;
	EXPECT_FALSE(a.delete_rec("anything"));
}

TEST(Avl_tree_table, can_find_elem)
{
	Avl_tree_table<string, int> a;
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

TEST(Avl_tree_table, throws_when_cant_find_elem)
{
	Avl_tree_table<string, int> a;
	string push;
	for (char i = 97; i < 123; i++)//(a -> z)
	{
		push = i;
		a.insert(push, i);
	}
	ASSERT_ANY_THROW(a.find("A"));
}

TEST(Avl_tree_table, can_insert_same_key_after_deletion)
{
	Avl_tree_table<string, int> a;
	a.insert("a", 1);
	a.delete_rec("a");
	EXPECT_TRUE(a.insert("a", 1));
}

TEST(Avl_tree_table, expected_false_when_insert_to_full_fill_table)
{
	Avl_tree_table<int, int> a;
	for (int i = 0; i < max_fill; i++)
		a.insert(i, 2 * i);
	EXPECT_FALSE(a.insert(max_fill, 2 * max_fill));
}

TEST(Avl_tree_table, can_handle_large_number_of_deletions)
{
	Avl_tree_table<int, int> a;
	for (int i = 0; i < max_fill; i++)
		a.insert(i, 2 * i);
	for (int i = 0; i < max_fill; i++)
		EXPECT_TRUE(a.delete_rec(i));
	EXPECT_TRUE(a.isEmpty());
}

TEST(Avl_tree_table, can_handle_duplicate_insertions_with_different_values)
{
	Avl_tree_table<string, int> a;
	a.insert("a", 1);
	EXPECT_FALSE(a.insert("a", 2));
	EXPECT_EQ(1, a.find("a"));
}

TEST(Avl_tree_table, can_find_after_multiple_insertions_and_deletions)
{
	Avl_tree_table<string, int> a;
	for (int i = 0; i < 100; i++)
		a.insert("name" + to_string(i), i);
	for (int i = 0; i < 50; i++)
		a.delete_rec("name" + to_string(i));
	for (int i = 50; i < 100; i++)
		EXPECT_EQ(i, a.find("name" + to_string(i)));
}

TEST(Avl_tree_table, can_insert_multiple_elements_with_same_value)
{
	Avl_tree_table<string, int> a;
	EXPECT_TRUE(a.insert("key1", 5));
	EXPECT_TRUE(a.insert("key2", 5));
	EXPECT_EQ(5, a.find("key1"));
	EXPECT_EQ(5, a.find("key2"));
}

TEST(Avl_tree_table, can_insert_after_deleting_all_elements)
{
	Avl_tree_table<string, int> a;
	for (int i = 0; i < 5; i++)
		a.insert("item" + to_string(i), i);
	for (int i = 0; i < 5; i++)
		a.delete_rec("item" + to_string(i));
	EXPECT_TRUE(a.insert("new_item", 10));
}

TEST(Avl_tree_table, can_get_all_records_from_empty_tree)
{
	Avl_tree_table<string, int> a;
	EXPECT_TRUE(a.GetAllRecords().empty());
}

TEST(Avl_tree_table, can_get_all_records_from_non_empty_tree)
{
	Avl_tree_table<string, int> a;
	a.insert("banana", 2);
	a.insert("apple", 1);
	a.insert("cherry", 3);

	ASSERT_EQ(a.GetAllRecords().size(), 3);

	// Проверяем, что записи отсортированы по ключу
	ASSERT_EQ(a.GetAllRecords()[0].key, "apple");
	ASSERT_EQ(a.GetAllRecords()[0].data, 1);
	ASSERT_EQ(a.GetAllRecords()[1].key, "banana");
	ASSERT_EQ(a.GetAllRecords()[1].data, 2);
	ASSERT_EQ(a.GetAllRecords()[2].key, "cherry");
	ASSERT_EQ(a.GetAllRecords()[2].data, 3);
}

TEST(Avl_tree_table, can_get_all_records_after_insertions_and_deletions)
{
	Avl_tree_table<int, string> a;
	a.insert(5, "five");
	a.insert(3, "three");
	a.insert(8, "eight");
	a.delete_rec(3);
	a.insert(1, "one");
	a.insert(4, "four");

	ASSERT_EQ(a.GetAllRecords().size(), 4);

	// Проверяем порядок после вставок и удаления
	ASSERT_EQ(a.GetAllRecords()[0].key, 1);
	ASSERT_EQ(a.GetAllRecords()[0].data, "one");
	ASSERT_EQ(a.GetAllRecords()[1].key, 4);
	ASSERT_EQ(a.GetAllRecords()[1].data, "four");
	ASSERT_EQ(a.GetAllRecords()[2].key, 5);
	ASSERT_EQ(a.GetAllRecords()[2].data, "five");
	ASSERT_EQ(a.GetAllRecords()[3].key, 8);
	ASSERT_EQ(a.GetAllRecords()[3].data, "eight");
}

TEST(Avl_tree_table, can_get_all_records_with_duplicate_values)
{
	Avl_tree_table<string, int> a;
	a.insert("a", 5);
	a.insert("b", 5);
	a.insert("c", 5);

	ASSERT_EQ(a.GetAllRecords().size(), 3);
	ASSERT_EQ(a.GetAllRecords()[0].key, "a");
	ASSERT_EQ(a.GetAllRecords()[0].data, 5);
	ASSERT_EQ(a.GetAllRecords()[1].key, "b");
	ASSERT_EQ(a.GetAllRecords()[1].data, 5);
	ASSERT_EQ(a.GetAllRecords()[2].key, "c");
	ASSERT_EQ(a.GetAllRecords()[2].data, 5);
}
