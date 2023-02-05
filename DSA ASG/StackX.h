#pragma once
#include <iostream>
#include <string.h>

using namespace std;

template <typename T>
class StackX
{
private:
	struct Node
	{
		T* item = nullptr;
		Node* next = nullptr;
	};

	Node* top = nullptr;

public:
	StackX(); // ok
	~StackX(); // ok
	bool push(T item);
	bool pop();
	bool isEmpty(); // ok

	T getTop(); // ?
	int getSize(); // ok

	void print();
	void printBackwards();
	void printWithCounter();
};

template <typename T>
StackX<T>::StackX() {
	top = nullptr;
}

template <typename T>
StackX<T>::~StackX() {
	while (!isEmpty()) {
		pop();
	}
}

template <typename T>
bool StackX<T>::isEmpty() {
	if (nullptr == top) // check if the object is nullptr
		return true;
	
	return false;
}

template <typename T>
int StackX<T>::getSize() {
	int counter = 0;
	Node* node = top;

	while (top)
		counter++;

	return counter;
}

template <typename T>
T StackX<T>::getTop() {
	return top->item; // a copy 
}

template <typename T>
bool StackX<T>::push(T item) {
	Node* node = new Node;
	node->item = *&item;
	node->next = top;

	top = node;

	return true;
}

template <typename T>
bool StackX<T>::pop() {
	if (!top)
		return false;

	Node* temp = top;
	top = top->next;
	
	temp->item = nullptr;
	temp->next = nullptr;
	delete temp;
	return true;
}

template <typename T>
void StackX<T>::print() {
	return;
}

template <typename T>
void StackX<T>::printBackwards() {
	return;
}

template <typename T>
void StackX<T>::printWithCounter() {
	return;
}