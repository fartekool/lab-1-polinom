#pragma once

#include "base_table.h"

template<class T, class B>
class Array_table : public Base_table<T, B>
{
	struct record
	{
		T data;
		B key;
	};
	vector<record> table;
	size_t fill;
public:
	Array_table() : fill(0) {};
	const T& find(const B& name) const override
	{
		if (this->isEmpty())
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
		record a;
		a.data = obj;
		a.key = name;
		table.push_back(a);
		fill++;
		return true;
	}
	bool delete_rec(const B& name) override
	{
		if (this->isEmpty())
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

