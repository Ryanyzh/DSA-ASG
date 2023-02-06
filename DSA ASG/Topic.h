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

#include "LinkedList.h"
#include "Post.h"

using namespace std;

class Topic
{
	private:
		string topicName;
		LinkedList<Post> postList;

	public:
		// Constructor
		Topic();

		// Destrcutor
		~Topic();

		// Topic setter 
		void setTopicName(string);

		// Topic getters
		string getTopicName();
		LinkedList<Post>* getPostList();
		LinkedList<Post> getPostListItem();

		// Add post to topic
		bool addPost(Post post);

		// Remove post from topic
		void removePost(int index);

		// Search and return post index from post name
		int searchPostIndex(string s);

		// Search and return post object from post name
		Post* searchPost(string s);

		// Display contents of the topic (from the Dictionary class)
		void print(int counter);

		// Display all the reply details
		void printChildren();


};

