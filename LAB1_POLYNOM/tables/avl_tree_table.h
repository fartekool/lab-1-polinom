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
		if (GetBalance(p) == 2) { // ������� ������� ������ ����
			if (GetBalance(p->pRight) < 0)
				p->pRight = RotateRight(p->pRight);
			return RotateLeft(p);
		}
		if (GetBalance(p) == -2) { // ������� ������� ������� ����
			if (GetBalance(p->pLeft) > 0)
				p->pLeft = RotateLeft(p->pLeft);
			return RotateRight(p);
		}
		return p; // ���� ������������ �� �����
	}

	TNode* FindNode(const T& key, TNode* pNode) const {
		if (pNode == nullptr)
			return nullptr;
		if (key < pNode->rc.key)
			pNode = FindNode(key, pNode->pLeft);
		if (key > pNode->rc.key)
			pNode = FindNode(key, pNode->pRight);
		return pNode;

	}

	TNode* InsertNode(TNode* p, const T& key, const B& data) {
		if (p == nullptr)
			return new TNode(key, data);

		if (key < p->rc.key)
			p->pLeft = InsertNode(p->pLeft, key, data);
		else if (key > p->rc.key)
			p->pRight = InsertNode(p->pRight, key, data);
		else return p; // ���� ��� ����������

		return Balance(p);
	}

	void DeleteTree(TNode* node) {
		if (node != nullptr) {
			DeleteTree(node->pLeft);
			DeleteTree(node->pRight);
			delete node;
		}
	}

public:
	Avl_tree_table() {
		Fill = 0;
		pRoot = nullptr;
	}
	const B& find(const T& name) const override {
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
		return true;
	}

	bool isEmpty() const override
	{
		return Fill == 0;
	}

	~Avl_tree_table() override {
		DeleteTree(pRoot);
	}
};

#endif