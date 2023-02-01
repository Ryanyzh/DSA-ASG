#pragma once
#include <iostream>

using namespace std;

const int MAX_SIZE = 6;

template <typename ItemType>

class Array
{
	private:
		ItemType items[MAX_SIZE];
		int      size;

	public:

		// constructor
		Array();

		// destructor
		~Array();

		// add an item to the back of the list (append)
		bool add(ItemType item);

		// add an item at a specified position in the list (insert)
		bool add(int index, ItemType item);

		// remove an item at a specified position in the list
		void remove(int index);

		// get an item at a specified position of the list (retrieve)
		ItemType get(int index);

		// check if the list is empty
		bool isEmpty();

		// check the size of the list
		int getLength();

		void print();

		void replace(int index, ItemType item);
};



