#ifndef ARRAY_TABLE_H
#define ARRAY_TABLE_H

#include "base_table.h"

template<class T>
class Array_table: public Base_table<T>
{
	using Base_table<T>::record;
	using Base_table<T>::Fill;
	vector<record> table;
public:
	Array_table() { Fill = 0; }
	const T& find(const string& name) const override
	{
		if (isEmpty())
			throw runtime_error("Table is empty!");//придумать вариант получше
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return table[i].data;
		throw runtime_error("Key not finded!");//придумать вариант получше
	}
	bool insert(const string& name, const T& obj) override
	{
		if (Fill == max_fill)//?
			return false;
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return false;
		table.push_back(record{ obj,name });
		Fill++;
		return true;
	}
	bool delete_rec(const string& name) override
	{
		if (isEmpty())
			return false;
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
			{
				table.erase(table.begin() + i);
				Fill--;
				return true;
			}
		return false;
	}
	bool isEmpty() const
	{
		return Fill == 0;
	}
	~Array_table() = default;
};
#endif
