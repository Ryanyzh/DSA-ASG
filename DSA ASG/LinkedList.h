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
		//constructor
		LinkedList();

		//destrcutor
		~LinkedList();

		//add an item to the back of the list
		bool add(ItemType item);

		//add an item at a specified position in the list
		bool add(int index, ItemType item);

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

		//search and return an object
		ItemType search(string s);

		//recusive search function for the above
		ItemType search(string s, Node* nodePointer);

		//search and return a index of object
		int searchIndex(string s);

		//recursive search function for the above
		int searchIndex(string s, Node* nodePointer, int index);

		//boolean to check if item is found
		bool searchFound(ItemType i);
};



