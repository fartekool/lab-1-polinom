#ifndef AVL_TREE_TABLE_H
#define AVL_TREE_TABLE_H

#include <string>
#include "base_table.h"

template<class T, class B>
class Avl_tree_table : public Base_table<T, B>
{
	using Base_table<T, B>::record;
	using Base_table<T, B>::Fill;

	struct TNode {
		record rc;

		size_t height = 0;

		TNode* pLeft;
		TNode* pRight;

		TNode(const T& key, const B& data) : rc{ key, data }, height(1),
			pLeft(nullptr), pRight(nullptr) {}
		TNode() : height(1), pLeft(nullptr), pRight(nullptr) {}
	};

	TNode* pRoot;

	size_t Height(TNode* p) {
		return p ? p->height : 0;
	}

	int GetBalance(TNode* p) {
		return Height(p->pRight) - Height(p->pLeft);
	}

	void FixHeight(TNode* p) {
		size_t h_left = Height(p->pLeft);
		size_t h_right = Height(p->pRight);
		p->height = (h_left > h_right ? h_left : h_right) + 1;
	}

	TNode* RotateLeft(TNode* q) {
		TNode* p = q->pRight;
		q->pRight = p->pLeft;
		p->pLeft = q;
		FixHeight(q);
		FixHeight(p);
		return p;
	}

	TNode* RotateRight(TNode* p) {
		TNode* q = p->pLeft;
		p->pLeft = q->pRight;
		q->pRight = p;
		FixHeight(p);
		FixHeight(q);
		return q;
	}

	TNode* Balance(TNode* p) {
		FixHeight(p);
		if (GetBalance(p) == 2) { // большой поворот левого узла
			if (GetBalance(p->pRight) < 0)
				p->pRight = RotateRight(p->pRight);
			return RotateLeft(p);
		}
		if (GetBalance(p) == -2) { // большой поворот правого узла
			if (GetBalance(p->pLeft) > 0)
				p->pLeft = RotateLeft(p->pLeft);
			return RotateRight(p);
		}
		return p; // если балансировка не нужна
	}

	TNode* FindNode(const T& key, TNode* pNode) const {
		if (pNode == nullptr)
			return nullptr;
		if (pNode->rc.key == key)
			return pNode;
		if (key < pNode->rc.key && pNode->pLeft != nullptr)
			return FindNode(key, pNode->pLeft);
		if (key > pNode->rc.key && pNode->pRight != nullptr)
			return FindNode(key, pNode->pRight);
		return nullptr;
	}

	TNode* InsertNode(TNode* p, const T& key, const B& data) {
		if (p == nullptr)
			return new TNode(key, data);

		if (key < p->rc.key)
			p->pLeft = InsertNode(p->pLeft, key, data);
		else if (key > p->rc.key)
			p->pRight = InsertNode(p->pRight, key, data);
		else return p; // Ключ уже существует

		return Balance(p);
	}

	TNode* FindMin(TNode* p) {  // поиск узла с минимальным ключом в дереве p
		return p->pLeft ? FindMin(p->pLeft) : p;
	}

	TNode* RemoveMin(TNode* p) { // удаление узла с минимальным ключом из дерева p
		if (p->pLeft == nullptr)
			return p->pRight;
		p->pLeft = RemoveMin(p->pLeft);
		return Balance(p);
	}

	TNode* Remove(TNode* p, const T& key) {
		if (p == nullptr)
			return nullptr;

		if (key < p->rc.key)
			p->pLeft = Remove(p->pLeft, key);
		else if (key > p->rc.key)
			p->pRight = Remove(p->pRight, key);
		else {
			TNode* left = p->pLeft;
			TNode* right = p->pRight;
			delete p;

			if (right == nullptr) return left;

			TNode* min = FindMin(right);
			min->pRight = RemoveMin(right);
			min->pLeft = left;
			return Balance(min);
		}

		return Balance(p);
	}

	void DeleteTree(TNode* node) {
		if (node != nullptr) {
			DeleteTree(node->pLeft);
			DeleteTree(node->pRight);
			delete node;
		}
	}

	void GetRecord(TNode* node, vector<record>& records) const {
		if (node != nullptr) {
			GetRecord(node->pLeft, records);
			records.push_back(node->rc);
			GetRecord(node->pRight, records);
		}
	}
public:
	Avl_tree_table() {
		Fill = 0;
		pRoot = nullptr;
	}

	B& find(const T& name) override {
		if (isEmpty())
			throw runtime_error("Table is empty!");

		TNode* pNode = FindNode(name, pRoot);

		if (pNode == nullptr)
			throw runtime_error("Key not found!");

		return pNode->rc.data;
	}

	bool insert(const T& name, const B& obj) override {
		if (Fill == max_fill)
			return false;

		if (FindNode(name, pRoot) != nullptr)
			return false;

		pRoot = InsertNode(pRoot, name, obj);
		Fill++;
		return true;
	}

	bool delete_rec(const T& name) override {
		if (isEmpty())
			return false;

		if (FindNode(name, pRoot) == nullptr)
			return false;

		pRoot = Remove(pRoot, name);
		Fill--;
		return true;
	}

	bool isEmpty() const override
	{
		return Fill == 0;
	}

	vector<record> GetAllRecords() const override
	{
		vector<record> records;
		GetRecord(pRoot, records);
		return records;
	}

	~Avl_tree_table() override {
		DeleteTree(pRoot);
	}
};

#endif