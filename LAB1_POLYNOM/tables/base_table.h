#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

const size_t max_fill = 500;

template<class T, class B>
struct record
{
	T key;
	B data;
};

template<class T, class B>
class Base_table
{
protected:
	
	size_t Fill;
public:
	virtual B& find(const T& name) = 0;
	virtual bool insert(const T& name, const B& obj) = 0;
	virtual bool delete_rec(const T& name) = 0;
	virtual bool isEmpty() const = 0;
	virtual vector<record<T, B>> GetAllRecords() const = 0;
	virtual ~Base_table() = default;
};

#endif