#pragma warning(disable : 4996) //disbale deprication warning

#include "Post.h"
#include <string>
#include <iostream>
#include <string>

//for getting the datetime result
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

Post::Post() {
	Ptitle = "";
	Pcontent = "";
	Pdatetime = "";
	user = User();  
	replyStack = Stack<Reply>();
	reactions = Array<Reaction>();

	vector<string> reactionsString;
	reactionsString.push_back("\x18");
	reactionsString.push_back("\x19");
	reactionsString.push_back(":)");
	reactionsString.push_back(":(");
	reactionsString.push_back(":0");
	for (string reactString : reactionsString) {
		Reaction r = Reaction();
		r.setEmoji(reactString);
		reactions.add(r);
	}

	reactionUsers = LinkedList<User>();
};

void Post::setPDateTime(string dateTime) {
	Pdatetime = dateTime;
}

void Post::setReactions(Array<Reaction> newReactions) {
	reactions = newReactions;
}

void Post::setReactionUsers(LinkedList<User> userList) {
	reactionUsers = userList;
}

Post::~Post() {
	// Deconstruct replyStack
	replyStack.~Stack<Reply>();
};

string Post::retrieveString() {
	return getPTitle();
}

Array<Reaction> Post::getReactions() {
	return reactions;
}

User Post::getPUser() {
	return user;
}

string Post::getPTitle() {
	return Ptitle;
};

string Post::getPContent() {
	return Pcontent;
};

string Post::getPDateTime() {
	return Pdatetime;
}

Stack<Reply>* Post::getRStack() {
	return &replyStack;
}

void Post::setPDateTime() {
	auto nowtime = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(nowtime);
	stringstream ss;
	ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
	string current_time = ss.str(); //2023-01-30 18:40:00 = 19 spaces
	Pdatetime = current_time;
};

void Post::setPTitle(string pt) {
	Ptitle = pt;
};

void Post::setPContent(string pc) {
	Pcontent = pc;
};

void Post::setPUser(User u) {
	user = u;
}

bool Post::addReply(Reply reply) {
	return this->getRStack()->push(reply);
}

void Post::addReaction(int i) {
	reactions.get(i - 1)->addCount();
}

bool Post::equivalent(Post anotherPost) {
	return (this->getPTitle() == anotherPost.getPContent());
}

void Post::printChildren() {
	replyStack.printWithCounter();
}



void Post::print(int counter) {
	//?________________________________________________________________________?  #1
	//|                                                                        |  #2
	//|  # Post 1                                                              |  #3
	//|                                                                        |  #4
	//|  Name: 	       John Cena                          ????-??-?? ??-??-??  |  #5
	//|                                                                        |  #6
	//|  Title:        Your ---                                                |  #7
	//|  Decription:   Your --- --- Your --- --- Your --- --- Your --- --- Yo  |  #8
	//|                Your --- --- Your --- --- Your --- --- Your --- --- Yo  |  #9
	//|                                                                        |  #10
	//|  Reactions:    1 - 999    2 - 999    33 - 999    44 - 999    55 - 999  |  #11
	//|                                                                        |  #12
	//?________________________________________________________________________?  #13

	//printing the first line
	cout << char(218);
	for (int i = 0; i < 72; i++) {	cout << char(196);	}
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
	int secondSpacing = 72 - getPUser().getUsername().length() - 37;
	cout << "|  Name:         " << this->getPUser().getUsername();
	for (int i = 0; i < secondSpacing; i++) { cout << " "; }
	cout << this->getPDateTime() << "  |" << endl;

	//printing the sixth line
	cout << "|                                                                        |" << endl;

	//printing the seventh line

	/*
	int thirdSpacing = 72 - getPTitle().length() - 18;
	cout << "|  Title:        " << this->getPTitle();
	for (int i = 0; i < thirdSpacing; i++) { cout << " "; }
	cout << "  |" << endl;
	*/

	int num_of_lines = (int)((getPTitle().length() / 53)) + 1;  //54 spaces
	//cout << "lines: " << num_of_lines << endl;
	if (num_of_lines == 1) {
		int thirdSpacing = 72 - getPTitle().length() - 18;
		cout << "|  Title:        " << this->getPTitle();
		for (int i = 0; i < thirdSpacing; i++) { cout << " "; }
		cout << "  |" << endl;
	}
	else {
		//string one = this->getPContent().substr(0, 53);
		cout << "|  Title:        " << this->getPTitle().substr(0, 53) << "-" << "  |" << endl;
		for (int i = 0; i < num_of_lines - 1; i++) {
			if (i != num_of_lines - 2) {
				cout << "|                " << this->getPTitle().substr(53 * (i + 1), 53) << "-" << "  |" << endl;
			}
			else {
				int char_left = this->getPTitle().length() - ((i + 1) * 53);
				int newSpacing = 72 - 16 - char_left - 2;
				cout << "|                " << this->getPTitle().substr((53 * (i + 1)), char_left);
				for (int i = 0; i < newSpacing; i++) { cout << " "; }
				cout << "  |" << endl;;
			}
		}
	}


	//printing the eighth line
	num_of_lines = (int)((getPContent().length() / 53)) + 1;  //54 spaces
	//cout << "lines: " << num_of_lines << endl;
	if (num_of_lines == 1) {
		int fourthSpacing = 72 - getPContent().length() - 18;
		cout << "|  Description:  " << this->getPContent();
		for (int i = 0; i < fourthSpacing; i++) { cout << " "; }
		cout << "  |" << endl;
	}
	else {
		//string one = this->getPContent().substr(0, 53);
		cout << "|  Description:  " << this->getPContent().substr(0, 53) << "-" << "  |" << endl;
		for (int i = 0; i < num_of_lines - 1; i++) {
			if (i != num_of_lines - 2) {
				cout << "|                " << this->getPContent().substr(53 * (i + 1), 53) << "-" << "  |" << endl;
			}
			else {
				int char_left = this->getPContent().length() - ((i + 1) * 53);
				int fifthSpacing = 72 - 16 - char_left - 2;
				cout << "|                " << this->getPContent().substr((53*(i + 1)), char_left);
				for (int i = 0; i < fifthSpacing; i++) { cout << " "; }
				cout << "  |" << endl;;
			}
		}
	}
	

	//printing the tenth line
	cout << "|                                                                        |" << endl;

	//printing the eleventh line
	cout << "|  Reactions:    ";
	this->getReactions().print();
	cout << "|" << endl;

	//printing the twelveth line 
	cout << "|                                                                        |" << endl;

	//printing the thirteen line
	cout << char(192);
	for (int i = 0; i < 72; i++) { cout << char(196); }
	cout << char(217) << endl;
	

	if (replyStack.isEmpty() != true) {
		//printChildren();
		replyStack.printWithCounter();
	}
	else {
		cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219)
			<< "|  There is no reply for this post.                                |" << endl;
		cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
		cout << char(192);
		for (int i = 0; i < 66; i++) { cout << char(196); }
		cout << char(217) << endl;
	}

	// ** TO BE EDITED BY RYAN **
	// 
	//cout << this->getPTitle() << endl;
	//cout << this->getPContent() << endl;
	//cout << this->getPDateTime() << endl;
	//this->getRStack().printInOrder();
	//this->getReactions().print();
	//cout << this->getPUser().getUsername() << endl;
}



LinkedList<User> Post::returnReactionUsers() {
	return reactionUsers;
}

void Post::addReactionUsers(User u) {
	this->reactionUsers.add(u);
}