#pragma once
#include <iostream>

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
		ItemType getTop();

		//Check for empty stack
		bool isEmpty();

		//Display replies in order
		void printInOrder();

		//Display replies in order of insertion
		void printInOrderOfInsertion();

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


