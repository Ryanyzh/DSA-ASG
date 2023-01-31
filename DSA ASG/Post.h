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
		User getPUser();
		Array<Reaction> getReactions();
		Stack<Reply> getRStack();

		string retrieveString();

		bool equivalent(Post p);

		//Add reply to post
		bool addReply(Reply reply);

		void updateReaction(int index);

		void print();
};

