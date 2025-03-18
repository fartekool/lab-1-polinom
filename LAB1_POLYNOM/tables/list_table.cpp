#include "list_table.h"


template<class T, class B>
T& List_table<T, B>::find(const B& name) const
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

template<class T, class B>
bool List_table<T, B>::insert(const B& name,const T& obj)
{
	for (int i = 0; i < table.size(); i++)
		if (table[i].key == name)
			return false;
	table.PushFront(record{ name, obj });
	fill++;
	return true;
}

template<class T, class B>
bool List_table<T, B>::delete_rec(const B& name)
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