#pragma warning(disable : 4996) //disbale deprication warning

#include "Reply.h"
#include <string>
#include <iostream>
//for getting the datetime result
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

Reply::Reply() {
	Rtitle = "";
	Rcontent = "";
	Rdatetime = { nullptr };
	//user = NULL;  HOW TO SET THE USER TO NULL?
};

Reply::~Reply() {
	//idk
};

string Reply::getRTitle() {
	return Rtitle;
};

string Reply::getRContent() {
	return Rcontent;
};

string Reply::getRDateTime() {
	return Rdatetime;
}

void Reply::setRDateTime() {
	auto nowtime = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(nowtime);
	stringstream ss;
	ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
	string current_time = ss.str(); //2023-01-30 18:40:00
	Rdatetime = current_time;
};

void Reply::setRTitle(string rt) {
	Rtitle = rt;
};

void Reply::setRContent(string rc) {
	Rcontent = rc;
};
