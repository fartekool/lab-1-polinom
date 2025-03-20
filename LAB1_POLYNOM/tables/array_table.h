#ifndef ARRAY_TABLE_H
#define ARRAY_TABLE_H

#include "base_table.h"

template<class T, class B>
class Array_table: public Base_table<T,B>
{
	struct record
	{
		T data;
		B key;
	};
	size_t fill;
	vector<record> table;
public:
	Array_table() : fill(0) {};
	const T& find(const B& name) const override
	{
		if (is_empty())
			throw runtime_error("Table is empty!");//придумать вариант получше
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return table[i].data;
		throw runtime_error("Key not finded!");//придумать вариант получше
	}
	bool insert(const B& name, const T& obj) override
	{
		if (fill == max_fill)//?
			return false;
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return false;
		table.push_back(record{ name, obj });
		fill++;
		return true;
	}
	bool delete_rec(const B& name) override
	{
		if (isEmpty())
			return false;
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
			{
				table.erase(table.begin() + i);
				fill--;
				return true;
			}
		return false;
	}
	bool isEmpty() const
	{
		return fill == 0;
	}
};

#endif
