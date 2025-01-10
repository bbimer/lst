#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

template <typename T>
class Node
{
public:
	T value;
	Node<T>* next;
	Node<T>* prev;

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

	~List() { DeleteAll(); }

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

	void DeleteAll()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
		size = 0;
	}

	void DeleteByIdx(int index) {
		if (index < 0 || index >= size) {
			std::cerr << "Index out of range.\n";
			return;
		}

		Node<T>* current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}

		if (current == head) {
			DeleteFromHead();
			return;
		}

		if (current == tail) {
			DeleteFromTail();
			return;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;

		delete current;
		--size;
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

	int findPosition(const T& value) const
	{
		int position = 0; 
		for (Node<T>* nodePtr = head; nodePtr != nullptr; nodePtr = nodePtr->next, ++position)
		{
			if (nodePtr->value == value)
			{
				return position; 
			}
		}
		return -1;
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
		if (afterPtr->next != nullptr)
		{
			afterPtr->next->prev = nodePtr;
		}
		afterPtr->next = nodePtr;
		nodePtr->prev = afterPtr;
		if (afterPtr == tail)
		{
			tail = nodePtr;
		}
		++size;
		return nodePtr;
	}


	Node<T>* addByIdx(const T& value, int index) {
		if (index < 0 || index >= size)
			return nullptr;

		Node<T>* current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}

		Node<T>* nodePtr = new Node<T>(value);
		nodePtr->next = current->next;
		if (current->next != nullptr) {
			current->next->prev = nodePtr;
		}

		current->next = nodePtr;
		nodePtr->prev = current;

		if (current == tail)
		{
			tail = nodePtr;
		}

		++size;
		return nodePtr;
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

	void Show()
	{
		std::cout << " > ";
		doForEach(printNode);
		std::cout << std::endl;
	}


};

#endif