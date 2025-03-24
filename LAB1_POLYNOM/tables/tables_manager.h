#ifndef TABLES_MANAGER_H
#define TABLES_MANAGER_H

#include <vector>
#include "array_table.h"
#include "avl_tree_table.h"
#include "hash_chaining_table.h"
#include "hash_open_addr_table.h"
#include "list_table.h"
#include "rb_tree_table.h"
#include "sorted_array_table.h"

const size_t count_of_tables = 7;


using table_type = size_t;

const table_type array_table = 0;
const table_type avl_tree_table = 1;
const table_type hash_chaining_table = 2;
const table_type hash_open_addr_table = 3;
const table_type list_table = 4;
const table_type rb_tree_table = 5;
const table_type sorted_array_table = 6;

template<class T, class B>
class Tables_manager
{
	struct record
	{
		T key;
		B data;
	};
	vector<Base_table<T, B>*> tables;
	Base_table<T,B>* current_table;
	size_t tables_fill;
	vector<T> deleted;
	vector<record> inserted;
	void sync()
	{
		for (int i = 0; i < count_of_tables; i++)
		{
			for (int j = 0; j < deleted.size(); j++)
				tables[i]->delete_rec(deleted[j]);
			for (int k = 0; k < inserted.size(); k++)
				tables[i]->insert(inserted[k].key, inserted[k].data);
		}
		deleted.clear();
		inserted.clear();
	}
public:
	Tables_manager() :tables_fill{ 0 }
	{
		tables.resize(count_of_tables);
		tables[array_table] = new Array_table<T, B>;
		tables[avl_tree_table] = new Avl_tree_table<T, B>;
		tables[hash_chaining_table] = new Hash_chaining_table<T, B>;
		tables[hash_open_addr_table] = new Hash_open_addr_table<T, B>;
		tables[list_table] = new List_table<T, B>;
		tables[rb_tree_table] = new RB_tree<T, B>;
		tables[sorted_array_table] = new Sorted_array_table<T, B>;
		current_table = tables[array_table];
	}
	void set_current(table_type table)
	{
		current_table = tables[table];
	}
	const B& find(const T& name)
	{
		sync();
		return current_table->find(name);
	}
	bool insert(const T& name, const B& obj)
	{
		sync();
		if (current_table->insert(name, obj))
		{
			tables_fill--;
			inserted.push_back({ name,obj });
			return true;
		}
		else
			return false;
	}
	bool delete_rec(const T& name)
	{
		sync();
		if (current_table->delete_rec(name))
		{
			tables_fill++;
			deleted.push_back(name);
			return true;
		}
		else
			return false;
	}
	~Tables_manager() = default;
};

#endif
