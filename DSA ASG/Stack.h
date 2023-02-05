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
		//Constructor
		Stack();

		//Deconstructor
		~Stack();

		//Add a reply to the stack
		bool push(ItemType item);

		//Delete a reply from stack (Used for deconstructor)
		bool pop();

		//Get reply at top of stack
		ItemType* getTop();

		//Check for empty stack
		bool isEmpty();

		//Display replies in order
		void print();

		//Display replies in order of insertion
		void printBackwards();

		void printWithCounter();

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





