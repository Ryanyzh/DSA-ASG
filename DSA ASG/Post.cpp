#pragma warning(disable : 4996) //disbale deprication warning

#include "Post.h"
#include <string>
#include <iostream>
//for getting the datetime result
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

Post::Post() {
	Ptitle = "";
	Pcontent = "";
	Pdatetime = "";
	user = User();  
	replyStack = Stack<Reply>();
	reactions = Array<Reaction>();
};

Post::~Post() {
	// Deconstruct replyStack
	replyStack.~Stack<Reply>();
};

string Post::retrieveString() {
	return getPTitle();
}

Array<Reaction> Post::getReactions() {
	return reactions;
}

User Post::getPUser() {
	return user;
}

string Post::getPTitle() {
	return Ptitle;
};

string Post::getPContent() {
	return Pcontent;
};

string Post::getPDateTime() {
	return Pdatetime;
}

Stack<Reply> Post::getRStack() {
	return replyStack;
}

void Post::setPDateTime() {
	auto nowtime = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(nowtime);
	stringstream ss;
	ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
	string current_time = ss.str(); //2023-01-30 18:40:00 = 19 spaces
	Pdatetime = current_time;
};

void Post::setPTitle(string pt) {
	Ptitle = pt;
};

void Post::setPContent(string pc) {
	Pcontent = pc;
};

void Post::setPUser(User u) {
	user = u;
}

bool Post::addReply(Reply reply) {
	return replyStack.push(reply);
}

void Post::updateReaction(int i) {
	reactions.get(i - 1).addCount();
}

bool Post::equivalent(Post anotherPost) {
	return (this->getPTitle() == anotherPost.getPContent());
}

void Post::print() {
	cout << "Rizz 2" << endl;
	//?________________________________________________________________________?
	//|                                                                        |
	//|  # Post 1                                                              |
	//|                                                                        |
	//|  Name: 	       John Cena                          ????-??-?? ??-??-??  |
	//|                                                                        |
	//|  Title:        Your ---                                                |
	//|  Decription:   Your --- --- Your --- --- Your --- --- Your --- --- Yo  |
	//|                Your --- --- Your --- --- Your --- --- Your --- --- Yo  |
	//|                                                                        |
	//|  Reactions:    1 - 999    2 - 999    33 - 999    44 - 999    55 - 999  |
	//|                                                                        |
	//?________________________________________________________________________?
	// ** TO BE EDITED BY RYAN **
	cout << this->getPTitle() << endl;
	cout << this->getPContent() << endl;
	cout << this->getPDateTime() << endl;
	//this->getRStack().printInOrder();
	//this->getReactions().print();
	//cout << this->getPUser().getUsername() << endl;
}
