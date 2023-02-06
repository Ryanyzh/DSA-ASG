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

#include "User.h"

using namespace std;

class Reply
{
	private:
		string Rtitle;
		string Rcontent;
		string Rdatetime;
		User user;

	public:
		//Constructors
		Reply();

		//Destrcutors
		~Reply();

		//Reply setters
		void setRDateTime();
		void setRDateTime(string);
		void setRTitle(string);
		void setRContent(string);
		void setRUser(User);
		
		// Reply getters
		string getRTitle();
		string getRContent();
		string getRDateTime();
		User getRUser();

		// Display the contents of the reply
		void print(int counter);
		
};

