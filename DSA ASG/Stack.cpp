
/*
#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;


template <typename ItemType>
Stack<ItemType>::Stack() {
	topNode = NULL;
};

template <typename ItemType>
Stack<ItemType>::~Stack() {
	while (!isEmpty()) {
		pop();
	}
}

template <typename ItemType>
bool Stack<ItemType>::isEmpty() {
	if (topNode == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template <typename ItemType>
bool Stack<ItemType>::push(ItemType item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	newNode->next = topNode; //set new node's pointer to point to node pointed to by topNode
	topNode = newNode; //set topNode(pointer) to point to new Node

	return true;
}

template <typename ItemType>
bool Stack<ItemType>::pop() {
	if (!isEmpty()) {
		Node* tempNode = topNode;
		topNode = topNode->next;
		tempNode->next = NULL;
		delete tempNode;
		return true;
	}
	return false;
}

template <typename ItemType>
ItemType Stack<ItemType>::getTop() {
	if (!isEmpty()) {
		return topNode->item;
	}
	return ItemType();
}

template <typename ItemType>
void Stack<ItemType>::printInOrder() {
	Node* currentNode = new Node;
	currentNode = topNode;
	do {
		cout << "Item is: " << currentNode->item.getRContent() << endl;
		currentNode = currentNode->next;
	} while (currentNode != NULL);
}

template <typename ItemType>
void Stack<ItemType>::printInOrderOfInsertion() {
	Stack newStack;
	Node* current = new Node;
	current = topNode;
	while (current != NULL) {
		newStack.push(current->item);
		current = current->next;
	}
	newStack.printInOrder();
}
*/

