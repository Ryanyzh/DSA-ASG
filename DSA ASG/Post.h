#pragma once
#include <iostream>
#include <string>
#include <ctime>

#include "Stack.h"
#include "Array.h"
#include "User.h"
#include "Reply.h"
#include "Reaction.h"
#include "LinkedList.h"

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
		LinkedList<User> reactionUsers;


	public:
		//Post constructors and destructures
		Post();
		~Post();

		// Post setters
		void setPDateTime();
		void setPDateTime(string);
		void setPTitle(string);
		void setPContent(string);
		void setPUser(User);
		void setReactions(Array<Reaction>);
		void setReactionUsers(LinkedList<User>);

		//Post getters
		string getPTitle();
		string getPContent();
		string getPDateTime();
		User getPUser();
		Array<Reaction> getReactions();
		Stack<Reply>* getRStack();

		string retrieveString();

		bool equivalent(Post p);

		//Add reply to post
		bool addReply(Reply reply);

		void addReaction(int index);

		void print(int counter);

		void printChildren();

		LinkedList<User> returnReactionUsers();

		void addReactionUsers(User u);
};

