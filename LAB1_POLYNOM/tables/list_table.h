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
	List<record> table;
	size_t fill;
public:
	List_table();
	const T& find(const B& name) const override;
	bool insert(const B& name, const T& obj) override;
	bool delete_rec(const B& name) override;
	bool isEmpty() const override
	{
		return fill == 0;
	}
	~List_table() override;
};

#endif