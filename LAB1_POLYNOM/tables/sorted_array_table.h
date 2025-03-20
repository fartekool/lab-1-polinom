#ifndef SORTED_ARRAY_TABLE_H
#define SORTED_ARRAY_TABLE_H

#include <string>
#include <algorithm>
#include "base_table.h"

template<class T, class B>
class Sorted_array_table : public Base_table<T,B>
{
	struct record
	{
		T data;
		B key;
	};
	size_t fill;
	struct binary_result
	{
		bool flag;
		size_t index;
	};
	vector<record> table;
	void shift_elem(size_t pos, const B& name, const T& obj)
	{
		table.push_back(record{ obj,name });
		for (int i = table.size() - 1; i > pos; i--)
		{
			record tmp = table[i];
			table[i] = table[i - 1];
			table[i - 1] = tmp;
		}
	}
	binary_result binary_search(const B& name)
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
	Sorted_array_table() :fill(0) {}
	const T& find(const B& name) const override
	{
		if (isEmpty())
			throw runtime_error("Table is empty!");
		binary_result search = binary_search(table, name);
		if (search.flag)
			return table[search.index];
		throw runtime_error("Key not finded!");
	}
	bool insert(const B& name, const T& obj) override
	{
		if (fill == max_fill)
			return false;
		binary_result search = binary_search(name);
		if (search.flag)
			return false;
		shift_elem(search.index, name, obj);
		fill++;
		return true;
	}
	bool delete_rec(const B& name) override
	{
		if (is_empty())
			return false;
		binary_result search = binary_search(name);
		if (!search.flag)
			return false;
		table.erase(table.begin() + search.index);
		fill--;
		return true;
	}
	bool isEmpty() const override
	{
		return fill == 0;
	}
	~Sorted_array_table() override = default;
};

#endif