#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

const size_t max_fill = 1000;

template<class T,class B>
class Base_table
{
	struct record
	{
		T data;
		B key;
	};
	size_t fill;
public:
	virtual const T& find(const B& name) const = 0;
	virtual bool insert(const B& name, const T& obj) = 0;
	virtual bool delete_rec(const B& name) = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Base_table();
};

#endif