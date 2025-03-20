#ifndef HASH_OPEN_ADDR_TABLE_H
#define HASH_OPEN_ADDR_TABLE_H

#include <string>
#include "base_table.h"

template<class T, class B>
class Hash_open_addr_table : public Base_table<T, B>
{
	size_t fill;
public:
	Hash_open_addr_table();
	B find(const T& name) const override;
	void insert(const T& name, const T& obj) override;
	void pop(const T& name) override;
	~Hash_open_addr_table() override;
};

#endif