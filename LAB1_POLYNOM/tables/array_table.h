#ifndef ARRAY_TABLE_H
#define ARRAY_TABLE_H

#include "base_table.h"

template<class T, class B>
class Array_table: public Base_table<T, B>
{

	using Base_table<T, B>::Fill;
	vector<record<T, B>> table;
public:
	Array_table() { Fill = 0; }
	B& find(const T& name) override
	{
		if (isEmpty())
			throw runtime_error("Table is empty!");
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return table[i].data;
		throw runtime_error("Key not found!");
	}
	bool insert(const T& name, const B& obj) override
	{
		if (Fill == max_fill)//?
			return false;
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return false;
		table.push_back(record<T, B>{ name, obj });
		Fill++;
		return true;
	}
	bool delete_rec(const T& name) override
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
	vector<record<T, B>> GetAllRecords() const override
	{
		return table;
	}
	~Array_table() = default;
};
#endif
