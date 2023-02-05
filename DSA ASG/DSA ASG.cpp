//  +------------------------------------------------------------+
//  |                      Team 02: AWOL                         |
//  +------------------------------------------------------------+
//  |        Student 1: Yong Zong Han Ryan, S10219317A           |
//  |                                                            |
//  |        Student 2: Tan Jin Daat, S10222867?                 |
//  +------------------------------------------------------------+

//Note to developers: only 5 reactions combined : upvote [\x18], downvote [\x19], happy [:)], sad [:(], shock [:0], cry [:'(]


//import all the necessary libraries 
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "LinkedList.h"
#include "Stack.h"
#include "Dictionary.h"
#include "Array.h"

#include "Post.h"
#include "Reply.h"
#include "Topic.h"
#include "User.h"
#include "Reaction.h"

using namespace std;



// --- Instantiation of variables ---
User currentUser;                                                   // User Obj for current user
LinkedList<User> userList;                                          // List of 
Dictionary<string, Topic> topicDictionary;                          // Dictionary (Hash Table) of topics
vector<char> specialchar;                                           // Vector of special chars (!, @, #, $ etc..)
vector<int> mainOptions;                                            // Vector of main options (Topic Level Options)
vector<int> postOptions;                                            // Vector of post options (Post Level Options) 
vector<int> reactionOptions;
int pageState;                                                      // int to store page state
string currentTopicName;                                            // string to store current topic name


// --- List of functions used ---
void displayBanner();                                               // Function to display banner
bool displaySignInScreen();                                         // Function to display the sign in screen
bool displaySignUpScreen();                                         // Finction to display the sign up screen
void displayMainMenu();                                             // Function to display the menu of sign in options [note the change]
void displayTopicMenu();                                            // Function to display the menu of topic options [note the change]
void displayPostMenu();                                             // Function to display the menu of post options
void displayReactionsMenu();                                        // Function to display the menu of reactions options

void init();                                                        // Function to initialise variables for the program 
int getOptionInput();                                               // Function to get the integer input from the menu (with validation)

bool validateUser(string username, string password);                // Function to validate the user with the backend when they sign in
bool validateUsernameInput(string username);                        // Function to validate the user USERNAME input when they sign in/sign up 
bool validatePasswordInput(string password);                        // Function to validate the user PASSWORD input when they sign in/sign up 
bool checkSpecialCharacters(string p);                              // Function to check for special characters (!, @, #, $ etc..) -> found in the vector when the user enter their PASSWORD input
bool checkInteger(string input);                                    // Function to check if the input is an integer -> for the function get Option Input
bool validateTopicName(string nameOfTopic);                         // Function to validate the user NAME input when they enter the new topic name
bool validateTopicNumber(int topicNum);                             // Function to validate the user OPTION input with the current topic dictionary when they select the topic name
bool validatePostNumber(int postNum, LinkedList<Post> postListing);


Post getNewPost();
Post editCurrentPost();
Reply getNewReply();


void saveTopicAddition(Topic t);
void savePostAddition(Post p, string topicName);
void savePostDeletion(Post p, string topicName);
void saveReplyAddition(Reply r, Post p, string topicName);
void savePostRevision(Post p, string topicName); //for add reaction and edit post
void saveUsers(User u);

void loadFiles();


