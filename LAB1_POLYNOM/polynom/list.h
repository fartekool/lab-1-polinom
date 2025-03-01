#ifndef LIST_H
#define LIST_H

using namespace std;

template<class T>//тут потом эксепшены адекватные надо сделать будет
class List
{
	struct Node
	{
		T data;
		Node* pNext = nullptr;
	};
	Node* pFirst, * pLast;
	size_t sz;
public:
	List() :pFirst(nullptr), pLast(nullptr), sz(0) {}

	List(const List& to_copy) :sz(to_copy.sz), pFirst(nullptr), pLast(nullptr)
	{
		if (!to_copy.pFirst)
			return;
		pFirst = new Node{ to_copy.pFirst->data };
		Node* p = to_copy.pFirst->pNext;
		Node* current = pFirst;
		while (p)
		{
			current->pNext = new Node{ p->data };
			current = current->pNext;
			p = p->pNext;
		}
		pLast = current;
	}

	~List()
	{
		Node* p = pFirst;
		while (p)
		{
			pFirst = pFirst->pNext;
			delete p;
			p = pFirst;
		}
	}

	size_t get_size() const noexcept
	{
		return sz;
	}

	bool is_empty() const noexcept
	{
		return sz == 0;
	}

	void push_back(const T& elem)
	{
		Node* to_push = new Node{ elem };
		if (!pFirst)
		{
			pFirst = pLast = to_push;
			sz++;
			return;
		}
		pLast->pNext = to_push;
		pLast = to_push;
		sz++;
	}

	void erase(size_t pos)
	{
		if (is_empty())
			throw "list is empty!";
		if (pos >= sz)
			throw "Incorrect list's elem position!";
		Node* p = pFirst;
		if (pos == 0)
		{
			pFirst = pFirst->pNext;
			delete p;
			sz--;
			return;
		}
		for (size_t i = 0; i != pos - 1; p = p->pNext, i++);
		Node* to_del = p->pNext;
		p->pNext = p->pNext->pNext;
		delete to_del;
		sz--;
	}

	T& operator[](size_t index)
	{
		if (is_empty())
			throw "list is empty!";
		if (index >= sz)
			throw "Incorrect list's elem position!";
		Node* p = pFirst;
		for (size_t i = 0; i != index; i++, p = p->pNext);
		return p->data;
	}

	const T& operator[](size_t index) const
	{
		if (is_empty())
			throw "list is empty!";
		if (index >= sz)
			throw "Incorrect list's elem position!";
		Node* p = pFirst;
		for (size_t i = 0; i != index; i++, p = p->pNext);
		return p->data;
	}

	bool operator==(const List& compare)  const
	{
		if (this == &compare)
			return true;
		if (sz != compare.sz)
			return false;
		Node* leftCur = pFirst, * rightCur = compare.pFirst;
		while (leftCur)
		{
			if (leftCur->data != rightCur->data)
				return false;
			leftCur = leftCur->pNext;
			rightCur = rightCur->pNext;
		}
		return true;
	}

	bool operator!=(const List& compare)
	{
		return !(operator==(compare));
	}

	List& operator = (const List& other)
	{
		if (*this == other)
			return *this;
		List tmp(other);
		swap(sz, tmp.sz);
		swap(pFirst, tmp.pFirst);
		swap(pLast, tmp.pLast);
		return *this;
	}
};

#endif 

