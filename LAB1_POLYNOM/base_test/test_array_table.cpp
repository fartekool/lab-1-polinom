#include "gtest.h"
#include "../tables/array_table.h"

TEST(Array_table, can_create_table)
{
	ASSERT_ANY_THROW(Array_table<int> tmp);
}

TEST(Array_table, can_insert_elem)
{
	ADD_FAILURE();
}

TEST(Array_table, throws_when_insert_if_table_is_full)
{
	ADD_FAILURE();
}

TEST(Array_table, can_delete_elem)
{
	ADD_FAILURE();
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