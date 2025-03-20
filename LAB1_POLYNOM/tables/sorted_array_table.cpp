#include "sorted_array_table.h"

template<class T, class B>
Sorted_array_table<T, B>::binary_result Sorted_array_table<T, B>::binary_search(const B& name)
{
	size_t left = 0;
	size_t right = table.size() - 1;
	size_t mid = right / 2;
	size_t position;
	while (left <= right)
	{
		if (table[mid].key == name)
		{
			position = mid;
			return binary_result{ true,position };//true - значит, что элемент есть
		}
		else if (name < table[mid].key)
			right = mid - 1;
		else if (name > table[mid].key)
			left = mid + 1;
		mid = left + (right - left) / 2;
	}
	return binary_result{ false, left };
}

template<class T, class B>
void Sorted_array_table<T,B>::shift_elem(size_t pos, const B& name, const T& obj)
{
	table.push_back(record{ obj,name });
	for (int i = table.size() - 1; i > pos; i--)
	{
		record tmp = table[i];
		table[i] = table[i - 1];
		table[i - 1] = tmp;
	}
}

template<class T, class B>
const T& Sorted_array_table<T, B>::find(const B& name) const
{
	if (isEmpty())
		throw runtime_error("Table is empty!");
	binary_result search = binary_search(table, name);
	if (search.flag)
		return table[search.index];
	throw runtime_error("Key not finded!");

}

template<class T, class B>
bool compare(const typename Sorted_array_table<T,B>::record& left, const typename Sorted_array_table<T, B>::record& right)
{
	return left.key < right.key;
}

template<class T, class B>
bool Sorted_array_table<T, B>::insert(const B& name, const T& obj)
{
	if (fill == max_fill)
		return false;
	binary_result search = binary_search(name);
	if (search.flag)
		return false;
	shift_elem(search.index, name, obj);
	fill++;
	return true;
}

template<class T, class B>
bool Sorted_array_table<T, B>::delete_rec(const B& name)
{
	if (is_empty())
		return false;
	binary_result search = binary_search(name);
	if (!search.flag)
		return false;
	table.erase(table.begin() + search.index);
	fill--;
	return true;
}