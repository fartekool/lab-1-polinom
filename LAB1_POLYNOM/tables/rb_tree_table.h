#ifndef RB_TREE_TABLE_H
#define RB_TREE_TABLE_H

#include <string>
#include <stack>
#include "base_table.h"

template<class T, class B>
class RB_tree : public Base_table<T, B>
{
	using Base_table<T, B>::record;
	using Base_table<T, B>::Fill;

	enum class Color { RED, BLACK };

	struct TNode {
		record rc;

		TNode* pLeft;
		TNode* pRight;
		TNode* Parent;
		Color color;

		TNode(const T& key, const B& data) : rc{ key, data },
			pLeft(nullptr), pRight(nullptr), Parent(nullptr), color(Color::BLACK) {}
		TNode() : pLeft(nullptr), pRight(nullptr), Parent(nullptr), color(Color::BLACK) {}
	};

	TNode* nil;

	TNode* pRoot;

	TNode* FindNode(const T& key, TNode* pNode) const {
		if (pNode == nil)
			return nil;
		if (key < pNode->rc.key)
			pNode = FindNode(key, pNode->pLeft);
		if (key > pNode->rc.key)
			pNode = FindNode(key, pNode->pRight);
		return pNode;

	}

	TNode* FindInsertionPoint(const T& key, stack<TNode*>& path) {
		TNode* current = pRoot;
		TNode* parent = nil;

		while (current != nil) {
			parent = current;
			path.push(current);

			if (key < current->rc.key) {
				current = current->pLeft;
			}
			else if (key > current->rc.key) {
				current = current->pRight;
			}
			else {
				return current;
			}
		}

		return parent;
	}

	TNode* FindNodeToDelete(const T& key, stack<TNode*>& path)
	{
		TNode* current = pRoot;

		while (current != nil) {
			path.push(current);

			if (key < current->rc.key) {
				current = current->pLeft;
			}
			else if (key > current->rc.key) {
				current = current->pRight;
			}
			else {
				return current; // вершина найдена
			}
		}

		return nil; // вершина не найдена
	}

	void DeleteTree(TNode* node) {
		if (node != nil) {
			DeleteTree(node->pLeft);
			DeleteTree(node->pRight);
			delete node;
		}
	}

public:
	RB_tree() {
		Fill = 0;
		nil = new TNode{ T(), B() };
		nil->color = Color::BLACK;
		pRoot = nil;
	}

	const B& find(const T& name) const override {
		if (isEmpty())
			throw runtime_error("Table is empty!");

		TNode* pNode = FindNode(name, pRoot);

		if (pNode == nil)
			throw runtime_error("Key not found!");

		return pNode->rc.data;
	}

	bool insert(const T& name, const B& obj) override {
		if (Fill == max_fill)
			return false;

		stack<TNode*> path;

		TNode* parent = FindInsertionPoint(name, path);
		if (parent == nil) // нам вернулс€ nil -> либо такой ключ уже существует, либо нет корн€
		{
			if (pRoot == nil) { // дерево пустое, создаЄм корень
				pRoot = new TNode(name, obj);
				pRoot->color = Color::BLACK;
				pRoot->pLeft = nil;
				pRoot->pRight = nil;
			}
			else
				return false; // иначе ключ уже существует
		}
		else { // иначе создаЄм новую вершину
			TNode* newNode = new TNode(name, obj);
			newNode->color = Color::RED;
			newNode->pLeft = nil;
			newNode->pRight = nil;
			newNode->Parent = parent;

			if (name < parent->rc.key) {
				parent->pLeft = newNode;
			}
			else {
				parent->pRight = newNode;
			}
		}

		// тут будет балансировка (идЄм по стеку и что-то делаем)

		Fill++;
	}

	bool delete_rec(const T& name) override {
		if (isEmpty())
			return false;

		stack<TNode*> path;

		TNode* d = FindNodeToDelete(name, path);
		if (d == nil) // такого ключа нет
			return false;

		// тут надо помен€ть указатели и сделать балансировку

		Fill--;
		return true;
	}

	bool isEmpty() const override
	{
		return Fill == 0;
	}

	~RB_tree() override {
		DeleteTree(pRoot);
		delete nil;
	}
};

#endif
