#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

const size_t max_fill = 1000;

template<class T>
class Base_table
{
protected:
	struct record
	{
		T data;
		string key;
	};
	size_t Fill;
public:
	virtual const T& find(const string& name) const = 0;
	virtual bool insert(const string& name, const T& obj) = 0;
	virtual bool delete_rec(const string& name) = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Base_table() = default;
};

#endif