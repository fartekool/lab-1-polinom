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

template<class T>
class Tables_manager
{
	vector<Base_table<T>*> tables(count_of_tables);
	vector<T> database;//мб тоже не надо
	Base_table* current_table;//тут можно тэйбл_тайпом наверное
	//а может и не лучше
	size_t tables_fill;
	bool are_sync;//тут наверное задел на оптимизацию, пока не уверен, нужно ли это (типа синхронизировать таблички только по надобности)
	void sync();
public:
	Tables_manager() :tables_fill{ 0 }, are_sync{ true };
	~Tables_manager();
	size_t get_fill();
	bool get_condition();//возможно во вне это не нужно
	void set_current(table_type table);
	T find(const string& name);
	void insert(const string& name, const T& obj);
	void pop(const string& name);
};

#endif
