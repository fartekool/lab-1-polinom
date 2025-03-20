#include "gtest.h"
#include "../tables/array_table.h"
#include<string>
#include <type_traits>
TEST(Array_table, can_create_table)
{	
	static constexpr std::size_t n = TypeParam::value;
	ASSERT_NO_THROW(Array_table<TYPED_TEST, TYPED_TEST> tmp);

}

TEST(Array_table, can_insert_elem)
{
	Array_table<int, string> A;
	ASSERT_NO_THROW(A.insert("name", 4));
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