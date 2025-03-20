#ifndef AVL_TREE_TABLE_H
#define AVL_TREE_TABLE_H

#include <string>
#include "base_table.h"

template<class T, class B>
class Avl_tree_table : public Base_table<T, B>
{
	size_t fill;
public:
	Avl_tree_table();
	T find(const string& name) const override;
	void insert(const string& name, const T& obj) override;
	void pop(const string& name) override;
	~Avl_tree_table() override;
};

#endif