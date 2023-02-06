//  +------------------------------------------------------------+
//  |                      Team 02: AWOL                         |
//  +------------------------------------------------------------+
//  |        Student 1: Yong Zong Han Ryan, S10219317A           |
//  |                                                            |
//  |        Student 2: Tan Jin Daat, S10222867E                 |
//  +------------------------------------------------------------+

#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename ItemType>

class LinkedList
{
	private:
		struct Node {
			ItemType item;
			Node* next;
		};
		Node* FirstNode;
		int size;

	public:
		// Constructor
		LinkedList();

		// Destructor
		~LinkedList();

		// Add an item to the back of the list
		bool add(ItemType item);

		// Add an item at a specified position in the list
		bool add(int index, ItemType item);

		// Remove an item at a specified position of the list
		void remove(int index);

		// Get an item at a specified position of the list
		ItemType* get(int index);

		// Get an item at a specified position of the list
		ItemType getItem(int index);

		// Check if the size of the list is empty
		bool isEmpty();

		// Check the size of the list
		int getLength();

		// Display all the items in the list
		void print();

		// Search the list with a string
		ItemType* search(string s);

		// Recusive search function for the above seach function
		ItemType* search(string s, Node* nodePointer);

		// Search and return the index pf item
		int searchIndex(string s);

		// Recursive search function for the above searchIndex function
		int searchIndex(string s, Node* nodePointer, int index);

		// Search the list with the item
		bool searchFound(ItemType i);

		// Display the contents of the list with index number
		void printWithCounter();
};


template <typename ItemType>
LinkedList<ItemType>::LinkedList()
{
	size = 0;
	FirstNode = NULL;
}

template <typename ItemType>
LinkedList<ItemType>::~LinkedList()
{

}

template <typename ItemType>
bool LinkedList<ItemType>::add(ItemType item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	Node* current = FirstNode;

	if (size == 0) {
		FirstNode = newNode;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	size++;
	return true;
}

template <typename ItemType>
bool LinkedList<ItemType>::add(int index, ItemType item)
{
	if (index <= size) {
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;

		if (index == 0) {
			newNode->next = FirstNode;
			FirstNode = newNode;
		}
		else {
			Node* current = FirstNode;
			for (index; index - 1 > 0; index--) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
		size++;
		return true;
	}
	else {
		return false;
	}
}

template <typename ItemType>
void LinkedList<ItemType>::remove(int index)
{
	if (index <= size) {

		if (index == 0) {
			Node* tempNode = FirstNode;
			FirstNode = FirstNode->next;

			// Set next pointer to null
			tempNode->next = NULL;
			// Deconstruct replies in the post obj
			tempNode->item.~Post();
			// Delete node which contains post obj
			delete tempNode;
			size--;
		}
		else {
			Node* current = FirstNode;
			for (int i = 0; i < index - 1; i++) {
				current = current->next;
			}
			Node* tempNode = current->next;
			current->next = current->next->next;

			// Set next pointer to null
			tempNode->next = NULL;
			// Deconstruct replies in the post obj
			tempNode->item.~Post();
			// Delete node which contains post obj
			delete tempNode;
			size--;
		}
	}
}

template <typename ItemType>
ItemType* LinkedList<ItemType>::get(int index)
{
	Node* current = new Node;
	current = FirstNode;
	int loop = index;
	while (current != NULL) {
		if (loop == 0) {
			return &current->item;
		}
		else {
			loop--;
			current = current->next;
		}
	}
	return nullptr;
}

template <typename ItemType>
ItemType LinkedList<ItemType>::getItem(int index)
{
	Node* current = new Node;
	current = FirstNode;
	int loop = index;
	while (current != NULL) {
		if (loop == 0) {
			return current->item;
		}
		else {
			loop--;
			current = current->next;
		}
	}
	return ItemType();
}

template <typename ItemType>
bool LinkedList<ItemType>::isEmpty()
{
	return size == 0;
}

template <typename ItemType>
int LinkedList<ItemType>::getLength()
{
	return size;
}

template <typename ItemType>
void LinkedList<ItemType>::print()
{
	Node* tempPointer;
	tempPointer = FirstNode;

	while (tempPointer != NULL) {
		tempPointer->item.print();
		tempPointer = tempPointer->next;
	}
}

template <typename ItemType>
void LinkedList<ItemType>::printWithCounter ()
{
	int counter = 1;
	Node* tempPointer;
	tempPointer = FirstNode;

	while (tempPointer != NULL) {
		tempPointer->item.print(counter++);
		tempPointer = tempPointer->next;
	}

	cout << endl;
}

template <typename ItemType>
ItemType* LinkedList<ItemType>::search(string str)
{
	Node* current = FirstNode;
	//return search(str, current);
	return search(str, current);
}

template <typename ItemType>
ItemType* LinkedList<ItemType>::search(string str, Node* nodePointer)
{
	if (!isEmpty()) {
		if (nodePointer->item.retrieveString() == str) {
			return &nodePointer->item;
		}
		else {
			if (nodePointer->next != NULL) {
				return search(str, nodePointer->next);
			}
			else {
				return nullptr;
			}
		}
	}
	else {
		return nullptr;
	}
	
}

template <typename ItemType>
int LinkedList<ItemType>::searchIndex(string str) {
	Node* current = FirstNode;
	int index = 0;
	return searchIndex(str, current, index);
}

template <typename ItemType>
int LinkedList<ItemType>::searchIndex(string str, Node* nodePointer, int index) {
	if (nodePointer->item.retrieveString() == str) {
		return index;
	}
	else {
		searchIndex(str, nodePointer->next, index + 1);
	}
	return 0;
}

template <typename ItemType>
bool LinkedList<ItemType>::searchFound(ItemType i) {
	Node* tempPointer;
	tempPointer = FirstNode;

	while (tempPointer != NULL) {
		if (tempPointer->item.equivalent(i)) {
			return true;
			break;
		}
		tempPointer = tempPointer->next;
	}
	return false;
}



