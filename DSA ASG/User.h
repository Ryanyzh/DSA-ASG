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
		User();
		~User();
		string getUsername();
		string getPassword();
		void setUsername(string);
		void setPassword(string);
		string retrieveString();
		bool equivalent(User u);

		void print();
		//void displayUserDetails();
};

