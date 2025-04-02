#include "gtest.h"
#include "../tables/tables_manager.h"

TEST(Tables_manager, can_create_manager)
{
	ASSERT_NO_THROW(decltype(Tables_manager<string, int> ())a);
}

TEST(Tables_manager, can_insert_element_in_tables)
{
	Tables_manager<string, int> a;
	EXPECT_TRUE(a.insert("name1", 1));
}

TEST(Tables_manager, false_when_insert_existing_element_in_tables)
{
	Tables_manager<string, int> a;
	a.insert("name1", 1);
	EXPECT_FALSE(a.insert("name1", 1));
}

TEST(Tables_manager, can_find_element_in_tables)
{
	Tables_manager<string, int> a;
	a.insert("name1", 1);
	EXPECT_EQ(a.find("name1"), 1);
}

TEST(Tables_manager, can_delete_element_out_of_tables)
{
	Tables_manager<string, int> a;
	a.insert("name1", 1);
	EXPECT_TRUE(a.delete_rec("name1"));
}

TEST(Tables_manager, false_when_try_to_delete_elem_from_empty_tables)
{
	Tables_manager<string, int> a;
	EXPECT_FALSE(a.delete_rec("name1"));
}

TEST(Tables_manager, false_when_try_to_delete_unexist_elem)
{
	Tables_manager<string, int> a;
	a.insert("name1", 1);
	EXPECT_FALSE(a.delete_rec("name2"));
}

TEST(Tables_manager, throws_when_try_to_find_elem_in_empty_tables)
{
	Tables_manager<string, int> a;
	ASSERT_ANY_THROW(a.find("name1"));
}

TEST(Tables_manager, throws_when_try_to_find_unexisting_elem)
{
	Tables_manager<string, int> a;
	a.insert("name1", 1);
	ASSERT_ANY_THROW(a.find("name2"));
}

TEST(Tables_manager, false_when_try_to_insert_elem_in_full_tables)
{
	Tables_manager<string, int> a;
	for (int i = 0; i < max_fill; i++)
		EXPECT_TRUE(a.insert("name" + to_string(i), i));
	EXPECT_FALSE(a.insert("name" + to_string(max_fill), max_fill));
}

TEST(Tables_manager, inserts_into_all_tables_at_once)
{
	Tables_manager<string, int> a;
	a.insert("name", 1);
	a.set_current(TableType::LIST_TABLE);
	EXPECT_EQ(a.find("name"), 1);
}

TEST(Tables_manager, delete_out_of_all_tables_at_once)
{
	Tables_manager<string, int> a;
	a.insert("name", 1);
	a.delete_rec("name");
	ASSERT_ANY_THROW(a.find("name"));
	a.set_current(TableType::LIST_TABLE);
	EXPECT_FALSE(a.delete_rec("name"));
}

TEST(Tables_manager, can_find_an_element_in_another_table)
{
	Tables_manager<string, int> a;
	a.insert("name", 1);
	a.set_current(TableType::SORTED_ARRAY_TABLE);
	EXPECT_EQ(a.find("name"), 1);
}

TEST(Tables_manager, false_when_insert_in_one_table_then_insert_it_in_another)
{
	Tables_manager<string, int> a;
	a.insert("name", 1);
	a.set_current(TableType::SORTED_ARRAY_TABLE);
	EXPECT_FALSE(a.insert("name",1));
}

TEST(Tables_manager, false_when_insert_in_one_table_then_insert_it_in_another_table_but_different_value)
{
	Tables_manager<string, int> a;
	a.insert("name", 1);
	a.set_current(TableType::SORTED_ARRAY_TABLE);
	EXPECT_FALSE(a.insert("name", 2));
}

TEST(Tables_manager, isEmpty_worked_correctly)
{
	Tables_manager<string, int> a;
	EXPECT_TRUE(a.isEmpty());
	a.insert("name1", 1);
	EXPECT_FALSE(a.isEmpty());
	a.delete_rec("name1");
	EXPECT_TRUE(a.isEmpty());
}

TEST(Tables_manager, can_insert_many_values_in_one_table_and_delete_all_in_another)
{
	Tables_manager<string, int> a;
	for (int i = 0; i < max_fill; i++)
		EXPECT_TRUE(a.insert("name" + to_string(i), i));
	a.set_current(TableType::LIST_TABLE);
	for (int i = 0; i < max_fill; i++)
		EXPECT_TRUE(a.delete_rec("name" + to_string(i)));
	EXPECT_TRUE(a.isEmpty());
}



