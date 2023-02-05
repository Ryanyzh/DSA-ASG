#include "Reaction.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

Reaction::Reaction() {
	reactionEmoji = "";
	reactionCount = 0;
};

Reaction::~Reaction() {
	//idk
};

int Reaction::getEmojiCount() {
	return reactionCount;
};

void Reaction::setEmoji(string emoji) {
	reactionEmoji = emoji;
	reactionCount = 0;
};

void Reaction::addCount() {
	reactionCount = reactionCount + 1;
}

void Reaction::print() {
	if (reactionEmoji == ":0") {
		cout << reactionEmoji << " - " << setw(3) << setfill('0') << reactionCount << "  ";
	}
	else {
		cout << reactionEmoji << " - " << setw(3) << setfill('0') << reactionCount << "    ";
	}
	
}

