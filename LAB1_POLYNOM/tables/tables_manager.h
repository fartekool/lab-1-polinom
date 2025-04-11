#ifndef TABLES_MANAGER_H
#define TABLES_MANAGER_H

#include <vector>
#include "array_table.h"
#include "avl_tree_table.h"
#include "hash_chaining_table.h"
#include "hash_open_addr_table.h"
#include "list_table.h"
#include "sorted_array_table.h"

const size_t count_of_tables = 6;

using table_type = size_t;

enum class TableType {
	ARRAY_TABLE = 0,
	AVL_TREE_TABLE = 1,
	HASH_CHAINING_TABLE = 2,
	HASH_OPEN_ADDR_TABLE = 3,
	LIST_TABLE = 4,
	SORTED_ARRAY_TABLE = 5
};

template<class T, class B>
class Tables_manager
{
	struct record
	{
		T key;
		B data;
	};
	enum class Operation {ins,del};
	vector<Base_table<T, B>*> tables;
	Base_table<T,B>* current_table;
	size_t tables_fill;
	record to_synchr;
	void sync(record elem, Operation op)
	{
		for (int i = 0; i < count_of_tables; i++)
		{
			if (op == Operation::del)
				tables[i]->delete_rec(elem.key);
			if (op == Operation::ins)
				tables[i]->insert(elem.key, elem.data);
		}
	}
public:
	Tables_manager() :tables_fill{ 0 }
	{
		tables.resize(count_of_tables);
		tables[static_cast<size_t>(TableType::ARRAY_TABLE)] = new Array_table<T, B>;
		tables[static_cast<size_t>(TableType::AVL_TREE_TABLE)] = new Avl_tree_table<T, B>;
		tables[static_cast<size_t>(TableType::HASH_CHAINING_TABLE)] = new Hash_chaining_table<T, B>;
		tables[static_cast<size_t>(TableType::HASH_OPEN_ADDR_TABLE)] = new Hash_open_addr_table<T, B>;
		tables[static_cast<size_t>(TableType::LIST_TABLE)] = new List_table<T, B>;
		tables[static_cast<size_t>(TableType::SORTED_ARRAY_TABLE)] = new Sorted_array_table<T, B>;
		current_table = tables[static_cast<size_t>(TableType::ARRAY_TABLE)];
	}
	void set_current(TableType table)
	{
		current_table = tables[static_cast<size_t>(table)];
	}
	B& find(const T& name)
	{
		return current_table->find(name);
	}
	bool insert(const T& name, const B& obj)
	{
		if (current_table->insert(name, obj))
		{
			tables_fill++;
			sync({ name,obj }, Operation::ins);
			return true;
		}
		else
			return false;
	}
	bool delete_rec(const T& name)
	{
		if (current_table->delete_rec(name))
		{
			tables_fill--;
			sync({ name }, Operation::del);
			return true;
		}
		else
			return false;
	}
	bool isEmpty() const
	{
		return current_table->isEmpty();
	}
	size_t GetFill() const
	{
		return tables_fill;
	}
	~Tables_manager() = default;
	vector<record> GetAllRecords() const
	{
		return current_table->GetAllRecords();
	}
};

#endif
