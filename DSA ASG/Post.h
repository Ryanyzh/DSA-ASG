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
		// Constructors 
		Post();

		// Destructors
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
		LinkedList<User> returnReactionUsers();

		// Get the title of the post
		string retrieveString();

		// Check if both Post object matches
		bool equivalent(Post p);

		// Add reply to post
		bool addReply(Reply reply);

		// Add reaction to post
		void addReaction(int index);

		// Display the content of the post and reply
		void print(int counter);

		// Display the content of the post and reply with index number
		void printChildren();

		// Add users to reaction list
		void addReactionUsers(User u);
};

