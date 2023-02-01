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
		ItemType getTop();

		//Check for empty stack
		bool isEmpty();

		//Display replies in order
		void printInOrder();

		//Display replies in order of insertion
		void printInOrderOfInsertion();

};


