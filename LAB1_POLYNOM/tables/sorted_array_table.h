#ifndef SORTED_ARRAY_TABLE_H
#define SORTED_ARRAY_TABLE_H

#include <string>
#include "base_table.h"

template<class T>
class Sorted_array_table : public Base_table<T>
{
	size_t fill;
public:
	Sorted_array_table();
	T find(const string& name) const override;
	void insert(const string& name, const T& obj) override;
	void pop(const string& name) override;
	~Sorted_array_table() override;
};

#endif