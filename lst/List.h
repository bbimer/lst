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
	Node* down;

	Node(const T& value) : value(value), next(nullptr), down(nullptr) {}

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
	int size;


	List() : head(nullptr), size(0) {}

	void add(const T& value)
	{
		Node<T>* nodePtr = new Node<T>(value);
		nodePtr->next = head;
		head = nodePtr;
		++size;
	}
	// head ->[10 | next -> nullptr]
	// nodePtr ->[20 | next -> nullptr]
	// nodePtr ->[20 | next ->[10 | next -> nullptr]]
	// head ->[20 | next ->[10 | next -> nullptr]]


	void remove()
	{
		if (head != nullptr)
		{
			Node<T>* nodePtr = head;
			head = head->next;
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
			remove();
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