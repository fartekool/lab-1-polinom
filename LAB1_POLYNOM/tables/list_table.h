#ifndef LIST_TABLE_H
#define LIST_TABLE_H

#include <string>
#include "base_table.h"

template<class T>
class List_table : public Base_table<T>
{
	size_t fill;
public:
	List_table();
	T find(const string& name) const override;
	void insert(const string& name, const T& obj) override;
	void pop(const string& name) override;
	~List_table() override;
};

#endif