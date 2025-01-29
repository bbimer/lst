#include <iostream>
#include <string>

#include "List.h"

int main()
{
	std::cout << "Linked List" << std::endl << std::endl;

	List<std::string> list;
	/*list.AddToHead("one");
	list.AddToHead("two");
	list.AddToHead("three");
	list.AddToTail("four");
	list.Show();
	std::cout << std::endl;

	list.DeleteFromHead();
	list.DeleteFromTail();
	list.Show();
	std::cout << std::endl;

	list.DeleteFromHead();
	list.DeleteFromTail();
	list.Show();
	std::cout << std::endl;*/

	list.AddToHead("one");
	list.AddToHead("two");
	list.AddToHead("three");
	list.Show();
	std::cout << std::endl;

	Node<std::string>* nodePtr = list.find("two");
	if (nodePtr != nullptr)
	{
		nodePtr->value = "two + two";
	}
	list.Show();
	std::cout << std::endl;

	nodePtr = list.find("one");
	if (nodePtr != nullptr)
	{
		nodePtr->value = "new value";
	}
	list.Show();
	std::cout << std::endl;

	nodePtr = list.find("three");
	list.addAfter("four", nodePtr);
	nodePtr = list.findPrev("two + two");
	list.addAfter("two", nodePtr);
	list.Show();
	std::cout << std::endl;
	std::cout << "find position: " << list.findPosition("two") << std::endl;
	std::cout << "find position: " << list.findPosition("five") << std::endl;
	
	std::cout << std::endl << std::endl;
	list.addByIdx("new_element", 4);
	list.Show();
	list.reverse();
	list.Show();

	/*nodePtr = list.findPrev("two + two");
	list.removeAfter(nodePtr);
	nodePtr = list.find("three");
	list.removeAfter(nodePtr);
	list.Show();
	std::cout << std::endl;

	list.DeleteAll();
	list.Show();
	std::cout << std::endl;

	list.AddToHead("ten");
	list.addAfter("twelve", (list.addAfter("eleven", list.head)));
	nodePtr = list.find("ten");
	if (nodePtr != nullptr) {
		list.addAfter("one", nodePtr);
	}
	list.Show();
	std::cout << std::endl;

	std::cout << std::endl;*/

	return 0;
}