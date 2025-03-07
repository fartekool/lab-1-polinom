#include "gtest.h"
#include "../polynom/list.h"

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> tmp{});
}

TEST(List, can_copy_list)
{
	List<int> tmp{};

	ASSERT_NO_THROW(List<int> test(tmp));
}

TEST(List, can_push_back)
{
	List<int> test{};
	ASSERT_NO_THROW(test.push_back(1));
}

TEST(List, can_get_size)
{
	List<int> test{};

	EXPECT_EQ(0, test.get_size());
	test.push_back(1);

	EXPECT_EQ(1, test.get_size());
}

TEST(List, is_empty_working)
{
	List<int> test{};

	EXPECT_TRUE(test.is_empty());

	test.push_back(1);

	EXPECT_FALSE(test.is_empty());
}

TEST(List, push_back_and_indexation_operator_working_correctly)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);

	EXPECT_EQ(test[0], 1);
	EXPECT_EQ(test[1], 2);
}

TEST(List, comparison_operator_working_correctly)
{
	List<int> one{};
	one.push_back(1);
	one.push_back(2);
	one.push_back(3);

	List<int> another{};
	another.push_back(1);
	another.push_back(2);
	another.push_back(3);

	EXPECT_TRUE(one == another);

	another[2] = 100;

	EXPECT_TRUE(one != another);
}

TEST(List, throws_when_try_to_erase_from_empty_list)
{
	List<int> test{};

	ASSERT_ANY_THROW(test.erase(0));
}

TEST(List, throws_when_try_to_erase_out_of_range)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	ASSERT_ANY_THROW(test.erase(3));
}

TEST(List, throws_when_try_to_erase_element_with_negative_index)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	ASSERT_ANY_THROW(test.erase(-1));
}

TEST(List, erase_element_correctly)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	test.erase(1);

	EXPECT_EQ(3, test[1]);
}

TEST(List, change_size_when_erase)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	test.erase(1);

	EXPECT_EQ(2, test.get_size());
}

TEST(List, indexation_operator_can_set_and_get_element)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	test[2] = 4;

	EXPECT_EQ(4, test[2]);
}

TEST(List, indexation_operator_throws_if_index_is_invalid)
{
	List<int> test{};
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	ASSERT_ANY_THROW(test[3] = 4);
	ASSERT_ANY_THROW(test[-1] = 0);
}

TEST(List, can_assign_lists_correctly)
{
	List<int> one{};
	one.push_back(1);
	one.push_back(2);
	one.push_back(3);

	List<int> another{};
	another = one;

	EXPECT_EQ(one, another);
}