#pragma once
#include <iostream>

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
		//constructor
		LinkedList();

		//destrcutor
		~LinkedList();

		//add an item to the back of the list
		bool add(ItemType item);

		//add an item at a specified position in the list
		bool addwithPosition(int index, ItemType item);

		//remove an item at a specified position of the list
		void remove(int index);

		//get an item at a specified position of the list
		ItemType get(int index);

		//check if the size of the list is empty
		bool isEmpty();

		//check the size of the list
		int getLength();

		//display all the items in the list
		void print();
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
bool LinkedList<ItemType>::addwithPosition(int index, ItemType item)
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

