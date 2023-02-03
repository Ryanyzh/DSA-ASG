#include "Reaction.h"
#include <iostream>
#include <string>

using namespace std;

Reaction::Reaction() {
	reactionEmoji = "";
	reactionCount = 0;
};

Reaction::~Reaction() {
	//idk
};

int Reaction::getEmojiCount(string emoji) {
	return reactionCount;
};

void Reaction::setEmoji(string emoji) {
	reactionEmoji = emoji;
	reactionCount = 0;
};

void Reaction::addCount() {
	reactionCount++;
}

void Reaction::print() {
	cout << reactionEmoji << "   :   " << reactionCount << endl;
}

