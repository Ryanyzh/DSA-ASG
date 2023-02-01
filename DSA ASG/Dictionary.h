#pragma once
#include <iostream>
#include <string>

using namespace std;

const int HT_MAX_SIZE = 31;
const int PRIME_CONST = 31;

template <typename KeyType, typename ItemType>

class Dictionary
{
	

	private:
		struct Node
		{
			KeyType key;
			ItemType item;
			Node* next; //or use hashnext;
		};

		Node* items[HT_MAX_SIZE];
		int size;

	public:
		//constructor
		Dictionary();

		//destructor
		~Dictionary();

		//get hash value from key
		int hash(KeyType key);

		//add a new item with the specified key in the Dictionary
		bool add(KeyType newKey, ItemType item);

		//remove an item with the specified key in the Dictionary
		void remove(KeyType key);

		//get an item with the specified key in the Dictionary
		ItemType get(KeyType key);

		//check if the Dictionary is empty
		bool isEmpty();

		//check the size of the Dictionary
		int getLength();

		//display the topics in the Dictionary
		void print();

		// ** TO BE CHANGED (parameter name)
		// ===================================================
		ItemType search(KeyType topicName);

		ItemType returnSearchOption(int topicNum);

		ItemType search(KeyType topicName, Node* topicNode);
		// ===================================================
};

