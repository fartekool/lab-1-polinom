#ifndef HASH_CHAINING_TABLE_H
#define HASH_CHAINING_TABLE_H

#include <string>
#include "base_table.h"

template<class T>
class Hash_chaining_table : public Base_table<T>
{
	size_t fill;
public:
	Hash_chaining_table();
	T find(const string& name) const override;
	void insert(const string& name, const T& obj) override;
	void pop(const string& name) override;
	~Hash_chaining_table() override;
};

#endif