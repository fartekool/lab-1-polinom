#include "gtest.h"
#include "../tables/hash_open_addr_table.h"

TEST(Hash_open_addr_table, can_create_table)
{
	ASSERT_NO_THROW(decltype(Hash_open_addr_table<string, int>()) tmp);
}

TEST(Hash_open_addr_table, can_insert_elem)
{
	Hash_open_addr_table<string, int> a;
	ASSERT_NO_THROW(a.insert("name", 4));
	EXPECT_TRUE(a.insert("name2", 10));
}

TEST(Hash_open_addr_table, expected_false_when_insert_if_table_is_full)
{
	Hash_open_addr_table<string, int> a;
	for (int i = 0; i < max_fill; ++i)
		a.insert("name" + to_string(i), 4);
	EXPECT_FALSE(a.insert("name" + to_string(max_fill), 4));
}

TEST(Hash_open_addr_table, expected_false_when_insert_existing_element)
{
	Hash_open_addr_table<string, int> a;
	a.insert("name", 4);
	EXPECT_FALSE(a.insert("name", 5));
}

TEST(Hash_open_addr_table, can_delete_elem)
{
	Hash_open_addr_table<string, int> a;
	a.insert("a", 1);
	ASSERT_NO_THROW(a.delete_rec("a"));
	a.insert("b", 1);
	EXPECT_TRUE(a.delete_rec("b"));

}

TEST(Hash_open_addr_table, expected_false_when_delete_if_table_is_empty)
{
	Hash_open_addr_table<string, int> a;
	EXPECT_FALSE(a.delete_rec("anything"));
}

TEST(Hash_open_addr_table, expected_false_when_delete_unexisting_element)
{
	Hash_open_addr_table<string, int> a;
	a.insert("name1", 100);
	EXPECT_FALSE(a.delete_rec("anything"));
}

TEST(Hash_open_addr_table, can_find_elem)
{
	Hash_open_addr_table<string, int> a;
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

TEST(Hash_open_addr_table, throws_when_cant_find_elem)
{
	Hash_open_addr_table<string, int> a;
	string push;
	for (char i = 97; i < 123; i++)//(a -> z)
	{
		push = i;
		a.insert(push, i);
	}
	ASSERT_ANY_THROW(a.find("A"));
}

TEST(Hash_open_addr_table, can_insert_same_key_after_deletion)
{
	Hash_open_addr_table<string, int> a;
	a.insert("a", 1);
	a.delete_rec("a");
	EXPECT_TRUE(a.insert("a", 1));
}

TEST(Hash_open_addr_table, can_handle_large_number_of_deletions)
{
	Hash_open_addr_table<string, int> a;
	for (int i = 0; i < max_fill; i++)
		a.insert("name" + to_string(i), 2 * i);
	for (int i = 0; i < max_fill; i++)
		EXPECT_TRUE(a.delete_rec("name" + to_string(i)));
	EXPECT_TRUE(a.isEmpty());
}

TEST(Hash_open_addr_table, can_handle_duplicate_insertions_with_different_values)
{
	Hash_open_addr_table<string, int> a;
	a.insert("a", 1);
	EXPECT_FALSE(a.insert("a", 2));
	EXPECT_EQ(1, a.find("a"));
}

TEST(Hash_open_addr_table, can_find_after_multiple_insertions_and_deletions)
{
	Hash_open_addr_table<string, int> a;
	for (int i = 0; i < 100; i++)
		a.insert("name" + to_string(i), i);
	for (int i = 0; i < 50; i++)
		a.delete_rec("name" + to_string(i));
	for (int i = 50; i < 100; i++)
		EXPECT_EQ(i, a.find("name" + to_string(i)));
}

TEST(Hash_open_addr_table, can_insert_multiple_elements_with_same_value)
{
	Hash_open_addr_table<string, int> a;
	EXPECT_TRUE(a.insert("key1", 5));
	EXPECT_TRUE(a.insert("key2", 5));
	EXPECT_EQ(5, a.find("key1"));
	EXPECT_EQ(5, a.find("key2"));
}

TEST(Hash_open_addr_table, can_insert_after_deleting_all_elements)
{
	Hash_open_addr_table<string, int> a;
	for (int i = 0; i < 5; i++)
		a.insert("item" + to_string(i), i);
	for (int i = 0; i < 5; i++)
		a.delete_rec("item" + to_string(i));
	EXPECT_TRUE(a.insert("new_item", 10));
}

TEST(Hash_open_addr_table, hash_function_for_equal_keys_will_output_equal_codes)
{
	Hash_open_addr_table<string, int> a;
	string key1 = "tmp";
	string key2 = "tmp";
	EXPECT_EQ(a.hash_function("tmp"), a.hash_function("tmp"));
	EXPECT_EQ(a.hash_function("tmp"), a.hash_function(key1));
	EXPECT_EQ(a.hash_function(key1), a.hash_function(key2));
}

TEST(Hash_open_addr_table, hash_function_handles_complex_keys_correctly)
{
	Hash_open_addr_table<vector<string>, int> a;
	vector<string> key1 = { "Help", "me", ",","please","!" };
	vector<string> key2 = { "Help", "me", ",","please","!" };
	EXPECT_EQ(a.hash_function(key1), a.hash_function(key2));
}