// --- Main function for execution ---
int main()
{
    init();
    int signInOption = -1;
    int topicOption = -1;
    int postOption = -1;
    bool signInStatus = false;
    bool signUpStatus = false;
    while (signInOption != 0 && topicOption != 0 && postOption != 0) {

        while (currentUser.getUsername() == "" || currentUser.getPassword() == "") {
            signInOption = -999;
            while (signInOption != 1 && signInOption != 2) {
                displayMainMenu();
                signInOption = getOptionInput();
                if (signInOption == 1 && userList.isEmpty() == true) {
                    signInOption = -1;
                }
            }
            if (signInOption == 1) {
                while (!signInStatus) {
                    signInStatus = displaySignInScreen();
                }
                pageState = 1;
                displayBanner();
            }
            else {
                while (!signUpStatus) {
                    signUpStatus = displaySignUpScreen();
                }
                pageState = 1;
                displayBanner();
            }
        }

        // pageState 0 = not set
        // pageState 1 = main menu page
        // pageState 2 = post menu page


        // Topic related functions
        while ((currentUser.getUsername() != "" || currentUser.getPassword() != "") && pageState == 1) {
            topicOption = -999;
            while (!count(mainOptions.begin(), mainOptions.end(), topicOption)) {
                displayTopicMenu();
                topicOption = getOptionInput();
            }
            if (count(mainOptions.begin(), mainOptions.end(), topicOption)) {
                if (topicOption == 1) {
                    cout << endl;
                    topicDictionary.printWithCounter();
                    topicOption = -1;
                }
                else if (topicOption == 2) {
                    bool topicNameValid = false;    // boolean topic name validation
                    Topic newTopic = Topic();       // Create new Topic Obj
                    string topicName = "";          // string variable to store topic name

                    // Validate topic name
                    while (topicNameValid == false) {
                        cout << char(175) << char(175) << " Enter new Topic name:  ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, topicName);
                        cout << endl;
                        topicNameValid = validateTopicName(topicName);
                    }
                    newTopic.setTopicName(topicName);           // Set topic name to Topic Obj
                    topicDictionary.add(topicName, newTopic);   // Add topic Obj to Dictionary (Topic Hash Table)

                    //Saving the topic into a file
                    saveTopicAddition(newTopic);

                    topicOption = -1;
                }
                else if (topicOption == 3) {
                    topicOption = -1;
                    // Insert Codes Here
                    string username;                                                            //Username varaible
                    User* searchedUser;

                    cout << char(175) << char(175) << " Enter username:  ";                     //Get username from User
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, username);

                    searchedUser = userList.search(username);                                   //Return Topic Obj

                    if (searchedUser == NULL) {
                        cout << "No users found!" << endl;
                    }
                    else {
                        cout << "User found!" << endl;                                //Display topic
                        cout << "Username: " << searchedUser->getUsername() << endl;
                    }
                }
                else if (topicOption == 4) {
                    topicOption = -1;

                    string topicTitle;                                      //Topic title varaible
                    Topic* searchedTopic;

                    cout << char(175) << char(175) << " Enter Topic title:  ";                     //Get Topic title from User
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');    
                    getline(cin, topicTitle);                               
                    
                    searchedTopic = topicDictionary.search(topicTitle);     //Return Topic Obj
                    // IMPORTANT !!! SECOND PARAMETER IS THE INDEX + 1

                    if (searchedTopic != NULL) {
                        Topic topicObj = *searchedTopic;
                        topicObj.print(topicObj, 1);                  //Display topic
                    }
                    else {
                        cout << "No topic found!" << endl;
                    }

                    
                }
                else {
                    pageState = 2;
                    break;
                }
            }
        }

        // Post related functions
        while ((currentUser.getUsername() != "" || currentUser.getPassword() != "") && pageState == 2) {
            postOption = -999;
            while (!count(postOptions.begin(), postOptions.end(), postOption)) {
                displayPostMenu();
                postOption = getOptionInput();
            }
            if (postOption == 1) {
                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }
                //cout << currentTopicName << endl;
                if (topicDictionary.search(currentTopicName)->getPostList()->isEmpty()) {
                    cout << "There is no posts to display. " << endl;
                }
                else {
                    topicDictionary.search(currentTopicName)->printChildren();
                }
                postOption = -1;
            }
            else if (postOption == 2) {
                // Display the table for the user to choose
                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }

                // Add Post
                Post newPost = getNewPost();
                Topic* searchedTopic = topicDictionary.search(currentTopicName);
                bool addPostSuccess = searchedTopic->addPost(newPost);

                if (addPostSuccess) {
                    cout << "\n[SUCCESS] Post has been added." << endl;
                    savePostAddition(newPost, searchedTopic->getTopicName());
                }
                else {
                    cout << "\n[FAILED] Post was not added." << endl;
                }

                postOption = -1;
            }
            else if (postOption == 3) {
                postOption = -1;
                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }
                // Get topic ptr
                Topic* chosenTopic = topicDictionary.search(currentTopicName);
                // Print all post
                chosenTopic->printChildren();
                // Get user input
                int postIndex = -1;
                cout << char(175) << char(175) << " Select a post to edit:  ";
                cin >> postIndex;
                LinkedList<Post>* postList = chosenTopic->getPostList();
                Post* chosenPost = postList->get(postIndex - 1);

                // !!! IMPORTANT : DO YOU WANT TO ACCOUNT FOR INVALID INPUT? !!!

                string chosenPostTitle = chosenPost->getPTitle();
                Post* postObjPtr = chosenTopic->searchPost(chosenPostTitle);
                
                if (postObjPtr->getPUser().getUsername() == currentUser.getUsername()) {
                    string currentPostTitle = postObjPtr->getPTitle();
                    string currentPostDesc = postObjPtr->getPContent();

                    string newPostTitle;
                    string newPostDesc;

                    cout << "Current Post Title: " << currentPostTitle << endl;
                    cout << "Enter new Post Title: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, newPostTitle);
                    //newPostTitle = currentPostTitle + newPostTitle;

                    cout << endl;

                    cout << "Current Post Content: " << currentPostDesc << endl;
                    cout << "Enter new Post Content: ";
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, newPostDesc);
                    //newPostDesc = currentPostDesc + newPostDesc;

                    postObjPtr->setPTitle(newPostTitle);
                    postObjPtr->setPContent(newPostDesc);

                    cout << "Post updated!" << endl;
                }
                else {
                    cout << "Unable to edit as you did not make this post." << endl;
                }

                // !!! IMPORTANT : NEED TO CHECK IF THE PERSON WHO POSTED IS THE CURRENT USER !!!
            }
            else if (postOption == 4) {
                // Delete Post
                // 1. Choose a topic
                // 2. Choose a post in the topic to delete?

                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }
                Topic* chosenTopic = topicDictionary.search(currentTopicName);
                chosenTopic->printChildren();

                int postIndex = -1;
                cout << char(175) << char(175) << " Select a post to delete:  ";
                cin >> postIndex;
                chosenTopic->removePost(postIndex - 1);
                cout << chosenTopic->getPostList()->isEmpty();

                postOption = -1;

            }
            else if (postOption == 5) {
                // Add Reply

                // !!! IMPORTANT: CANNOT ADD REPLY WHEN THERE IS NO POST !!!
                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }
                // Get topic ptr
                //Topic* chosenTopic = topicDictionary.search(currentTopicName);
                topicDictionary.search(currentTopicName)->printChildren();

                LinkedList<Post>* postListPtr = topicDictionary.search(currentTopicName)->getPostList();

                // Get user input
                int postIndex = -1;
                bool postSelectionSuccess = false;

                while (!postSelectionSuccess) {
                    //Can try adding in validation for post number
                    cout << char(175) << char(175) << " Select a post to continue:  ";
                    cin >> postIndex;
                    postSelectionSuccess = validatePostNumber(postIndex, *postListPtr);
                }


                
                Post* chosenPost = postListPtr->get(postIndex - 1);

                Post* postObjPtr = topicDictionary.search(currentTopicName)->searchPost(chosenPost->getPTitle());

                cout << endl;

                Reply newReply = getNewReply();
                //newReply.setRTitle("testing title");
                //newReply.setRContent("Reply content");
                bool addReplySuccess = postObjPtr->addReply(newReply);
                if (addReplySuccess) {
                    cout << "\n[SUCCESS] Reply has been added." << endl;
                    //saveReplyAddition(newReply, postListPtr->getItem(postIndex - 1), currentTopicName);
                }
                else {
                    cout << "\n[FAILED] Reply was not added." << endl;
                }
                postOption = -1;
            }
            else if (postOption == 6) {
                // Add Reactions
                
                // Display the table for the user to choose
                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }
                
                // Get topic ptr
                Topic* chosenTopic = topicDictionary.search(currentTopicName);
                LinkedList<Post>* postList = chosenTopic->getPostList();
                //If post exists
                if (!postList->isEmpty()) {
                    cout << endl;
                    // Print all post
                    chosenTopic->printChildren();
                    // Get user input
                    int postIndex = -1;
                    bool postSelectionSuccess = false;

                    while (!postSelectionSuccess) {
                        //Can try adding in validation for post number
                        cout << char(175) << char(175) << " Select a post to continue:  ";
                        cin >> postIndex;
                        postSelectionSuccess = validatePostNumber(postIndex, *postList);
                    }
                    
                    Post* chosenPost = postList->get(postIndex - 1);
                    string chosenPostTitle = chosenPost->getPTitle();
                    Post* postObjPtr = chosenTopic->searchPost(chosenPostTitle);

                    //user can only add reaction 
                    LinkedList<User> listOfUsersThatReacted = chosenPost->returnReactionUsers();
                    if (listOfUsersThatReacted.search(currentUser.getUsername()) == nullptr) {
                        cout << endl;

                        // Prompt user for reaction (emoji)
                        int reactionOption = -999;
                        while (!count(reactionOptions.begin(), reactionOptions.end(), reactionOption)) {
                            displayReactionsMenu();
                            reactionOption = getOptionInput();
                        }

                        //Add reaction to post
                        postObjPtr->addReaction(reactionOption);
                        postObjPtr->addReactionUsers(currentUser);
                    }
                    else {
                        cout << "\nYou can only react once." << endl;
                    }
            
                }
                else {
                    cout << "\nThere is no post to react to. Please try again." << endl;
                }
                
              
                //return back to post menu
                postOption = -1;
            }
            else if (postOption == 7) {
                postOption = -1;
                int topicSelected = -1;
                bool topicSelectionSuccess = false;
                while (topicSelectionSuccess == false) {
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();
                    topicSelected = getOptionInput();
                    topicSelectionSuccess = validateTopicNumber(topicSelected);
                }
                // Get topic ptr
                Topic* chosenTopic = topicDictionary.search(currentTopicName);

                string chosenPostTitle;
                cout << "Enter a post title: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, chosenPostTitle);
                if (!chosenTopic->getPostList()->isEmpty()) {
                    Post* postObjPtr = chosenTopic->searchPost(chosenPostTitle);
                    if (postObjPtr != NULL) {
                        postObjPtr->print(1);
                    }
                    else {
                        cout << "No post found!" << endl;
                    }
                }
                else {
                    cout << "There are no post in this topic" << endl;
                }
            }
            else {
                pageState = 1;
                break;
            }
        }
    }



    while (signInOption == 0 || topicOption == 0 || postOption == 0) {
        cout << "Exiting program. See you again!" << endl;
        exit(0);
    }

    return 0;
}

