#pragma once
#include <string>
template<class T>
class Array_table
{
	T find(const std::string& name) const;
	void insert(const std::string& name, const T& obj);
	void pop(const std::string& name);
};
