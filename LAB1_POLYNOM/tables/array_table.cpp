#include "array_table.h"

template<class T, class B>
const T& Array_table<T, B>::find(const B& name) const
{
	if (is_empty())
		throw runtime_error("Table is empty!");//придумать вариант получше
	for (int i = 0; i < table.size(); i++)
		if (table[i].key == name)
			return table[i].data;
	throw runtime_error("Key not finded!");//придумать вариант получше
}

template<class T, class B>
bool Array_table<T, B>::insert(const B& name, const T& obj)
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

template<class T, class B>
bool Array_table<T, B>::delete_rec(const B& name)
{
	if (is_empty())
		return false;
	for(int i = 0;i<table.size();i++)
		if (table[i].key == name)
		{
			table.erase(table.begin() + i);
			fill--;
			return true;
		}
	return false;
}