// --- ENTER DESCRIPTION HERE ---
void init() {
    specialchar.push_back('!');
    specialchar.push_back('@');
    specialchar.push_back('#');
    specialchar.push_back('$');
    specialchar.push_back('%');
    specialchar.push_back('&');

    mainOptions.push_back(1);
    mainOptions.push_back(2);
    mainOptions.push_back(3);
    mainOptions.push_back(4);
    mainOptions.push_back(5);

    postOptions.push_back(1);
    postOptions.push_back(2);
    postOptions.push_back(3);
    postOptions.push_back(4);
    postOptions.push_back(5);
    postOptions.push_back(6);
    postOptions.push_back(7);
    postOptions.push_back(8);

    reactionOptions.push_back(1);
    reactionOptions.push_back(2);
    reactionOptions.push_back(3);
    reactionOptions.push_back(4);
    reactionOptions.push_back(5);


    currentUser = User();
    currentUser.setUsername("");
    currentUser.setPassword("");

    currentTopicName = "";
    pageState = 0;

    //creating directories --> must upgrade to C++ 17 first 
    //link: https://stackoverflow.com/questions/41308933/how-to-enable-c17-compiling-in-visual-studio
    fs::create_directories("./Assets/Content");
    fs::create_directories("./Assets/Users");

    //getting the topic names and storing into the topic dictionary
    std::string path = "Assets/Content";
    for (const auto& entry : fs::directory_iterator(path)) {
        string nameOfFile = entry.path().string();
        string delimiter1 = "Content\\";
        string delimiter2 = ".txt";
        size_t start_pos = nameOfFile.find(delimiter1) + delimiter1.length();
        size_t end_pos = nameOfFile.find(delimiter2);
        string topicResult = nameOfFile.substr(start_pos, end_pos - start_pos);
        //cout << topicResult << endl;
        Topic newSavedTopic = Topic();
        newSavedTopic.setTopicName(topicResult);
        topicDictionary.add(topicResult, newSavedTopic);
    }

    //getting the users and storing into a user list
    ifstream userfile;
    userfile.open("Assets/Users/userlist.txt");
    string line;
    while (getline(userfile, line)) {
        string userString =  line;
        string delimiter = ",";
        size_t pos = userString.find(delimiter);
        string usernameString = userString.substr(0, pos);
        string passwordString = userString.substr(pos + delimiter.length());
        User newSavedUser = User();
        newSavedUser.setUsername(usernameString);
        newSavedUser.setPassword(passwordString);
        bool addedSavedUserSuccess = userList.add(newSavedUser);
    }
    userfile.close();

}


