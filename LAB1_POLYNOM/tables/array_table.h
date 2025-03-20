#ifndef ARRAY_TABLE_H
#define ARRAY_TABLE_H

#include "base_table.h"

template<class T, class B>
class Array_table: public Base_table<T,B>
{
	struct record
	{
		T data;
		B key;
	};
	vector<record> table;
	size_t fill;
public:
	Array_table() : fill(0) {};
	const T& find(const B& name) const override;
	bool insert(const B& name, const T& obj) override;
	bool delete_rec(const B& name) override;
	bool isEmpty() const
	{
		return fill == 0;
	}
};

#endif
