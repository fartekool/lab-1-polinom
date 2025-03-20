#ifndef SORTED_ARRAY_TABLE_H
#define SORTED_ARRAY_TABLE_H

#include <string>
#include <algorithm>
#include "base_table.h"

template<class T, class B>
class Sorted_array_table : public Base_table<T, B>
{
	using Base_table<T, B>::record;
	using Base_table<T, B>::Fill;
	struct binary_result
	{
		bool flag;
		size_t index;
	};
	vector<record> table;
	void shift_elem(size_t pos, const string& name, const T& obj)
	{
		table.push_back(record{ obj,name });
		for (int i = table.size() - 1; i > pos; i--)
		{
			record tmp = table[i];
			table[i] = table[i - 1];
			table[i - 1] = tmp;
		}
	}
	binary_result binary_search(const string& name)
	{
		size_t left = 0;
		size_t right = table.size() - 1;
		size_t mid = right / 2;
		size_t position;
		while (left <= right)
		{
			if (table[mid].key == name)
			{
				position = mid;
				return binary_result{ true,position };//true - значит, что элемент есть
			}
			else if (name < table[mid].key)
				right = mid - 1;
			else if (name > table[mid].key)
				left = mid + 1;
			mid = left + (right - left) / 2;
		}
		return binary_result{ false, left };
	}
public:
	Sorted_array_table() :Fill(0) {}
	const T& find(const string& name) const override
	{
		if (isEmpty())
			throw runtime_error("Table is empty!");
		binary_result search = binary_search(table, name);
		if (search.flag)
			return table[search.index];
		throw runtime_error("Key not finded!");
	}
	bool insert(const string& name, const T& obj) override
	{
		if (Fill == max_fill)
			return false;
		binary_result search = binary_search(name);
		if (search.flag)
			return false;
		shift_elem(search.index, name, obj);
		Fill++;
		return true;
	}
	bool delete_rec(const string& name) override
	{
		if (isEmpty())
			return false;
		binary_result search = binary_search(name);
		if (!search.flag)
			return false;
		table.erase(table.begin() + search.index);
		Fill--;
		return true;
	}
	bool isEmpty() const override
	{
		return Fill == 0;
	}
	~Sorted_array_table() override = default;
};

#endif