void loadFiles() {

}




// --- ENTER DESCRIPTION HERE ---
void displayTopicMenu() {
    cout << endl;
    cout << "+------------------------------------------------------------------------+" << endl;
    cout << "|  Options                                                               |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  1  | View Topics     |  2  | Add Topics      |  3  | Search Users     |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  4  | Search Topics   |  5  | Display Post Menu For Selected Topic     |" << endl;
    cout << "+-----+-----------------+-----+------------------------------------------+" << endl;
    cout << "|  0  | Exit Program                                                     |" << endl;
    cout << "+-----+------------------------------------------------------------------+" << endl;
    cout << endl;
};

// --- ENTER DESCRIPTION HERE ---
void displayPostMenu() {
    cout << endl;
    cout << "+------------------------------------------------------------------------+" << endl;
    cout << "|  Options                                                               |" << endl;
    cout << "+-----+-----------------------------------------+-----+------------------+" << endl;
    cout << "|  1  | View Post(s) And Reply(ies)             |  2  | Add Post         |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  3  | Edit Post       |  4  | Delete Post     |  5  | Add Reply        |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  6  | Add Reactions   |  7  | Search Post                              |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  8  | Return Back To Main Menu                |  0  | Exit Program     |" << endl;
    cout << "+-----+-----------------------------------------+-----+------------------+" << endl;
    cout << endl;
}

