#pragma once
#include <iostream>

using namespace std;

const int MAX_SIZE = 5;

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
		ItemType* get(int index);

		// check if the list is empty
		bool isEmpty();

		// check the size of the list
		int getLength();

		void print();

		void replace(int index, ItemType item);

};



template <typename ItemType>
Array<ItemType>::Array() { size = 0; }

template <typename ItemType>
Array<ItemType>::~Array() {}

template <typename ItemType>
bool Array<ItemType>::add(ItemType item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

template <typename ItemType>
bool Array<ItemType>::add(int index, ItemType item)
{
	bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
	if (success)
	{  // make room for the item by shifting all items at
	   // positions >= index toward the end of the
	   // List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert the item
		items[index] = item;
		size++;  // increase the size by 1
	}
	return success;
}

template <typename ItemType>
void Array<ItemType>::remove(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
	{  // delete item by shifting all items at positions >
	   // index toward the beginning of the list
	   // (no shift if index == size)
		for (int pos = index; pos < size; pos++)
			items[pos] = items[pos + 1];
		size--;  // decrease the size by 1
	}

}

template <typename ItemType>
ItemType* Array<ItemType>::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return &items[index];
	else
		return nullptr;
}

template <typename ItemType>
bool Array<ItemType>::isEmpty() { return size == 0; }

template <typename ItemType>
int Array<ItemType>::getLength() { return size; }

template <typename ItemType>
void Array<ItemType>::print()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i].print();
	}
}

template <typename ItemType>
void Array<ItemType>::replace(int index, ItemType item)
{
	bool success = (index >= 0) && (index < size);
	if (success) {
		items[index] = item;
	}
}