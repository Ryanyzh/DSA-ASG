/*

#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;

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

template <typename ItemType>
ItemType LinkedList<ItemType>::get(int index)
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
		cout << "The item is " << tempPointer->item.getContent() << "." << endl;
		tempPointer = tempPointer->next;
	}
}

template <typename ItemType>
ItemType LinkedList<ItemType>::search(string str)
{
	Node* current = FirstNode;
	return search(str, current);
}

template <typename ItemType>
ItemType LinkedList<ItemType>::search(string str, Node* nodePointer)
{
	if (nodePointer->item.retrieveString() == str) {
		return nodePointer->item;
	}
	else {
		search(str, nodePointer->next);
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
		searchIndex(str, nodePointer->next, index+1);
	}
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



*/