// --- ENTER DESCRIPTION HERE ---
void displayReactionsMenu() {
    cout << endl;
    cout << "+------------------------------------------------------------------------+" << endl;
    cout << "|  Options                                                               |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  1  | \x18 [Upvote]      |  2  | \x19 [Downvote]    |  3  | :) [Happy]       |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  4  | :( [Sad]        |  5  | :0 [Shock]                               |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << endl;
}

// --- ENTER DESCRIPTION HERE ---
void displayMainMenu() {
    cout << "+------------------------------------------------------------------------+" << endl;
    cout << "|  Options                                                               |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  1  | Sign In         |  2  | Sign Up         |  0  | Exit Program     |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << endl;
};


// --- ENTER DESCRIPTION HERE ---
void displayBanner()
{
    cout << "\n" << endl;
    int nameCounter = 0;
    for (char c : currentUser.getUsername()) {
        nameCounter++;
    }
    cout << char(218);
    for (int i = 0; i < 72; i++) {
        char abc = 196;
        cout << abc;
    }
    cout << char(191) << endl;
    cout << "|                                                                        |" << endl;
    cout << "|";
    int spaces = (72 - 14 - nameCounter) / 2;
    if (nameCounter % 2 == 0) { //even characters
        for (int space = 0; space < spaces; space++) {
            cout << " ";
        }
        cout << "Welcome [" << currentUser.getUsername() << "] to";
        for (int space = 0; space < spaces + 1; space++) {
            cout << " ";
        }
        cout << "|";
    }
    else {
        for (int space = 0; space < spaces; space++) {
            cout << " ";
        }
        cout << "Welcome [" << currentUser.getUsername() << "] to";
        for (int space = 0; space < spaces + 2; space++) {
            cout << " ";
        }
        cout << "|";
    }
    cout << endl;
    cout << "|                        Discussion Forum 2023                           |" << endl;
    cout << "|                                                                        |" << endl;
    cout << char(192);
    for (int i = 0; i < 72; i++) {
        char abc = 196;
        cout << abc;
    }
    cout << char(217) << endl;
    cout << endl;
};

