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
		try
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
		catch (const std::exception&)
		{
			throw std::runtime_error("AddToHead: memory allocation error");
		}
	}

	
	void AddToTail(const T& value)
	{
		try
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
		catch (const std::exception&)
		{
			throw std::runtime_error("AddToTail: memory allocation error");
		}
	}


	void DeleteFromHead()
	{
		if (head == nullptr)
			throw std::runtime_error("DeleteFromHead: attempt to delete from an empty list");

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

	void DeleteFromTail()
	{
		if (tail == nullptr)
			throw std::runtime_error("DeleteFromTail: attempt to delete from an empty list");

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

	void DeleteAll()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
		size = 0;
	}

	void DeleteByIdx(int index) {
		if (index < 0 || index >= size)
			throw std::out_of_range("DeleteByIdx: index out of range");

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
			throw std::invalid_argument("addAfter: Invalid node pointer");
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
			throw std::out_of_range("addByIdx: index out of range");

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

	void reverse() {
		if (!head || !head->next) return;

		Node<T>* current = head;
		Node<T>* temp = nullptr;
		 
		while (current) {
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;
			current = current->prev;
		}

		temp = head;
		head = tail;
		tail = temp;
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