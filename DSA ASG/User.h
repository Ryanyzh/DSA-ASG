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

class User
{
	private:
		string username;
		string password;

	public:

		// Constructor
		User();

		// Destrcutor
		~User();

		// User getters
		string getUsername();
		string getPassword();

		// User setters
		void setUsername(string);
		void setPassword(string);

		// Get the username of the user
		string retrieveString();

		// Check if both User objects matches
		bool equivalent(User u);

		// Display the contents of the user 
		void print();
};

