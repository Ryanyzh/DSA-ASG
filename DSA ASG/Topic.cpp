#include "Topic.h"
#include <iostream>
#include <string>

using namespace std;

Topic::Topic() {
	topicName = "";
	postList = LinkedList<Post>();
};

Topic::~Topic() {
	//idk
};

string Topic::getTopicName() {
	return topicName;
};

void Topic::setTopicName(string tn) {
	topicName = tn;
};

LinkedList<Post>* Topic::getPostList() {
	return &postList;
}

LinkedList<Post> Topic::getPostListItem() {
	return postList;
}

bool Topic::addPost(Post post) {
	return postList.add(post);
}

int Topic::searchPostIndex(string str) {
	return postList.searchIndex(str);
}

Post* Topic::searchPost(string str) {
	return postList.search(str);
}

void Topic::removePost(int index) {
	postList.remove(index);
}

void Topic::print(int counter) {
	int spacing = 0;
	if (counter == 1) {
		cout << "+------------------------------------------------------------------------+" << endl;
		cout << "| Topic |     Name                                                       |" << endl;
		cout << "+------------------------------------------------------------------------+" << endl;
	}
	spacing = 64 - 5 - (int)topicName.length();
	if (counter < 10) {
		cout << "|   " << counter << "   |     " << topicName;
		for (int spaces = 0; spaces < spacing; spaces++) {
			cout << " ";
		}
		cout << "|" << endl;
		cout << "+------------------------------------------------------------------------+" << endl;
		//counter++;
	}
	else {
		cout << "|  " << counter << "   |     " << topicName;
		for (int spaces = 0; spaces < spacing; spaces++) {
			cout << " ";
		}
		cout << "|" << endl;
		cout << "+------------------------------------------------------------------------+" << endl;
		//counter++;
	}
}


void Topic::printChildren() {
	if (postList.isEmpty()) {
		cout << "There is no post to display" << endl;
	}
	else {
		postList.printWithCounter();
	}
	
}

