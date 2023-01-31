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
		void setEmoji(string e, int c);

		//Topic getter
		int getEmoji(string e);

		//Display topic details?
		void print();
};

