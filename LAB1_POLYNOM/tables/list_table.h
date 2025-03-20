#ifndef LIST_TABLE_H
#define LIST_TABLE_H

#include <string>
#include "base_table.h"
#include "../polynom/list.h"

template<class T>
class List_table : public Base_table<T>
{
	using Base_table<T>::record;
	using Base_table<T>::Fill;
	List<record> table;
public:
	List_table() : Fill(0) {}
	const T& find(const string& name) const override
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
	bool insert(const string& name, const T& obj) override
	{
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return false;
		table.PushFront(record{ obj,name });
		Fill++;
		return true;
	}
	bool delete_rec(const string& name) override
	{
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
			{
				table.EraseAfter(i - 1);
				fill--;
				return true;
			}
		return false;
	}
	bool isEmpty() const override
	{
		return Fill == 0;
	}
	~List_table() override;
};
#endif