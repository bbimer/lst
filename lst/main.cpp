#include <iostream>
#include <string>

#include "List.h"

int main()
{
	std::cout << "Linked List" << std::endl << std::endl;

	List<std::string> list;
	list.AddToHead("one");
	list.AddToHead("two");
	list.AddToHead("three");
	list.AddToTail("four");
	list.print();
	std::cout << std::endl;

	list.DeleteFromHead();
	list.DeleteFromTail();
	list.print();
	std::cout << std::endl;

	list.DeleteFromHead();
	list.DeleteFromTail();
	list.print();
	std::cout << std::endl;

	list.AddToHead("one");
	list.AddToHead("two");
	list.AddToHead("three");
	list.print();
	std::cout << std::endl;

	Node<std::string>* nodePtr = list.find("two");
	if (nodePtr != nullptr)
	{
		nodePtr->value = "two + two";
	}
	list.print();
	std::cout << std::endl;

	nodePtr = list.find("two");
	if (nodePtr != nullptr)
	{
		nodePtr->value = "new value";
	}
	list.print();
	std::cout << std::endl;

	nodePtr = list.find("three");
	list.addAfter("four", nodePtr);
	nodePtr = list.findPrev("two + two");
	list.addAfter("two", nodePtr);
	list.print();
	std::cout << std::endl;

	nodePtr = list.findPrev("two + two");
	list.removeAfter(nodePtr);
	nodePtr = list.find("three");
	list.removeAfter(nodePtr);
	list.print();
	std::cout << std::endl;

	list.clear();
	list.print();
	std::cout << std::endl;

	list.AddToHead("ten");
	list.addAfter("twelve", (list.addAfter("eleven", list.head)));
	list.print();
	std::cout << std::endl;

	std::cout << std::endl;

	return 0;
}