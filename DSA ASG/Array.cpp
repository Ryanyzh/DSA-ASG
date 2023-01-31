/*
#include "Array.h"
// constructor
ReactionList::ReactionList() { size = 0; }

// add an item to the back of the list 
bool ReactionList::add(ItemType item)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = item;    // add to the end of the list
		size++;                // increase the size by 1
	}
	return success;
}

// add an item at a specified position in the list 
bool ReactionList::add(int index, ItemType item)
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

// remove an item at a specified position in the list
void ReactionList::remove(int index)
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

// get an item at a specified position of the list (retrieve)
ReactionList::ItemType ReactionList::get(int index)
{
	bool success = (index >= 0) && (index < size);
	if (success)
		return items[index];
	else
		return -1;
}

// check if the list is empty
bool ReactionList::isEmpty() { return size == 0; }

// check the size of the list
int ReactionList::getLength() { return size; }

// display the items in the list
void ReactionList::print()
{

}

// replace the  item in the specified index in the list
void ReactionList::replace(int index, ItemType item)
{
	bool success = (index >= 0) && (index < size);
	if (success) {
		items[index] = item;
	}
}
*/
