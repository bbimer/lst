#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

template <typename T>
class Node
{
public:
	T value;
	Node* next;
	Node* prev;

	Node(const T& value) : value(value), next(nullptr), prev(nullptr) {}

	void print() const
	{
		std::cout << value;
	}
};

template <typename T>
class List
{
public:
	Node<T>* head;
	Node<T>* tail;
	int size;


	List() : head(nullptr), tail(nullptr), size(0) {}

	~List() { clear(); }

	void AddToHead(const T& value)
	{
		Node<T>* nodePtr = new Node<T>(value);
		if (head == nullptr) {
			head = tail = nodePtr;
		}
		else {
			nodePtr->next = head;
			head->prev = nodePtr;
			head = nodePtr;
		}
		++size;
	}
	
	void AddToTail(const T& value)
	{
		Node<T>* nodePtr = new Node<T>(value);
		if (head == nullptr) {
			head = tail = nodePtr;
		}
		else {
			tail->next = nodePtr;
			nodePtr->prev = tail;
			tail = nodePtr;
		}
		++size;
	}


	void DeleteFromHead()
	{
		if (head != nullptr)
		{
			Node<T>* nodePtr = head;
			head = head->next;
			if (head != nullptr) {
				head->prev = nullptr;
			}
			else {
				tail = nullptr;
			}
			delete nodePtr;
			--size;
		}
	}

	void DeleteFromTail()
	{
		if (tail != nullptr)
		{
			Node<T>* nodePtr = tail;
			tail = tail->prev;
			if (tail != nullptr) {
				tail->next = nullptr;
			}
			else {
				head = nullptr;
			}
			delete nodePtr;
			--size;
		}
	}

	Node<T>* find(const T& value) const
	{
		for (Node<T>* nodePtr = head;
			nodePtr != nullptr;
			nodePtr = nodePtr->next)
		{
			if (nodePtr->value == value)
			{
				return nodePtr;
			}
		}
		return nullptr;
	}

	Node<T>* findPrev(const T& value) const
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		for (Node<T>* nodePtr = head->next, *prevPtr = head;
			nodePtr != nullptr;
			nodePtr = nodePtr->next, prevPtr = prevPtr->next)
		{
			if (nodePtr->value == value)
			{
				return prevPtr;
			}
		}
		return nullptr;
	}

	Node<T>* addAfter(const T& value, Node<T>* afterPtr)
	{
		if (afterPtr == nullptr)
		{
			return nullptr;
		}
		Node<T>* nodePtr = new Node<T>(value);
		nodePtr->next = afterPtr->next;
		afterPtr->next = nodePtr;
		++size;
		return afterPtr->next;
	}

	Node<T>* removeAfter(Node<T>* afterPtr)
	{
		if (afterPtr != nullptr && afterPtr->next != nullptr)
		{
			Node<T>* nodePtr = afterPtr->next;
			afterPtr->next = afterPtr->next->next;
			delete nodePtr;
			--size;
		}
		return afterPtr;
	}

	void clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
		size = 0;
	}

	void doForEach(void(*func)(Node<T>* nodePtr))
	{
		for (Node<T>* nodePtr = head; nodePtr != nullptr; nodePtr = nodePtr->next)
		{
			func(nodePtr);
		}
	}

	static void printNode(Node<T>* nodePtr)
	{
		nodePtr->print();
		std::cout << " > ";
	}

	void print()
	{
		std::cout << " > ";
		doForEach(printNode);
		std::cout << std::endl;
	}
};

#endif