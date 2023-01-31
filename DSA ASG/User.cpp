#include "User.h"

#include <string>

using namespace std;

User::User() {
	username = "";
	password = "";
};

User::~User() {
	//idk
};

string User::getUsername() {
	return username;
};

string User::getPassword() {
	return password;
};

void User::setUsername(string u) {
	username = u;
};

void User::setPassword(string p) {
	password = p;
};


string User::retreiveDetails() {
	return getUsername();
}

bool User::equivalent(User anotherUser) {
	return (this->getUsername() == anotherUser.getUsername()) && (this->getPassword() == anotherUser.getPassword());
}

void User::print() {
	// ** TO BE EDITED BY RYAN **
	cout << getUsername() << endl;
}
