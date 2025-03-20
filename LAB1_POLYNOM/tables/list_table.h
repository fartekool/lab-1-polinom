#ifndef LIST_TABLE_H
#define LIST_TABLE_H

#include <string>
#include "base_table.h"
#include "../polynom/list.h"

template<class T,class B>
class List_table : public Base_table<T,B>
{
	struct record
	{
		T data;
		B key;
	};
	size_t fill;
	List<record> table;
public:
	List_table();
	const T& find(const B& name) const override
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
	bool insert(const B& name, const T& obj) override
	{
		for (int i = 0; i < table.size(); i++)
			if (table[i].key == name)
				return false;
		table.PushFront(record{ name, obj });
		fill++;
		return true;
	}
	bool delete_rec(const B& name) override
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
		return fill == 0;
	}
	~List_table() override;
};

#endif