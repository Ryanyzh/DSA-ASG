#include "Reaction.h"

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

void Reaction::print() {
	// Insert code here
}

