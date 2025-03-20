#ifndef SORTED_ARRAY_TABLE_H
#define SORTED_ARRAY_TABLE_H

#include <string>
#include <algorithm>
#include "base_table.h"

template<class T, class B>
class Sorted_array_table : public Base_table<T,B>
{
	struct record
	{
		T data;
		B key;
	};
	struct binary_result
	{
		bool flag;
		size_t index;
	};
	vector<record> table;
	size_t fill;
	void shift_elem(size_t pos, const B& name, const T& obj);
	binary_result binary_search(const B& name);
public:
	Sorted_array_table() :fill(0) {}
	const T& find(const B& name) const override;
	bool insert(const B& name, const T& obj) override;
	bool delete_rec(const B& name) override;
	bool isEmpty() const override
	{
		return fill == 0;
	}
	friend bool compare(const record& left, const record& right);
	~Sorted_array_table() override;
};

#endif