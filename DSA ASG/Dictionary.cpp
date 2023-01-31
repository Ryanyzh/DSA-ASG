/*

#include "Dictionary.h"

#include <string>

using namespace std;

TDictionary::TDictionary() {
	size = 0;
	for (int i = 0; i < HT_MAX_SIZE; i++) {
		items[i] = NULL;
	}
}

TDictionary::~TDictionary() {
	for (int i = 0; i < size; i++) {
		while (items[i] != NULL) {
			remove(items[i]->tkey);
		}
	}
}

int TDictionary::hash(KeyType key) { //use string or int
	//https://dev.to/muiz6/string-hashing-in-c-1np3
	size_t hashCode = 0;
	for (int i = 0; i < key.length(); i++) {
		hashCode += (key[i] * (int)pow(31, i)) % HT_MAX_SIZE;
	}
	return hashCode % HT_MAX_SIZE;
}


void output(string name, int spacing, int counter) {
	spacing = 64 - 5 - (int)name.length();
	if (counter < 10) {
		cout << "|   " << counter << "   |     " << name;
		for (int spaces = 0; spaces < spacing; spaces++) {
			cout << " ";
		}
		cout << "|" << endl;
		cout << "+------------------------------------------------------------------------+" << endl;
		counter++;
	}
	else {
		cout << "|  " << counter << "   |     " << name;
		for (int spaces = 0; spaces < spacing; spaces++) {
			cout << " ";
		}
		cout << "|" << endl;
		cout << "+------------------------------------------------------------------------+" << endl;
		counter++;
	}
}


bool TDictionary::add(KeyType newKey, ItemType newItem) {
	int index = hash(newKey);
	if (items[index] == NULL) {
		TNode* newNode = new TNode;
		newNode->tkey = newKey;
		newNode->titem = newItem;
		newNode->tnext = NULL;
		items[index] = newNode;
	}
	else {
		TNode* current = items[index];
		if (current->tkey == newKey) {
			cout << newKey << " already exists." << endl;
			return false;
		}
		while (current->tnext != NULL) {
			current = current->tnext;
			if (current->tkey == newKey) {
				cout << newKey << " already exists." << endl;
				return false;
			}
		}
		TNode* newNode2 = new TNode;
		newNode2->tkey = newKey;
		newNode2->titem = newItem;
		newNode2->tnext = NULL;
		current->tnext = newNode2;
	}
	size++;
	return true;
}

void TDictionary::remove(KeyType key) {
	int index = hash(key);
	if (items[index] != NULL) {
		TNode* removal = new TNode;
		TNode* current = new TNode;
		current = items[index];
		if (current->tkey == key) {
			items[index] = current->tnext;
			current->tnext = NULL;
			delete current;
		}
		else {
			while (current->tnext != NULL) {
				removal = current->tnext;
				if (removal->tkey == key) {
					current->tnext = removal->tnext;
					removal->tnext = NULL;
					delete removal;
				}
				else {
					current = current->tnext;
				}
			}
		}

	}
	size--;
}

TDictionary::ItemType TDictionary::get(KeyType key) {
	int index = hash(key);
	if (items[index] != NULL) {
		TNode* current = new TNode;
		current = items[index];
		while (current->tnext != NULL) {
			if (current->tkey == key) {
				return current->titem;
			}
			current = current->tnext;
		}
	}
	//need to return here?
	return ItemType();
}

bool TDictionary::isEmpty() { return size == 0; }

int TDictionary::getLength() { return size; }

void TDictionary::displayTopics() {
	int counter = 1;
	int spacing = 0;
	//cout << "\n\n" << endl;
	cout << "+------------------------------------------------------------------------+" << endl;
	cout << "| Topic |     Name                                                       |" << endl;
	cout << "+------------------------------------------------------------------------+" << endl;
	for (int i = 0; i < HT_MAX_SIZE; i++) {
		TNode* current = new TNode;
		current = items[i];
		if (current != NULL) {
			//output(current->titem.getTopicName(), spacing, counter);

			spacing = 64 - 5 - (int)current->titem.getTopicName().length();
			if (counter < 10) {
				cout << "|   " << counter << "   |     " << current->titem.getTopicName();
				for (int spaces = 0; spaces < spacing; spaces++) {
					cout << " ";
				}
				cout << "|" << endl;
				cout << "+------------------------------------------------------------------------+" << endl;
				counter++;
			}
			else {
				cout << "|  " << counter << "   |     " << current->titem.getTopicName();
				for (int spaces = 0; spaces < spacing; spaces++) {
					cout << " ";
				}
				cout << "|" << endl;
				cout << "+------------------------------------------------------------------------+" << endl;
				counter++;
			}


			//cout << current->tkey << " : " << current->titem.getTopicName() << endl;
			while (current->tnext != NULL) {
				//output(current->titem.getTopicName(), spacing, counter);

				spacing = 64 - 5 - (int)current->titem.getTopicName().length();
				if (counter < 10) {
					cout << "|   " << counter << "   |     " << current->titem.getTopicName();
					for (int spaces = 0; spaces < spacing; spaces++) {
						cout << " ";
					}
					cout << "|" << endl;
					cout << "+------------------------------------------------------------------------+" << endl;
					counter++;
				}
				else {
					cout << "|  " << counter << "   |     " << current->titem.getTopicName();
					for (int spaces = 0; spaces < spacing; spaces++) {
						cout << " ";
					}
					cout << "|" << endl;
					cout << "+------------------------------------------------------------------------+" << endl;
					counter++;
				}




				//cout << current->tnext->tkey << " : " << current->tnext->titem.getTopicName() << endl;
				current = current->tnext;
			}
		}
	}
	cout << "\n\n" << endl;
}

string TDictionary::returnTopicName(int topicNum) {
	int skip = topicNum - 1;
	for (int i = 0; i < HT_MAX_SIZE; i++) {
		TNode* current = new TNode;
		current = items[i];
		if (current != NULL) {
			if (skip != 0) {
				skip--;
			}
			else {
				return current->titem.getTopicName();
			}


			//cout << current->tkey << " : " << current->titem.getTopicName() << endl;
			while (current->tnext != NULL) {
				if (skip != 0) {
					skip--;
				}
				else {
					return current->titem.getTopicName();
				}
				current = current->tnext;
			}
		}
	}
}

// Function to serch topic by name
Topic TDictionary::searchTopic(string topicName) {
	TNode* current = items[hash(topicName)];
	return searchTopic(topicName, current);
}

// Recusrive search function
Topic TDictionary::searchTopic(string topicName, TNode* topicNode) {
	if (topicNode->titem.getTopicName() == topicName) {
		return topicNode->titem;
	}
	else {
		searchTopic(topicName, topicNode->tnext);
	}
}





*/