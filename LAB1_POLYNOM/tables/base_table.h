#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <string>

using namespace std;

const size_t max_fill = 1000;

template<class T>
class Base_table
{
	size_t fill;
public:
	Base_table() = 0;
	virtual T find(const string& name) const = 0;
	virtual void insert(const string& name, const T& obj) = 0;
	virtual void pop(const string& name) = 0;
	virtual ~Base_table() = 0;
};

#endif