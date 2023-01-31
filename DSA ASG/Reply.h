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
		Reply();
		~Reply();

		void setRDateTime();
		void setRTitle(string);
		void setRContent(string);

		string getRTitle();
		string getRContent();
		string getRDateTime(); 
};
