#ifndef RB_TREE_TABLE_H
#define RB_TREE_TABLE_H

#include <string>
#include "base_table.h"

template<class T, class B>
class RB_tree : public Base_table<T, B>
{
	size_t fill;
public:
	RB_tree();
	T find(const string& name) const override;
	void insert(const string& name, const T& obj) override;
	void pop(const string& name) override;
	~RB_tree() override;
};

#endif
