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

User Reply::getRUser() {
	return user;
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

void Reply::setRUser(User u) {
	user = u;
}

void Reply::print(int counter) {
	//XXXXXX?__________________________________________________________________?
	//XXXXXX|                                                                  |
	//XXXXXX|  # Reply 1                                                       |
	//XXXXXX|                                                                  |
	//XXXXXX|  Name: 	       John Cena                  ????-??-?? ??-??-??  |
	//XXXXXX|                                                                  |
	//XXXXXX|  Title:        Your ---                                          |
	//XXXXXX|  Decription:   Your --- --- Your --- --- Your --- --- Your ---Y  |
	//XXXXXX|                Your --- --- Your --- --- Your --- --- Your ---Y  |
	//XXXXXX|                                                                  |
	//XXXXXX?__________________________________________________________________?
	/*cout << this->getRTitle() << endl;
	cout << this->getRContent() << endl;
	cout << this->getRDateTime() << endl;
	cout << this->getRUser().getUsername() << endl;*/

	cout << char(218);
	for (int i = 0; i < 72; i++) { cout << char(196); }
	cout << char(191) << endl;

	//printing the second line
	cout << "|                                                                        |" << endl;

	//printing the third line
	int firstSpacing = 72 - (to_string(counter).length()) - 9;
	cout << "|  # Post " << counter;
	for (int i = 0; i < firstSpacing; i++) { cout << " "; }
	cout << "|" << endl;

	//printing the fourth line
	cout << "|                                                                        |" << endl;

	//printing the fifth line
	int secondSpacing = 72 - getRUser().getUsername().length() - 37;
	cout << "|  Name:         " << this->getRUser().getUsername();
	for (int i = 0; i < secondSpacing; i++) { cout << " "; }
	cout << this->getRDateTime() << "  |" << endl;

	//printing the sixth line
	cout << "|                                                                        |" << endl;

	//printing the seventh line
	int thirdSpacing = 72 - getRTitle().length() - 18;
	cout << "|  Title:        " << this->getRTitle();
	for (int i = 0; i < thirdSpacing; i++) { cout << " "; }
	cout << "  |" << endl;

	//printing the eighth line
	int num_of_lines = (int)((getRContent().length() / 53) + 0.5);  //54 spaces
	//cout << "lines: " << num_of_lines << endl;
	if (num_of_lines == 1) {
		int fourthSpacing = 72 - getRContent().length() - 18;
		cout << "|  Description:  " << this->getRContent();
		for (int i = 0; i < fourthSpacing; i++) { cout << " "; }
		cout << "  |" << endl;
	}
	else {
		//string one = this->getPContent().substr(0, 53);
		cout << "|  Description:  " << this->getRContent().substr(0, 53) << "-" << "  |" << endl;
		for (int i = 0; i < num_of_lines - 1; i++) {
			if (i != num_of_lines - 1) {
				cout << "|                " << this->getRContent().substr(53 * (i + 1), 53) << "-" << "  |" << endl;
			}
			else {
				int char_left = this->getRContent().length() - ((i + 1) * 53);
				int fifthSpacing = 72 - 16 - char_left - 2;
				cout << "|                " << this->getRContent().substr((53 * (i + 1)), char_left) << "-" << "  |" << endl;
				for (int i = 0; i < fifthSpacing; i++) { cout << " "; }
				cout << "  |" << endl;;
			}
		}
	}
}