// --- ENTER DESCRIPTION HERE ---
bool displaySignInScreen() {
    string username;
    string password;
    cout << endl;
    cout << "                       Please Sign In Below To Begin                      " << endl;
    for (int i = 0; i < 74; i++) {
        cout << char(196);
    }
    cout << "\n" << endl;
    cout << char(175) << char(175) << " Username:  ";
    cin >> username;
    cout << char(175) << char(175) << " Password:  ";
    cin >> password;
    //string correctname;
    //string correctpassword;
    //correctname = "abcdef";
    //correctpassword = "123456";
    if (validateUser(username, password)) {
        currentUser.setUsername(username);
        currentUser.setPassword(password);
        return true;
    }
    else {
        cout << "\n[ERROR] You have entered invalid credentials. Please try again.\n\n\n" << endl;
        //cout << "__________________________________________________________________________" << endl;
        return false;
    }
}


// --- ENTER DESCRIPTION HERE ---
bool displaySignUpScreen() {
    string username;
    string password;
    bool usernameClear = false;
    bool passwordClear = false;
    cout << endl;
    cout << "                  Please Sign Up Below For A New Account                  " << endl;
    for (int i = 0; i < 74; i++) {
        cout << char(196);
    }
    cout << "\n" << endl;
    while (usernameClear == false) {
        cout << char(175) << char(175) << " New Username:  ";
        cin >> username;
        cout << endl;
        usernameClear = validateUsernameInput(username);
    }

    while (passwordClear == false) {
        cout << char(175) << char(175) << " New Password:  ";
        cin >> password;
        cout << endl;
        passwordClear = validatePasswordInput(password);
    }
    currentUser.setUsername(username);
    currentUser.setPassword(password);

    //saving user to the text files
    saveUsers(currentUser);

    return true;
}

// --- ENTER DESCRIPTION HERE ---
int getOptionInput() {
    bool isInteger = false;
    string input;
    while (!isInteger) {
        cout << char(175) << char(175) << " Select an option to continue:  ";
        cin >> input;
        cout << endl;
        isInteger = checkInteger(input);
        if (checkInteger(input) == false) {
            cout << "[ERROR] Only (integer) numbers are accepted. Pls try again." << endl;
        }
    }

    return stoi(input);
}

