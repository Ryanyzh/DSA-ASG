#pragma once
#include <iostream>
#include <string>

using namespace std;

class Reaction
{
	private:
		string reactionEmoji;
		int reactionCount;

	public:
		//PLinkedList::PNode* postPointer;
		Reaction();
		~Reaction();

		//Topic Setter 
		void setEmoji(string e);

		//Topic getter
		int getEmojiCount();

		void addCount();

		void print();
};

