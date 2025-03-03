#pragma once
#include <string>
template<class T>
class Hash_open_addr_table
{
	T find(const std::string& name) const;
	void insert(const std::string& name, const T& obj);
	void pop(const std::string& name);
};