// --- ENTER DESCRIPTION HERE ---
bool checkInteger(string input)
{
    bool isNeg = false;
    int itr = 0;
    if (input.size() == 0)
        return false;
    if (input[0] == '-')
    {
        isNeg = true;
        itr = 1;
    }

    for (int i = itr; i < (int)input.size(); i++)
    {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}


// --- ENTER DESCRIPTION HERE ---
bool validateUser(string usernameInput, string passwordInput) {
    User tempUser = User();
    tempUser.setUsername(usernameInput);
    tempUser.setPassword(passwordInput);
    return userList.searchFound(tempUser);
}

// --- ENTER DESCRIPTION HERE ---
bool validateUsernameInput(string u) {
    if (u.length() > 30 || u.length() < 5) {
        cout << "[ERROR] Your username needs to be between 5 to 30 characters. Please try again.\n" << endl;
        return false;
    }
    for (char c : u) {
        if (iswalnum(c) == false) {
            cout << "[ERROR] Your username can only consists of alphabets and numbers. Please try again.\n" << endl;
            return false;
        }
    }
    return true;
}

// --- ENTER DESCRIPTION HERE ---
bool validatePasswordInput(string p) {
    if (p.length() > 20 || p.length() < 8) {
        cout << "[ERROR] Your password needs to be between 8 to 20 characters. Please try again.\n" << endl;
        return false;
    }
    if (checkSpecialCharacters(p) == false) {
        cout << "[ERROR] Your password need to include these special characters - !@#$%&. Please try again.\n" << endl;
        return false;
    }

    p.erase(remove(p.begin(), p.end(), '!'), p.end());
    p.erase(remove(p.begin(), p.end(), '@'), p.end());
    p.erase(remove(p.begin(), p.end(), '#'), p.end());
    p.erase(remove(p.begin(), p.end(), '$'), p.end());
    p.erase(remove(p.begin(), p.end(), '%'), p.end());
    p.erase(remove(p.begin(), p.end(), '&'), p.end());

    for (char c2 : p) {
        if (iswalnum(c2) == false) {
            cout << "[ERROR] Your password can only consists of alphabets, numbers and these special characters - !@#$%&. Please try again.\n" << endl;
            return false;
        }
    }
    return true;
}

// --- ENTER DESCRIPTION HERE ---
bool checkSpecialCharacters(string p) {
    for (char character1 : p) {
        for (char character2 : specialchar) {
            //cout << character << " : " << typeid(character).name() << " and " << spc << " : " << typeid(spc).name() << endl;
            if (character1 == character2) {
                return true;
            }
        }
    }
    return false;
}

// --- ENTER DESCRIPTION HERE ---
bool validateTopicNumber(int topicNum) {
    if (isdigit(topicNum)) {
        return false;
    }
    else if (topicNum <= 0) {
        return false;
    }
    currentTopicName = topicDictionary.returnSearchOption(topicNum).getTopicName();
    if (currentTopicName != "") {
        return true;
    }
    else {
        cout << "[ERROR] Invalid number inputted. Pls try again." << endl;
        return false;
    }
};

// --- ENTER DESCRIPTION HERE ---
bool validateTopicName(string nameOfTopic) {
    if (iswalnum(nameOfTopic[0]) && nameOfTopic.length() >= 1 && nameOfTopic.length() <= 50) {
        return true;
    }
    else {
        cout << "The first character needs to be an alphanumeric character and only 1 to 50 characters are allowed." << endl;
        return false;
    }
}

// --- ENTER DESCRIPTION HERE ---
Post getNewPost() {
    string title;
    string description;
    Post newPost = Post();
    cout << char(175) << char(175) << " Enter post title:  ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);
    cout << char(175) << char(175) << " Enter post description:  ";
    getline(cin, description);
    newPost.setPTitle(title);
    newPost.setPContent(description);
    newPost.setPDateTime();
    newPost.setPUser(currentUser);
    return newPost;
}

// --- ENTER DESCRIPTION HERE ---
Reply getNewReply() {
    string title;
    string description;
    Reply newReply = Reply();
    cout << char(175) << char(175) << " Enter reply title:  ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);
    cout << char(175) << char(175) << " Enter reply description:  ";
    getline(cin, description);
    newReply.setRTitle(title);
    newReply.setRContent(description);
    newReply.setRDateTime();
    newReply.setRUser(currentUser);
    return newReply;
}

Post editCurrentPost() {
    return Post();
}


// --- ENTER DESCRIPTION HERE ---
bool validatePostNumber(int postNum, LinkedList<Post> postListing) {

    if (isdigit(postNum)) {
        return false;
    }
    else if (postNum <= 0) {
        cout << "[ERROR] Invalid number inputted. Pls try again." << endl;
        return false;
    }
    else if (postNum > postListing.getLength()) {
        cout << "[ERROR] Invalid number inputted. Pls try again." << endl;
        return false;
    }
    else {
        return true;
    }
};


// --- ENTER DESCRIPTION HERE ---
void saveTopicAddition(Topic t) {

    //creating file for writing
    string filename = "Assets/Content/" + t.getTopicName() + ".txt";
    ofstream file;
    file.open(filename.c_str());
    file.close();
};

// --- ENTER DESCRIPTION HERE ---
void savePostAddition(Post p, string topicName) {
    // Open the file for reading and writing in append mode
    fstream file;
    string filename = "Assets/Content/" + topicName + ".txt";
    file.open(filename, ios::in | ios::out | ios::app);

    // Read the existing contents of the file into a vector of strings
    vector<string> contents;
    string line;
    while (getline(file, line)) {
        contents.push_back(line);
    }

    // Add the new string to the end of the vector
    string new_string = "[Post]" + p.getPTitle() + "\\" + p.getPContent() + "\\" + p.getPDateTime() + "\\" + p.getPUser().getUsername() + "\\" + p.getPUser().getPassword();
    for (int i = 0; i < p.getReactions().getLength(); i++) {
        Reaction* react = p.getReactions().get(i);
        new_string = new_string + "\\" + to_string(react->getEmojiCount());
    }
    contents.push_back(new_string);

    // Close the file
    file.close();

    // Open the file again, but this time in write mode
    file.open(filename, ios::out | ios::trunc);

    // Write the contents of the vector to the file
    for (const string& s : contents) {
        file << s << endl;
    }

    // Close the file
    file.close();
};

// --- ENTER DESCRIPTION HERE ---
void savePostDeletion(Post p, string topicName) {

};

// --- ENTER DESCRIPTION HERE ---
void saveReplyAddition(Reply r, Post p, string topicName) {
    vector<string> lines;
    string filename = "Assets/Content/" + topicName + ".txt";
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
    }
    // Find the line where you want to insert the new string
    //string targetLine = "This is the target line.";
    string targetLine = "[Post]" + p.getPTitle() + "\\" + p.getPContent() + "\\" + p.getPDateTime() + "\\" + p.getPUser().getUsername() + "\\" + p.getPUser().getPassword();
    for (int i = 0; i < p.getReactions().getLength(); i++) {
        Reaction* react = p.getReactions().get(i);
        targetLine = targetLine + "\\" + to_string(react->getEmojiCount());
    }
    int targetIndex = -1;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i] == targetLine) {
            targetIndex = i;
            break;
        }
    }
    // Insert the new string after the target line
    string new_string = "[Reply]" + r.getRTitle() + "\\" + r.getRContent() + "\\" + r.getRDateTime() + "\\" + r.getRUser().getUsername() + "\\" + r.getRUser().getPassword();
    if (targetIndex != -1) {
        lines.insert(lines.begin() + targetIndex + 1, new_string);
    }
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& line : lines) {
            outputFile << line << '\n';
        }
        outputFile.close();
    }
};

// --- ENTER DESCRIPTION HERE ---
void savePostRevision(Post r, string topicName) {

};


// --- ENTER DESCRIPTION HERE ---
void saveUsers(User u) {
    string filename = "Assets/Users/userlist.txt";
    ofstream file;
    file.open(filename.c_str(), ios::app);


    if (file.is_open()) {
        string inputUser = u.getUsername() + "," + u.getPassword();
        file << inputUser << endl;
        file.close();
    }
    else {
        std::cout << "Error in opening file." << std::endl;
    }
};