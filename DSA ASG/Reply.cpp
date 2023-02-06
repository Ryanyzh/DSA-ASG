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
	Rdatetime = "";
	user = User();
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

void Reply::setRDateTime(string s) {
	Rdatetime = s;
}

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
	//XXXXXX|                                                                  |  #2
	//XXXXXX|  # Reply 1                                                       |  #3
	//XXXXXX|                                                                  |  #4
	//XXXXXX|  Name: 	       John Cena                  ????-??-?? ??-??-??  |  #5
	//XXXXXX|                                                                  |  #6
	//XXXXXX|  Title:        Your ---                                          |  #7
	//XXXXXX|  Decription:   Your --- --- Your --- --- Your --- --- Your ---Y  |  #8
	//XXXXXX|                Your --- --- Your --- --- Your --- --- Your ---Y  |  #9
	//XXXXXX|                                                                  |  #10
	//XXXXXX?__________________________________________________________________?  #11
	/*cout << this->getRTitle() << endl;
	cout << this->getRContent() << endl;
	cout << this->getRDateTime() << endl;
	cout << this->getRUser().getUsername() << endl;*/



	//printing the second line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	cout << "|                                                                  |" << endl;

	//printing the third line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	int firstSpacing = 66 - (to_string(counter).length()) - 10;
	cout << "|  # Reply " << counter;
	for (int i = 0; i < firstSpacing; i++) { cout << " "; }
	cout << "|" << endl;

	//printing the fourth line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}  
	cout << "|                                                                  |" << endl;

	//printing the fifth line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	int secondSpacing = 66 - getRUser().getUsername().length() - 37;
	cout << "|  Name:         " << this->getRUser().getUsername();
	for (int i = 0; i < secondSpacing; i++) { cout << " "; }
	cout << this->getRDateTime() << "  |" << endl;

	//printing the sixth line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	cout << "|                                                                  |" << endl;

	//printing the seventh line
	/*
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	int thirdSpacing = 66 - getRTitle().length() - 18;
	cout << "|  Title:        " << this->getRTitle();
	for (int i = 0; i < thirdSpacing; i++) { cout << " "; }
	cout << "  |" << endl;
	*/

	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	int num_of_lines = (int)((getRTitle().length() / 46)) + 1;  //48 spaces

	if (num_of_lines == 1) {
		int thirdSpacing = 66 - getRTitle().length() - 18;
		cout << "|  Title:        " << this->getRTitle();
		for (int i = 0; i < thirdSpacing; i++) { cout << " "; }
		cout << "  |" << endl;
	}
	else {
		cout << "|  Title:        " << this->getRTitle().substr(0, 47) << "-" << "  |" << endl;
		for (int i = 0; i < num_of_lines - 1; i++) {
			if (i != num_of_lines - 2) {
				// ----- printIndentation
				for (int b = 0; b < 6; b++) {
					cout << char(219);
				}
				cout << "|                " << this->getRTitle().substr(47 * (i + 1), 47) << "-" << "  |" << endl;
			}
			else {
				// ----- printIndentation
				for (int b = 0; b < 6; b++) {
					cout << char(219);
				}
				int char_left = this->getRTitle().length() - ((i + 1) * 47);
				int newSpacing = 66 - 16 - char_left - 2;
				cout << "|                " << this->getRTitle().substr((47 * (i + 1)), char_left);
				for (int i = 0; i < newSpacing; i++) { cout << " "; }
				cout << "  |" << endl;;
			}
		}
	}





	//printing the eighth line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	num_of_lines = (int)((getRContent().length() / 46)) + 1;  //48 spaces
	
	if (num_of_lines == 1) {
		int fourthSpacing = 66 - getRContent().length() - 18;
		cout << "|  Description:  " << this->getRContent();
		for (int i = 0; i < fourthSpacing; i++) { cout << " "; }
		cout << "  |" << endl;
	}
	else {
		cout << "|  Description:  " << this->getRContent().substr(0, 47) << "-" << "  |" << endl;
		for (int i = 0; i < num_of_lines - 1; i++) {
			if (i != num_of_lines - 2) {
				// ----- printIndentation
				for (int b = 0; b < 6; b++) {
					cout << char(219);
				}
				cout << "|                " << this->getRContent().substr(47 * (i + 1), 47) << "-" << "  |" << endl;
			}
			else {
				// ----- printIndentation
				for (int b = 0; b < 6; b++) {
					cout << char(219);
				}
				int char_left = this->getRContent().length() - ((i + 1) * 47);
				int fifthSpacing = 66 - 16 - char_left - 2;
				cout << "|                " << this->getRContent().substr((47 * (i + 1)), char_left);
				for (int i = 0; i < fifthSpacing; i++) { cout << " "; }
				cout << "  |" << endl;;
			}
		}
	}

	//printing the tenth line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	cout << "|                                                                  |" << endl;

	//printing the eleventh line
	// ----- printIndentation
	for (int b = 0; b < 6; b++) {
		cout << char(219);
	}
	cout << char(192);
	for (int i = 0; i < 66; i++) { cout << char(196); }
	cout << char(217) << endl;
}

