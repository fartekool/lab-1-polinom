#ifndef HASH_CHAINING_TABLE_H
#define HASH_CHAINING_TABLE_H

#include "base_table.h"
#include "../polynom/list.h"
#include <bitset>

const size_t max_count_of_rows = 100;
const size_t default_count_of_rows = 10;

template<class T, class B>
class Hash_chaining_table : public Base_table<T, B>
{
	using Base_table<T, B>::record;
	using Base_table<T, B>::Fill;
	vector<List<record>> table;
	size_t count_of_rows;
public:
	Hash_chaining_table(size_t rows = default_count_of_rows)
	{
		Fill = 0;
		if (rows > max_count_of_rows)
			throw out_of_range("The allowed number of rows has been exceeded!");
		count_of_rows = rows;
		table.resize(count_of_rows);
	}
	int hash_function( const T& name) const
	{
		const unsigned char* data = reinterpret_cast<const unsigned char*>(&name);
		int len = sizeof(name);
		int hashcode = 0;
		const unsigned char last_byte = data[len - 1];
		bitset<8> last_bites(last_byte);
		for (int i = 0; i < last_bites.size(); i++)
			hashcode += last_bites[i] * (i + 1);
		return hashcode % count_of_rows;
	}
	B& find(const T& name) override
	{
		if (isEmpty())
			throw runtime_error("Table is empty!");
		int hashcode = hash_function(name);
		for (int i = 0; i < table[hashcode].size(); i++)
			if (table[hashcode][i].key == name)
				return table[hashcode][i].data;
		throw out_of_range("Key not found!");
	}
	bool insert(const T& name, const B& obj) override
	{
		if (Fill == max_fill)
			return false;
		int hashcode = hash_function(name);
		for (int i = 0; i < table[hashcode].size(); i++)
			if (table[hashcode][i].key == name)
				return false;//ключ уже есть
		table[hashcode].PushFront(record{ name, obj });
		Fill++;
		return true;
	}
	bool delete_rec(const T& name) override
	{
		if (isEmpty())
			return false;
		int hashcode = hash_function(name);
		for (int i = 0; i < table[hashcode].size(); i++)
			if (table[hashcode][i].key == name)
			{
				if (i == 0)
					table[hashcode].PopFront();
				else
					table[hashcode].EraseAfter(i - 1);
				Fill--;
				return true;
			}
		return false;
	}
	bool isEmpty() const
	{
		return Fill == 0;
	}
	vector<record> GetAllRecords() const override
	{
		vector<record> records;
		for (int i = 0; i < table.size(); i++)
			for (int j = 0; j < table[i].size(); j++)
				records.push_back(table[i][j]);
		return records;
	}
	~Hash_chaining_table() override = default;
};

#endif