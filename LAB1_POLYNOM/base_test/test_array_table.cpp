#include "gtest.h"
#include "../tables/array_table.h"

TEST(Array_table, can_create_table)
{
	ASSERT_NO_THROW(decltype(Array_table<std::string, int>()) tmp);
}

TEST(Array_table, can_insert_elem)
{
	Array_table<string, int> a;
	ASSERT_NO_THROW(a.insert("name", 4));
	EXPECT_TRUE(a.insert("name2", 10));
}

TEST(Array_table, expected_false_when_insert_if_table_is_full)
{
	Array_table<int, int> a;
	for (int i = 0; i < max_fill; ++i)
		a.insert(i, 4);
	EXPECT_FALSE(a.insert(1000, 4));
}

TEST(Array_table, expected_false_when_insert_existing_element)
{
	Array_table<string, int> a;
	a.insert("name", 4);
	EXPECT_FALSE(a.insert("name", 5));
}

TEST(Array_table, can_delete_elem)
{	
	Array_table<string, int> a;
	a.insert("a", 1);
	ASSERT_NO_THROW(a.delete_rec("a"));
	a.insert("b", 1);
	EXPECT_TRUE(a.delete_rec("b"));

}

TEST(Array_table, throws_when_delete_if_table_is_empty)
{
	ADD_FAILURE();
}

TEST(Array_table, can_find_elem)
{
	ADD_FAILURE();
}

TEST(Array_table, throws_when_cant_find_elem)
{
	ADD_FAILURE();
}