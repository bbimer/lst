#include <iostream>
#include <string>

#include "List.h"

int main()
{
	std::cout << "Linked List" << std::endl << std::endl;

	List<std::string> list;
	list.add("one");
	list.add("two");
	list.add("three");
	list.print();
	std::cout << std::endl;

	list.remove();
	list.remove();
	list.print();
	std::cout << std::endl;

	list.remove();
	list.remove();
	list.print();
	std::cout << std::endl;

	list.add("one");
	list.add("two");
	list.add("three");
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

	list.add("ten");
	list.addAfter("twelve", (list.addAfter("eleven", list.head)));
	list.print();
	std::cout << std::endl;

	std::cout << std::endl;

	return 0;
}