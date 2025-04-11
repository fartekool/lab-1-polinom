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
		int index;
	};
	vector<record> table;
	void shift_elem(size_t pos, const T& name, const B& obj)
	{
		table.push_back(record{ name, obj });
		for (int i = table.size() - 1; i > pos; i--)
		{
			record tmp = table[i];
			table[i] = table[i - 1];
			table[i - 1] = tmp;
		}
	}
	binary_result binary_search(const T& name) const
	{
		int left = 0;
		int right = table.size() - 1;
		int mid;
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (table[mid].key == name)
				return binary_result{ true,mid };//true - значит, что элемент есть
			else if (name < table[mid].key)
				right = mid - 1;
			else if (name > table[mid].key)
				left = mid + 1;
		}
		return binary_result{ false, left };
	}
public:
	Sorted_array_table() { Fill = 0; }
	B& find(const T& name) override
	{
		if (isEmpty())
			throw runtime_error("Table is empty!");
		binary_result search = binary_search(name);
		if (search.flag)
			return table[search.index].data;
		throw runtime_error("Key not finded!");
	}
	bool insert(const T& name, const B& obj) override
	{
		if (Fill == max_fill)
			return false;
		if (table.size() == 0)
		{
			table.push_back(record{ name,obj });
			Fill++;
			return true;
		}
		binary_result search = binary_search(name);
		if (search.flag)
			return false;
		shift_elem(search.index, name, obj);
		Fill++;
		return true;
	}
	bool delete_rec(const T& name) override
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
	bool isSorted()
	{
		if (isEmpty())
			return true;
		for (int i = 1; i < table.size(); i++)
			if (table[i].key < table[i - 1].key)
				return false;
		return true;
	}
	vector<record> GetAllRecords() const override
	{
		return table;
	}
	~Sorted_array_table() override = default;
};

#endif