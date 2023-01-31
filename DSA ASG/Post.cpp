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
	string current_time = ss.str(); //2023-01-30 18:40:00
	Pdatetime = current_time;
};

void Post::setPTitle(string pt) {
	Ptitle = pt;
};

void Post::setPContent(string pc) {
	Pcontent = pc;
};

bool Post::addReply(Reply reply) {
	return replyStack.push(reply);
}
