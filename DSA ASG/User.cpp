#include "User.h"

#include <iostream>
#include <string>

using namespace std;

User::User() {
	username = "";
	password = "";
};

User::~User() {};



string User::getUsername() { return username; };
string User::getPassword() { return password; };
string User::retrieveString() { return getUsername(); }



void User::setUsername(string u) { username = u; };
void User::setPassword(string p) { password = p; };



bool User::equivalent(User anotherUser) {
	return (this->getUsername() == anotherUser.getUsername()) && (this->getPassword() == anotherUser.getPassword());
}



