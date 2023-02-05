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
		//PLinkedList::PNode* postPointer;
		Topic();
		~Topic();

		//Topic Setter 
		void setTopicName(string);

		//Topic getter
		string getTopicName();

		// Post list getter
		LinkedList<Post>* getPostList();

		LinkedList<Post> getPostListItem();

		//Add post to topic
		bool addPost(Post post);

		//Remove post from topic
		void removePost(int index);

		//Search and return Post index
		int searchPostIndex(string s);

		//Search and return Post Object
		Post* searchPost(string s);

		//Display topic details -> from the Dictionary class
		void print(Topic t, int counter);

		void printChildren();


};

