#pragma once

#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

template<typename T>
class List {
    struct Node {
        T value;
        Node* pNext;
        Node(const T& val, Node* next = nullptr) : value(val), pNext(next) {}
    };
    Node* pFirst;
    size_t sz;
    mutable Node* lastNode; // кэшированный узел
    mutable size_t lastIndex; // кэшированный индекс

    friend void swap(List& l, List& r) noexcept {
        using std::swap;
        swap(l.pFirst, r.pFirst);
        swap(l.sz, r.sz);
        swap(l.lastNode, r.lastNode);
        swap(l.lastIndex, r.lastIndex);
    }

    Node* ToPos(size_t pos) const {
        if (pos >= sz)
            throw out_of_range("Index out of range");

        if (lastNode && lastIndex <= pos) {
            for (; lastIndex < pos; ++lastIndex) {
                lastNode = lastNode->pNext;
            }
        }
        else {
            lastNode = pFirst;
            lastIndex = 0;
            for (; lastIndex < pos; ++lastIndex) {
                lastNode = lastNode->pNext;
            }
        }
        return lastNode;
    }

public:
    List() : pFirst(nullptr), sz(0), lastNode(nullptr), lastIndex(0) {}

    List(const vector<T>& v) : pFirst(nullptr), sz(0), lastNode(nullptr), lastIndex(0) {
        for (size_t i = v.size(); i > 0; i--) {
            PushFront(v[i - 1]);
        }
    }

    List(const List& list) : pFirst(nullptr), sz(list.sz), lastNode(nullptr), lastIndex(0) {
        if (list.pFirst == nullptr) return;
        pFirst = new Node(list.pFirst->value);
        Node* currentNew = pFirst;
        Node* currentOld = list.pFirst->pNext;
        while (currentOld != nullptr) {
            currentNew->pNext = new Node(currentOld->value);
            currentNew = currentNew->pNext;
            currentOld = currentOld->pNext;
        }
    }

    List(List&& list) noexcept : pFirst(nullptr), sz(0), lastNode(nullptr), lastIndex(0) {
        swap(*this, list);
    }

    List& operator=(const List& list) {
        if (this != &list) {
            List tmp(list);
            swap(*this, tmp);
        }
        return *this;
    }

    List& operator=(List&& list) noexcept {
        if (this != &list) {
            swap(*this, list);
        }
        return *this;
    }

    ~List() {
        Node* p;
        while (pFirst != nullptr) {
            p = pFirst;
            pFirst = pFirst->pNext;
            delete p;
        }
    }

    size_t size() const noexcept { return sz; }

    bool isEmpty() const noexcept { return sz == 0; }

    T& Front() noexcept {
        return pFirst->value;
    }

    const T& Front() const noexcept {
        return pFirst->value;
    }

    void PushFront(const T& val) {
        Node* node = new Node(val, pFirst);
        pFirst = node;
        sz++;
        lastNode = nullptr;
        lastIndex = 0;
    }

    void PopFront() noexcept {
        if (pFirst == nullptr) return;
        Node* p = pFirst;
        pFirst = pFirst->pNext;
        delete p;
        sz--;
        lastNode = nullptr;
        lastIndex = 0;
    }

    T& operator[] (size_t pos) {
        Node* p = ToPos(pos);
        return p->value;
    }

    const T& operator[] (size_t pos) const {
        Node* p = ToPos(pos);
        return p->value;
    }

    void PushAfter(size_t pos, const T& val) {
        Node* p = ToPos(pos);
        Node* pNew = new Node(val, p->pNext);
        p->pNext = pNew;
        sz++;
        lastNode = nullptr;
        lastIndex = 0;
    }

    void EraseAfter(size_t pos) {
        Node* p = ToPos(pos);
        if (p->pNext == nullptr) return;
        Node* pDel = p->pNext;
        p->pNext = pDel->pNext;
        delete pDel;
        sz--;
        lastNode = nullptr;
        lastIndex = 0;
    }
};
