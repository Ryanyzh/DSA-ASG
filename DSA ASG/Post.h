#pragma once
#include <iostream>
#include <string>
#include <ctime>

#include "Stack.h"
#include "Array.h"
#include "User.h"
#include "Reply.h"
#include "Reaction.h"

using namespace std;


class Post
{
	private:
		string Ptitle;
		string Pcontent;
		string Pdatetime;
		User user;
		Array<Reaction> reactions;
		Stack<Reply> replyStack;


	public:
		//Post constructors and destructures
		Post();
		~Post();

		// Post setters
		void setPDateTime();
		void setPTitle(string);
		void setPContent(string);

		//Post getters
		string getPTitle();
		string getPContent();
		string getPDateTime();
		Stack<Reply> getRStack();

		//Add reply to post
		bool addReply(Reply reply);
};

