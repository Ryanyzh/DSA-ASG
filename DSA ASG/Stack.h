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

class Stack
{
	private:
		struct Node
		{
			ItemType item;
			Node* next;
		};

		Node* topNode;


	public:
		// Constructor
		Stack();

		// Deconstructor
		~Stack();

		// Add an item to the front of the stack
		bool push(ItemType item);

		// Remove an item from the front of the stack (Used for deconstructor)
		bool pop();

		// Get the item at top of stack
		ItemType* getTop();

		// Check if stack is empty
		bool isEmpty();

		// Display the contents of the stack
		void print();

		// Display the contents of the stack in reverse order
		void printBackwards();

		// Display the contents of the stack with index number
		void printWithCounter();

		// Get the size of the stack
		int getSize();
};


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
ItemType* Stack<ItemType>::getTop() {
	if (!isEmpty()) {
		return topNode->item;
	}
	return ItemType();
}


//printInOrder
template <typename ItemType>
void Stack<ItemType>::print() {
	Node* currentNode = new Node;
	currentNode = topNode;
	do {
		currentNode->item.print();
		currentNode = currentNode->next;
	} while (currentNode != NULL);
}


//printInOrder but with Counter
template <typename ItemType>
void Stack<ItemType>::printWithCounter() {
	int counter = getSize();
	Node* currentNode = new Node;
	currentNode = topNode;
	do {
		currentNode->item.print(counter--);
		currentNode = currentNode->next;
	} while (currentNode != NULL);
}


//printInOrdderOfInsertion
template <typename ItemType>
void Stack<ItemType>::printBackwards() {
	Stack newStack;
	Node* current = new Node;
	current = topNode;
	while (current != NULL) {
		newStack.push(current->item);
		current = current->next;
	}
	newStack.printInOrder();
}


//get the size of the stack
template <typename ItemType>
int Stack<ItemType>::getSize() {
	int sizeCount = 0;
	Node* current = topNode;
	while (current != NULL) {
		sizeCount++;
		current = current->next;
		 
	}
	return sizeCount;
}





