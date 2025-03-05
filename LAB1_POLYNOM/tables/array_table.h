#ifndef ARRAY_TABLE_H
#define ARRAY_TABLE_H

#include <string>
#include "base_table.h"

template<class T>
class Array_table: public Base_table<T>
{
	size_t fill;
public:
	Array_table();
	T find(const string& name) const override;
	void insert(const string& name, const T& obj) override;
	void pop(const string& name) override;
	~Array_table() override;
};

#endif
