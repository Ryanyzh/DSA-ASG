
#include "Array.h"
#include <iostream>
#include <string>

using namespace std;


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
ItemType Array<ItemType>::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return -1;
}

template <typename ItemType>
bool Array<ItemType>::isEmpty() { return size == 0; }

template <typename ItemType>
int Array<ItemType>::getLength() { return size; }

template <typename ItemType>
void Array<ItemType>::print()
{
	// ** TO BE EDITED BY RYAN **
	//for (int i; i < MAX_SIZE; i++) {
	//	cout << items[i] << endl;
	//}
}

template <typename ItemType>
void Array<ItemType>::replace(int index, ItemType item)
{
	bool success = (index >= 0) && (index < size);
	if (success) {
		items[index] = item;
	}
}