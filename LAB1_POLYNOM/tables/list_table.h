#ifndef LIST_TABLE_H
#define LIST_TABLE_H

#include <string>
#include "base_table.h"
#include "../polynom/list.h"

template<class T, class B>
class List_table : public Base_table<T, B>
{
	using Base_table<T, B>::record;
	using Base_table<T, B>::Fill;
	List<record> table;
public:
	List_table() { Fill = 0; }
	B& find(const T& name) override
	{
		if (table.isEmpty())
			throw runtime_error("Table is empty!");
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].key == name)
			{
				return table[i].data;
				break;
			}
		}
		throw runtime_error("Key not finded!");
	}
	bool insert(const T& name, const B& obj) override
	{
		if (Fill == max_fill)
			return false;
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return false;
		table.PushFront(record{ name, obj });
		Fill++;
		return true;
	}
	bool delete_rec(const T& name) override
	{
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
			{
				if (i == 0)
					table.PopFront();
				else
					table.EraseAfter(i - 1);
				Fill--;
				return true;
			}
		return false;
	}
	bool isEmpty() const override
	{
		return Fill == 0;
	}
	~List_table() = default;
};
#endif