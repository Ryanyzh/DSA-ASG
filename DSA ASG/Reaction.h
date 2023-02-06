//  +------------------------------------------------------------+
//  |                      Team 02: AWOL                         |
//  +------------------------------------------------------------+
//  |        Student 1: Yong Zong Han Ryan, S10219317A           |
//  |                                                            |
//  |        Student 2: Tan Jin Daat, S10222867E                 |
//  +------------------------------------------------------------+

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
		// Constructor
		Reaction();

		//Destructor
		~Reaction();

		//Reaction setters
		void setEmoji(string e);
		void setCount(int number);

		//Reaction getters
		int getEmojiCount();

		// Add reaction count by 1
		void addCount();

		// Display the contents of reactions
		void print();

		
};

