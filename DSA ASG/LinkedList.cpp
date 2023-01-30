/*
#include "LinkedList.h"
#include <string>
#include <iostream>

using namespace std;

// constructor
LinkedList::LinkedList() { size = 0; FirstNode = NULL; }

// destructor
LinkedList::~LinkedList()
{
}



// add an item to the back of the list
bool LinkedList::add(ItemType item)
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

// add an item at a specified position in the list
bool LinkedList::add(int index, ItemType item)
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

// remove an item at a specified position in the list
void LinkedList::remove(int index)
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
		}
	}

}

// get an item at a specified position of the list
LinkedList::ItemType LinkedList::get(int index)
{
	Node* current = new Node;
	if (index <= size) {
		for (index; index > 0; index--) {
			current = current->next;
		}
		return current->item;
	}
	else {
		return ItemType();
	}

}

// check if the list is empty
bool LinkedList::isEmpty() { return size == 0; }

// check the size of the list
int LinkedList::getLength() { return size; }

// display the items in the list
void LinkedList::print()
{
	Node* tempPointer;
	tempPointer = FirstNode;

	while (tempPointer != NULL) {
		cout << "The item is " << tempPointer->item.getContent() << "." << endl;
		tempPointer = tempPointer->next;
	}
}

*/

