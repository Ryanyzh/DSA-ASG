
/*
#include "Dictionary.h"
#include <iostream>
#include <string>

using namespace std;


template <typename KeyType, typename ItemType>
Dictionary<KeyType, ItemType>::Dictionary() {
	size = 0;
	for (int i = 0; i < HT_MAX_SIZE; i++) {
		items[i] = NULL;
	}
}


template <typename KeyType, typename ItemType>
Dictionary<KeyType, ItemType>::~Dictionary() {
	for (int i = 0; i < size; i++) {
		while (items[i] != NULL) {
			remove(items[i]->key);
		}
	}
}


template <typename KeyType, typename ItemType>
int Dictionary<KeyType, ItemType>::hash(KeyType key) { //use string or int
	// https://dev.to/muiz6/string-hashing-in-c-1np3
	size_t hashCode = 0;
	for (int i = 0; i < (int)key.length(); i++) {
		hashCode += (key[i] * (int)pow(31, i)) % HT_MAX_SIZE;
	}
	return hashCode % HT_MAX_SIZE;
}


template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::add(KeyType newKey, ItemType newItem) {
	int index = hash(newKey);
	if (items[index] == NULL) {
		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;
		newNode->next = NULL;
		items[index] = newNode;
	}
	else {
		Node* current = items[index];
		if (current->key == newKey) {
			cout << newKey << " already exists." << endl;
			return false;
		}
		while (current->next != NULL) {
			current = current->next;
			if (current->key == newKey) {
				cout << newKey << " already exists." << endl;
				return false;
			}
		}
		Node* newNode2 = new Node;
		newNode2->key = newKey;
		newNode2->item = newItem;
		newNode2->next = NULL;
		current->next = newNode2;
	}
	size++;
	return true;
}


template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::remove(KeyType key) {
	int index = hash(key);
	if (items[index] != NULL) {
		Node* removal = new Node;
		Node* current = new Node;
		current = items[index];
		if (current->key == key) {
			items[index] = current->next;
			current->next = NULL;
			delete current;
		}
		else {
			while (current->next != NULL) {
				removal = current->next;
				if (removal->key == key) {
					current->next = removal->next;
					removal->next = NULL;
					delete removal;
				}
				else {
					current = current->next;
				}
			}
		}

	}
	size--;
}


template <typename KeyType, typename ItemType>
ItemType Dictionary<KeyType, ItemType>::get(KeyType key) {
	int index = hash(key);
	if (items[index] != NULL) {
		Node* current = new Node;
		current = items[index];
		while (current->next != NULL) {
			if (current->key == key) {
				return current->item;
			}
			current = current->next;
		}
	}
	//need to return here?
	return ItemType();
}


template <typename KeyType, typename ItemType>
bool Dictionary<KeyType, ItemType>::isEmpty()
{
	return size == 0;
}


template <typename KeyType, typename ItemType>
int Dictionary<KeyType, ItemType>::getLength()
{
	return size;
}


template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::print() {
	int counter = 1;
	if (!isEmpty()) {
		for (int i = 0; i < HT_MAX_SIZE; i++) {
			Node* current = new Node;
			current = items[i];
			if (current != NULL) {
				current->item.print(current->item, counter++);

				while (current->next != NULL) {
					current->item.print(current->item, counter++);
					current = current->next;
				}
			}
		}
	}
	else {
		cout << "There is nothing to display.";
	}

	cout << "\n" << endl;
}


template <typename KeyType, typename ItemType>
ItemType Dictionary<KeyType, ItemType>::returnSearchOption(int topicNum) {
	int skip = topicNum - 1;
	for (int i = 0; i < HT_MAX_SIZE; i++) {
		Node* current = new Node;
		current = items[i];
		if (current != NULL) {
			if (skip != 0) {
				skip--;
			}
			else {
				return current->item;
			}
			//cout << current->key << " : " << current->item.getTopicName() << endl;
			while (current->next != NULL) {
				if (skip != 0) {
					skip--;
				}
				else {
					return current->item;
				}
				current = current->next;
			}
		}
	}
}


// Function to serch topic by name
template <typename KeyType, typename ItemType>
ItemType Dictionary<KeyType, ItemType>::search(KeyType str) {
	Node* current = items[hash(str)];
	return search(str, current);
}


// Recusrive search function
template <typename KeyType, typename ItemType>
ItemType Dictionary<KeyType, ItemType>::search(KeyType str, Node* nextNode) {
	if (nextNode->item.getTopicName() == str) {
		return nextNode->item;
	}
	else {
		search(str, nextNode->next);
	}
}
*/


