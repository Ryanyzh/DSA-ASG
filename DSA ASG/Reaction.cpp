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

int Reaction::getEmoji(string emoji) {
	return reactionCount;
};

void Reaction::setEmoji(string emoji, int counter) {
	reactionEmoji = emoji;
	reactionCount = counter;
};

void Reaction::addCount() {
	reactionCount++;
}

void Reaction::print() {
	// Insert code here
}

