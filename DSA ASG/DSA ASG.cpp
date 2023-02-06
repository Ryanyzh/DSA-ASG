//  +------------------------------------------------------------+
//  |                      Team 02: AWOL                         |
//  +------------------------------------------------------------+
//  |        Student 1: Yong Zong Han Ryan, S10219317A           |
//  |                                                            |
//  |        Student 2: Tan Jin Daat, S10222867E                 |
//  +------------------------------------------------------------+


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// IMPORTANT NOTE:  Must upgrade to C++ 17 firstlink: https://stackoverflow.com/questions/41308933/how-to-enable-c17-compiling-in-visual-studio before running the program
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/*  ################################################
    ##     Import all the necessary libraries     ##
    ################################################    */

#include <iostream>                                                         //use C++ standard library (for input and output)      
#include <string>                                                           //use C++ standard library (for using STRING data type)
#include <cmath>                                                            //use C++ standard library (for mathematical operations)
#include <vector>                                                           //use C++ standard library (for using vectors)

#include <algorithm>                                                        //use C++ standard library (storing and loading data into the program)
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <filesystem>
namespace fs = std::filesystem;                                             //uses the library (std) inside the global namespace

#include "LinkedList.h"                                                     //header files for data structures and algorithms - Linked List
#include "Stack.h"                                                          //header files for data structures and algorithms - Stack
#include "Dictionary.h"                                                     //header files for data structures and algorithms - Dictionary
#include "Array.h"                                                          //header files for data structures and algorithms - Array

#include "Post.h"                                                           //header files for individual class - Post
#include "Reply.h"                                                          //header files for individual class - Reply
#include "Topic.h"                                                          //header files for individual class - Topic
#include "User.h"                                                           //header files for individual class - User
#include "Reaction.h"                                                       //header files for individual class - Reaction

using namespace std;                                                        //uses the library (std) inside the global namespace



/*  ########################################
    ##     Instantiation of variables     ##
    ########################################    */

User currentUser;                                                           // User Obj for current user (that is logged in)
LinkedList<User> userList;                                                  // Linked List of Users
Dictionary<string, Topic> topicDictionary;                                  // Dictionary (Hash Table) of topics
vector<char> specialchar;                                                   // Vector of special chars (!, @, #, $ etc..)
vector<int> mainOptions;                                                    // Vector of main options (Topic Level Options)
vector<int> postOptions;                                                    // Vector of post options (Post Level Options) 
vector<int> reactionOptions;                                                // Vector of reaction options (Reaction Level Options) 
int pageState;                                                              // Integer to store page state (0 = not set, 1 = main menu page, 2 = post menu page)
string currentTopicName;                                                    // String to store current topic name


 /* ####################################
    ##     List of functions used     ##
    ####################################    */

void displayBanner();                                                       // Function to display banner
bool displaySignInScreen();                                                 // Function to display the sign in screen
bool displaySignUpScreen();                                                 // Finction to display the sign up screen
void displayMainMenu();                                                     // Function to display the menu of sign in options [note the change]
void displayTopicMenu();                                                    // Function to display the menu of topic options [note the change]
void displayPostMenu();                                                     // Function to display the menu of post options
void displayReactionsMenu();                                                // Function to display the menu of reactions options

void init();                                                                // Function to initialise variables for the program 
int getOptionInput();                                                       // Function to get the integer input from the menu (with validation)

bool validateUser(string username, string password);                        // Function to validate the user with the backend when they sign in
bool validateUsernameInput(string username);                                // Function to validate the user USERNAME input when they sign in/sign up 
bool validatePasswordInput(string password);                                // Function to validate the user PASSWORD input when they sign in/sign up 
bool checkSpecialCharacters(string p);                                      // Function to check for special characters (!, @, #, $ etc..) -> found in the vector when the user enter their PASSWORD input
bool checkInteger(string input);                                            // Function to check if the input is an integer -> for the function get Option Input
bool validateTopicName(string nameOfTopic);                                 // Function to validate the user NAME input when they enter the new topic name
bool validateTopicNumber(int topicNum);                                     // Function to validate the user OPTION input with the current topic dictionary when they select the topic name
bool validatePostNumber(int postNum, LinkedList<Post> postListing);

Post getNewPost();                                                          // Function that gets the user input for the post details and return the Post object
Post editCurrentPost();                                                     // Function that gets the user input for the post details and return the Post object
Reply getNewReply();                                                        // Function that gets the user input for the reply details and return the Reply object

void saveTopicAddition(Topic t);                                            // Function to insert the new Topic object into the text file for saving - for adding new topic
void savePostAddition(Post p, string topicName);                            // Function to insert the new Post object into the text file for saving - for adding new post
void savePostDeletion(Post* p, string topicName, int replyNum);             // Function to remove the Post object into the text file for saving - for deleting post
void saveReplyAddition(Reply r, Post *p, string topicName);                 // Function to insert the new Reply object into the text file for saving - for adding new reply
void savePostRevision(Post* newPost, Post* oldPost, string topicName);      // Function to replace the Post object into the text file for saving - for adding reactions and editing posts
void saveUsers(User u);                                                     // Function to insert the User object into the text file for saving 

void exitProgram();                                                         // Function used to exit the program



/*  #########################################
    ##     Main function for execution     ##
    #########################################   */
int main()
{
    init();                                                                                                 // Call function to intialize some variables and load the data from text file
    int signInOption = -1;                                                                                  // Initalize the options variables for Topic, Post and Log In Menu
    int topicOption = -1;
    int postOption = -1;
    bool signInStatus = false;                                                                              // Initalize the status of sign in/sign up of the user (true - success, false - failed)
    bool signUpStatus = false;
    while (true) {                                                                                          // Iterating the program until the option for exit is entered

        while (currentUser.getUsername() == "" || currentUser.getPassword() == "") {                        // Iterating the sign in page when the user credentials are empty
            signInOption = -999;                                                                    
            while (signInOption != 1 && signInOption != 2) {                                                // Iterating the login menu until the correct option entered
                displayMainMenu();                                                                          // Displaying the login menu
                signInOption = getOptionInput();                                                            // Getting the option for the login menu

                if (signInOption == 0) {
                    exitProgram();
                }

                if (signInOption == 1 && userList.isEmpty() == true) {                                      // Preventing user sign in if there is nothing in the list of users extracted from the text files
                    signInOption = -1;                                          
                }
            }
            if (signInOption == 1) {                                                                        // Sign In Process if the option entered is 1
                while (!signInStatus) {                                                             
                    signInStatus = displaySignInScreen();                                                   // Getting the status of sign in after entering the credentails and validation
                }
                pageState = 1;                                                                              // Variable to proceeding to the topic menu
                displayBanner();                                                                            // Displaying the banner to welcome the user
            }
            else {
                while (!signUpStatus) {                                                                     // Sign Up Process if the option entered is 2
                    signUpStatus = displaySignUpScreen();                                                   // Getting the status of sign up after entering the credentails and validation
                }
                pageState = 1;                                                                              // Variable to proceeding to the topic menu
                displayBanner();                                                                            // Displaying the banner to welcome the user
            }
        }

                                                                                                            // -------- Topic and Search related functions below --------
        while ((currentUser.getUsername() != "" || currentUser.getPassword() != "") && pageState == 1) {    // Iterating the topic page after the user has signed in
            topicOption = -999;
            while (!count(mainOptions.begin(), mainOptions.end(), topicOption)) {                           // Checking if the options are within the correct range for the Topic menu
                displayTopicMenu();                                                                         // Displaying the topic menu
                topicOption = getOptionInput();                                                             // Getting the option for the topic menu
                if (topicOption == 0) {
                    exitProgram();
                }
            }
            if (count(mainOptions.begin(), mainOptions.end(), topicOption)) {                               
                if (topicOption == 1) {                                                                     // Printing the topic names when the option is 1
                    cout << endl;
                    topicDictionary.printWithCounter();                                                     // Printing the topic names from the dictionary into a table
                    topicOption = -1;                                                                       // Resetting back to the topic menu
                }
                else if (topicOption == 2) {                                                                // Adding new topic when the option is 2
                    bool topicNameValid = false;                                                            // Boolean to validate the topic name input
                    Topic newTopic = Topic();                                                               // Create new Topic object 
                    string topicName = "";                                                                  // Store topic name in this string variable

                    while (topicNameValid == false) {                                                       // Iterating until the topic name input is correct
                        cout << char(175) << char(175) << " Enter new Topic name:  ";                       
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, topicName);                                                            // Storing the input into the string variable
                        cout << endl;
                        topicNameValid = validateTopicName(topicName);                                      // Validate topic name input
                    }
                    newTopic.setTopicName(topicName);                                                       // Set topic name to Topic object
                    topicDictionary.add(topicName, newTopic);                                               // Add new topic object to Dictionary (Hash Table for Topics)
                    
                    saveTopicAddition(newTopic);                                                            // Saving the topic into a file

                    cout << "[SUCCESS] Topic has been added." << endl;                                      // Display the result status

                    topicOption = -1;                                                                       // Resetting back to the topic menu
                }
                else if (topicOption == 3) {                                                                // Searching for users 
                    string username;                                                                        // String variable to store user input for username
                    User* searchedUser;                                                                     // Storing the user class into this variable

                    cout << char(175) << char(175) << " Enter username:  ";                                 // Getting user input
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, username);                                                                 // Storing into the string variable

                    searchedUser = userList.search(username);                                               // Search for user object from the user list containing all the user (extracted from the text file)

                    if (searchedUser == NULL) { 
                        cout << "No users found!" << endl;                                                  // Displaying the result status
                    }
                    else {
                        cout << "User found!" << endl;                                
                        cout << "Username: " << searchedUser->getUsername() << endl; 
                    }

                    topicOption = -1;                                                                       // Resetting back to the topic menu
                }
                else if (topicOption == 4) {                                                                // Searching for topics
                    
                    string topicTitle;                                                                      // Storing the topic object into the Topic pointer
                    Topic* searchedTopic;

                    cout << char(175) << char(175) << " Enter Topic title:  ";                              // Getting user input for the topic name
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');    
                    getline(cin, topicTitle);                                                               // Storing the input into the string variable        
                    
                    searchedTopic = topicDictionary.search(topicTitle);                                     // Search the topic name inside the Topic dictionary and return the topic object found

                    if (searchedTopic != NULL) {                                                            // Checking if the search return any non-empty object
                        Topic topicObj = *searchedTopic;                                                    
                        topicObj.print(1);                                                                  // Displaying the topic object
                    }
                    else {
                        cout << "No topic found!" << endl;                                                  // Displaying the result status if there is no post object
                    }
                    topicOption = -1;                                                                       // Resetting back to the topic menu
                }
                else {                                                                                      // Travel to the post menu options
                    if (topicDictionary.getLength() != 0) {                                                 // Can advance only if there are topic object in topic dictionary
                        pageState = 2;              
                        break;
                    }
                    else {
                        cout << "A topic needs to be added before proceeding." << endl;                     // Cannot advance if there are np topic object in topic dictionary
                        topicOption = -1;                                                                   // Resetting back to the topic menu
                    }
                }
            }
        }

                                                                                                            // -------- Post and Replyrelated functions --------
        while ((currentUser.getUsername() != "" || currentUser.getPassword() != "") && pageState == 2) {    // Iterating the post page after the user has signed in
            postOption = -999;
            while (!count(postOptions.begin(), postOptions.end(), postOption)) {                            // Checking if the options are within the correct range for the Post menu
                displayPostMenu();                                                                          // Displaying the post menu 
                postOption = getOptionInput();                                                              // Getting the option for the post menu
                if (postOption == 0) {
                    exitProgram();
                }
            }
            if (postOption == 1) {                                                                          // Printing the posts and replies when the option is 1
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option from the user
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the status
                }
                
                if (topicDictionary.search(currentTopicName)->getPostList()->isEmpty()) {                   // Search for the list of post from current topic in the topic dictionary based on the topic name
                    cout << "There is no posts to display. " << endl;                                       // Display the result status when there is no post inside that topic object
                }
                else {
                    topicDictionary.search(currentTopicName)->printChildren();                              // Printing all the post and reply belonging to that topic object
                }
                postOption = -1;                                                                            // Resetting back to the post menu
            }
            else if (postOption == 2) {                                                                     // Add post to the topic when the option is 2
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option from the user
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the status
                }
                   
                Post newPost = getNewPost();                                                                // Get the new post details through user input and store into a post object
                Topic* searchedTopic = topicDictionary.search(currentTopicName);                            // Searching for the topic based on the topic name (got from validateTopicNumber) and store the result into a topic pointer
                bool addPostSuccess = searchedTopic->addPost(newPost);                                      // Adding the post to the topic through the topic pointer

                if (addPostSuccess) {                                                                       
                    cout << "\n[SUCCESS] Post has been added." << endl;                                     // Displaying the corresponding status when the post is added successfully
                    savePostAddition(newPost, searchedTopic->getTopicName());                               // Saving the new post to the text file
                }
                else {
                    cout << "\n[FAILED] Post was not added." << endl;                                       // Displaying the corresponding status when the post is added unsuccessfully
                }
                postOption = -1;                                                                            // Resetting back to the post menu 
            }
            else if (postOption == 3) {                                                                     // Edit the post in the topic when the option is 3                                                    
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option for the topic table
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the status
                }
                
                Topic* chosenTopic = topicDictionary.search(currentTopicName);                              // Searching for the topic based on the topic name (got from validateTopicNumber) and store the result into a topic pointer
                chosenTopic->printChildren();                                                               // Display the list of post and reply for the user to choose (can only choose post through its number)

                if (!chosenTopic->getPostList()->isEmpty()) {                                               // Checking if there is any posts in the topic before continuing
                    LinkedList<Post>* postListPtr = topicDictionary.search(currentTopicName)->getPostList();// Storing the list of posts into a list pointer 
                      
                    int postIndex = -1;                                                                     // Storing the index of the post chosen from the post list into a integer variable
                    bool postSelectionSuccess = false;                                                      // Storing the status of the post selection into a boolen variable
                    while (!postSelectionSuccess) {                                                         // Iterating to get the post option
                        cout << char(175) << char(175) << " Select a post to continue:  ";          
                        cin >> postIndex;                                                                   // Getting the post option from the user
                        postSelectionSuccess = validatePostNumber(postIndex, *postListPtr);                 // Validating the post number chosen and return the status
                    }

                    LinkedList<Post>* postList = chosenTopic->getPostList();                                // Retrieving the list of post based on the topic name and storing into the list pointer
                    Post* chosenPost = postList->get(postIndex - 1);                                        // Retrieving the post object based on the post index (from user input) and storing into the post pointer
                    Post* anOldPost = postList->get(postIndex - 1);                                         // Retrieving the post object based on the post index (from user input) and storing into the post pointer --> repeated as this stores the old post object before it is being edited and is used when saving

                    string chosenPostTitle = chosenPost->getPTitle();                                       // Retrieving the post title based on the post index (from user input) and storing into the string variable
                    Post* postObjPtr = chosenTopic->searchPost(chosenPostTitle);                            // Retrieving the post object based on the post index (from user input) and storing into the string variable

                    if (postObjPtr->getPUser().getUsername() == currentUser.getUsername()) {                // Checking if the user (who has created the post) is the same as the current user signed in 
                        string currentPostTitle = postObjPtr->getPTitle();                                  // Storing the old post title into a string object
                        string currentPostDesc = postObjPtr->getPContent();                                 // Storing the old post content into a string object

                        string newPostTitle;                                                                // String variable to store new post title
                        string newPostDesc;                                                                 // String variable to store new post description 

                        cout << "Current Post Title: " << currentPostTitle << endl;                         // Displaying the old post title
                        cout << "Enter new Post Title: ";                                                   // Getting the post title from the user
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, newPostTitle);

                        cout << endl;

                        cout << "Current Post Content: " << currentPostDesc << endl;                        // Displaying the old post description
                        cout << "Enter new Post Content: ";                                                 // Getting the post description from the user
                        getline(cin, newPostDesc);

                        postObjPtr->setPTitle(newPostTitle);                                                // Setting the new post title into the post object
                        postObjPtr->setPContent(newPostDesc);                                               // Setting the new post description into the post object

                        cout << "[SUCCESS] Post updated!" << endl;                                          // Display the status of the post edit
                        savePostRevision(postObjPtr, anOldPost, currentTopicName);                          // Saving the updated post into the text file
                    }
                    else {
                        cout << "[FAILED] Unable to edit as you did not make this post." << endl;           // Display the result status
                    }
                }
                else {
                    cout << "[FAILED] There is no post to edit. Please try again." << endl;                 // Display the result status
                }
                postOption = -1;                                                                            // Resetting back to post menu
            }
            else if (postOption == 4) {                                                                     // Delete post from the topic when the option is 4
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option for the topic table
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the value
                }
                Topic* chosenTopic = topicDictionary.search(currentTopicName);                              // Searching for the topic based on the topic name (got from validation)
                chosenTopic->printChildren();                                                               // Display the list of post and reply for the user to choose from

                if (!chosenTopic->getPostList()->isEmpty()) {                                               // Checking if there is any posts in the topic before continuing
                    LinkedList<Post>* postListPtr = topicDictionary.search(currentTopicName)->getPostList();// Storing the list of posts into a list pointer 
                    
                    int postIndex = -1;                                                                     // Storing the index of the post chosen from the post list into a integer variable
                    bool postSelectionSuccess = false;                                                      // Storing the status of the post selection into a boolen variable
                    while (!postSelectionSuccess) {                                                         // Iterating to get the post option
                        cout << char(175) << char(175) << " Select a post to continue:  ";
                        cin >> postIndex;                                                                   // Getting the post option from the user
                        postSelectionSuccess = validatePostNumber(postIndex, *postListPtr);                 // Validating the post number chosen and return the status
                    }

                    Post* toBeDeleted = chosenTopic->getPostList()->get(postIndex - 1);                     // Retrieving the post object based on the post index (from user input) and storing into the post pointer

                    if (toBeDeleted->getPUser().getUsername() == currentUser.getUsername()) {               // Checking if the user (who has created the post) is the same as the current user signed in 
                        int replyNum = toBeDeleted->getRStack()->getSize();                                 // Getting the number of reply for removal during saving
                        savePostDeletion(toBeDeleted, currentTopicName, replyNum);                          // Removing the post in the text file and saving it
                        chosenTopic->removePost(postIndex - 1);                                             // Removing the post from the topic using the post index
                        cout << "[SUCCESS] Post has been deleted." << endl;                                 // Display the result status
                    }
                    else {
                        cout << "[FAILED] Unable to delete this post as you did not write this post." << endl;// Display the result status
                    }
                }
                else {
                    cout << "[FAILED] There is no post to delete. Please try again." << endl;               // Display the result status
                }
                postOption = -1;                                                                            // Resetting back to post menu
            }
            else if (postOption == 5) {                                                                     // Add reply in the post when the option is 5
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option for the topic table
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the status
                }
                
                Topic* chosenTopic = topicDictionary.search(currentTopicName);                              // Searching for the topic based on the topic name (got from validateTopicNumber) and store the result into a topic pointer
                if (!chosenTopic->getPostList()->isEmpty()) {                                               // Checking if there is any posts in the topic before continuing
                    topicDictionary.search(currentTopicName)->printChildren();                              // Display the list of post and reply for the user to choose (can only choose post through its number)

                    LinkedList<Post>* postListPtr = topicDictionary.search(currentTopicName)->getPostList();// Storing the list of posts into a list pointer 

                    int postIndex = -1;                                                                     // Storing the index of the post chosen from the post list into a integer variable
                    bool postSelectionSuccess = false;                                                      // Storing the status of the post selection into a boolen variable
                    while (!postSelectionSuccess) {                                                         // Iterating to get the post option
                        cout << char(175) << char(175) << " Select a post to continue:  ";
                        cin >> postIndex;                                                                   // Getting the post option from the user
                        postSelectionSuccess = validatePostNumber(postIndex, *postListPtr);                 // Validating the post number chosen and return the status
                    }

                    Post* chosenPost = postListPtr->get(postIndex - 1);                                     // Retrieving the post object based on the post index (from user input) and storing into the post pointer

                    cout << endl;

                    Reply newReply = getNewReply();                                                         // Getting the reply details through user input and storing into a reply object
                    bool addReplySuccess = chosenPost->addReply(newReply);                                  // Add reply to the post
                    if (addReplySuccess) {
                        cout << "\n[SUCCESS] Reply has been added." << endl;                                // Display the result status
                        saveReplyAddition(newReply, chosenPost, currentTopicName);                          // Saving the new reply into the text files
                    }
                    else {
                        cout << "\n[FAILED] Unable to add reply." << endl;                                  // Display the result status
                    }
                }
                else {
                    cout << "[FAILED] There is no post to reply to. Please try again." << endl;             // Display the result status
                }

                postOption = -1;                                                                            // Resetting back to the post menu
            }
            else if (postOption == 6) {                                                                     // Add reaction to the post when the option is 6
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option for the topic table
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the status
                }
                
                Topic* chosenTopic = topicDictionary.search(currentTopicName);                              // Searching for the topic based on the topic name (got from validateTopicNumber) and store the result into a topic pointer
                LinkedList<Post>* postList = chosenTopic->getPostList();                                    // Storing the list of post for that topic into a list pointer
                
                if (!chosenTopic->getPostList()->isEmpty()) {                                               // Checking if there is any posts in the topic before continuing
                    cout << endl;
                    chosenTopic->printChildren();                                                           // Display the list of post and reply for the user to choose (can only choose post through its number)
                    
                    int postIndex = -1;                                                                     // Storing the index of the post chosen from the post list into a integer variable
                    bool postSelectionSuccess = false;                                                      // Storing the status of the post selection into a boolen variable
                    while (!postSelectionSuccess) {                                                         // Iterating to get the post option
                        cout << char(175) << char(175) << " Select a post to continue:  ";
                        cin >> postIndex;                                                                   // Getting the post option from the user
                        postSelectionSuccess = validatePostNumber(postIndex, *postList);                    // Validating the post number chosen and return the status
                    }
                    
                    Post* chosenPost = postList->get(postIndex - 1);                                        // Retrieving the post object based on the post index (from user input) and storing into the post pointer (changed along with codes)
                    Post* anOldPost = postList->get(postIndex - 1);                                         // Retrieving the post object based on the post index (from user input) and storing into the post pointer (used for saving)

                    string chosenPostTitle = chosenPost->getPTitle();                                       // Retrieving the post title based on the post index (from user input) and storing into the string variable
                    Post* postObjPtr = chosenTopic->searchPost(chosenPostTitle);                            // Retrieving the post object based on the post title and storing into the post pointer

                    LinkedList<User> listOfUsersThatReacted = chosenPost->returnReactionUsers();            // Checking if the user has reacted before (based on the linked list of users stored in the post object)
                    if (listOfUsersThatReacted.search(currentUser.getUsername()) == nullptr) {              // Checking if the user exists in the list 
                        cout << endl;

                        int reactionOption = -999;                                                          // Prompt user for reaction (emoji)
                        while (!count(reactionOptions.begin(), reactionOptions.end(), reactionOption)) {    // Checking if the reaction option is within acceptable range
                            displayReactionsMenu();                                                         // Display the option menu for the user to choose
                            reactionOption = getOptionInput();                                              // Getting the user input for the reaction option
                        }

                        postObjPtr->addReaction(reactionOption);                                            // Add reaction to post
                        postObjPtr->addReactionUsers(currentUser);                                          // Add user to reaction users in the post 

                        savePostRevision(postObjPtr, anOldPost, currentTopicName);                          // Saving new updated post with reactions into the text file
                        cout << "\n[SUCCESS] Reaction added to post." << endl;                              // Display the result status
                    }
                    else {
                        cout << "\n[FAILED]You can only react once." << endl;                               // Display the result status
                    }
                }
                else {
                    cout << "\n[FAILED] There is no post to react to. Please try again." << endl;           // Display the result status
                }
                postOption = -1;                                                                            // Resetting back to post menu
            }
            else if (postOption == 7) {                                                                     // Search for post in the topic when the option is 7                               
                int topicSelected = -1;                                                                     // Storing the index of the topic chosen into a integer variable
                bool topicSelectionSuccess = false;                                                         // Storing the status of the topic selection into a boolean variable
                while (topicSelectionSuccess == false) {                                                    // Iterating to get the topic object
                    cout << "\n\n" << endl;
                    cout << "+------------------------------------------------------------------------+" << endl;
                    cout << "|  Choose a topic                                                        |" << endl;
                    topicDictionary.printWithCounter();                                                     // Display the table of topics for the user to choose
                    topicSelected = getOptionInput();                                                       // Getting the option for the topic table
                    topicSelectionSuccess = validateTopicNumber(topicSelected);                             // Validating the topic number chosen and return the status
                }
                
                Topic* chosenTopic = topicDictionary.search(currentTopicName);                              // Searching for the topic based on the topic name (got from validateTopicNumber) and store the result into a topic pointer

                string chosenPostTitle;                                                                     // String variable to store the title of the post to search
                cout << char(175) << char(175) << "Enter a post title: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');                            
                getline(cin, chosenPostTitle);                                                              // Getting the user input for the post title
                if (!chosenTopic->getPostList()->isEmpty()) {                                               // Checking if there is any posts in the topic before continuing
                    Post* postObjPtr = chosenTopic->searchPost(chosenPostTitle);                            // Retrieving the post object based on the post title (from user input) and storing into the post pointer
                    if (postObjPtr != NULL) {
                        postObjPtr->print(1);                                                               // Displaying the details of the post if found
                    }
                    else {
                        cout << "No post found!" << endl;                                                   // Display the result status
                    }
                }
                else {
                    cout << "There are no post in this topic" << endl;                                      // Display the result status
                }
                postOption = -1;                                                                            // Resetting back to the post menu

            }
            else {
                pageState = 1;                                                                              // Travel to the post menu options
                break;
            }
        }
    }

    return 0;
}


/*  ##########################################################################################
    ##     Initialize function for variables and load the data from the saved text file     ##
    ##########################################################################################   */
void init() {
    specialchar.push_back('!');                                                                             // Vector containing the special characters for new user registration (password) -> adding to the vector
    specialchar.push_back('@');                                                                             
    specialchar.push_back('#');
    specialchar.push_back('$');
    specialchar.push_back('%');
    specialchar.push_back('&');

    mainOptions.push_back(1);                                                                               // Vector containing the list of acceptable number range for the topic options -> adding to the vector
    mainOptions.push_back(2);
    mainOptions.push_back(3);
    mainOptions.push_back(4);
    mainOptions.push_back(5);

    postOptions.push_back(1);                                                                               // Vector containing the list of acceptable number range for the post options -> adding to the vector
    postOptions.push_back(2);
    postOptions.push_back(3);
    postOptions.push_back(4);
    postOptions.push_back(5);
    postOptions.push_back(6);
    postOptions.push_back(7);
    postOptions.push_back(8);

    reactionOptions.push_back(1);                                                                           // Vector containing the list of acceptable number range for the reactions options -> adding to the vector
    reactionOptions.push_back(2);
    reactionOptions.push_back(3);
    reactionOptions.push_back(4);
    reactionOptions.push_back(5);


    currentUser = User();                                                                                   // Initializing an empty user (used to store the current user signed in) with empty username and password
    currentUser.setUsername("");
    currentUser.setPassword("");

    currentTopicName = "";                                                                                  // Initializing an empty string to store the topic name (required for loading post and reply)
    pageState = 0;

    fs::create_directories("./Assets/Content");                                                             // Creating the directories to store the text files if there is none currently
    fs::create_directories("./Assets/Users");

    vector<string> linesOfContent;                                                                          // Vector to store the split strings (delimiter : \\)

    
    std::string path = "Assets/Content";                                                                    
    for (const auto& entry : fs::directory_iterator(path)) {                                                // Getting each text file from the stated path and extracting the topic name from the filename
        string nameOfFile = entry.path().string();
        string delimiter1 = "Content\\";
        string delimiter2 = ".txt";
        size_t start_pos = nameOfFile.find(delimiter1) + delimiter1.length();
        size_t end_pos = nameOfFile.find(delimiter2);
        string topicResult = nameOfFile.substr(start_pos, end_pos - start_pos);
        
        Topic newSavedTopic = Topic();                                                                      // Adding the topic to the topic dictionary
        newSavedTopic.setTopicName(topicResult);
        topicDictionary.add(topicResult, newSavedTopic);

        if (entry.is_regular_file() && entry.path().extension() == ".txt") {                                // Getting the content out of the text file
            ifstream inputFile(entry.path());
            if (inputFile.is_open()) {
                string line;
                while (std::getline(inputFile, line)) {
                    linesOfContent.push_back(line);
                }
                inputFile.close();
            }
        }

        int postCounter = 0;                                                                                // Used to find the post index when adding reply

        for (string contentLine : linesOfContent) {
            if (contentLine.rfind("[Post]", 0) == 0) {                                                      // Check if the line belongs to a Post object
                string toRemove = "[Post]";                                                                 // Remove '[Post]' from the string

                size_t pos = contentLine.find(toRemove);                                                    // Find the position of the string to remove
                if (pos != std::string::npos) {
                    contentLine.erase(pos, toRemove.length());                                              // Erase the string from the original string
                }

                string primarydelimiter = "\\";                                                             
                vector<string> postDetails;                                                                 // Vector to store the split strings                                   
                size_t prev = 0;
                size_t next = 0;

                while ((next = contentLine.find(primarydelimiter, prev)) != string::npos) {                 // Splitting the string with the delimiter - (\\)
                    postDetails.push_back(contentLine.substr(prev, next - prev));
                    prev = next + primarydelimiter.size();
                }
                postDetails.push_back(contentLine.substr(prev));

                Post extractPost = Post();                                                                  // Create an empty post object to store the details of the post

                string postTitle = postDetails[0];                                                          
                extractPost.setPTitle(postTitle);                                                           // Store the first string as the post title

                string postDescription = postDetails[1];
                extractPost.setPContent(postDescription);                                                   // Store the second string as the post content

                string postDateTime = postDetails[2];
                extractPost.setPDateTime(postDateTime);                                                     // Store the third string as the post datetime

                User postUser = User();
                string postUsername = postDetails[3];
                string postPassword = postDetails[4];
                postUser.setUsername(postUsername);
                postUser.setPassword(postPassword);
                extractPost.setPUser(postUser);                                                             // Store the fourth and fifth string as the post user

                string postReactions = postDetails[5];                                                      // Store the sixth string as the post reactions
                string secondarydelimiter = ",";
                vector<string> reactionDetails;
                size_t thePrev = 0;
                size_t theNext = 0;

                while ((theNext = postReactions.find(secondarydelimiter, thePrev)) != string::npos) {       // split the string with the delimiter (,)
                    reactionDetails.push_back(postReactions.substr(thePrev, theNext - thePrev));
                    thePrev = theNext + secondarydelimiter.size();
                }
                reactionDetails.push_back(postReactions.substr(thePrev));
                
                extractPost.getReactions().get(0)->setCount(stoi(reactionDetails[0]));                      // Storing the relevant reactions into the array of reactions
                extractPost.getReactions().get(1)->setCount(stoi(reactionDetails[1]));
                extractPost.getReactions().get(2)->setCount(stoi(reactionDetails[2]));
                extractPost.getReactions().get(3)->setCount(stoi(reactionDetails[3]));
                extractPost.getReactions().get(4)->setCount(stoi(reactionDetails[4]));

                if (postDetails.size() > 6) {                                                               // Store the seventh string as the (post) reaction users
                    string postReactionsUser = postDetails[6];
                    string tertiarydelimiter = "<>";
                    vector<string> reactionUserDetails;                                                     // Vector to store the split strings 
                    size_t aPrev = 0;
                    size_t aNext = 0;

                    while ((aNext = postReactionsUser.find(tertiarydelimiter, aPrev)) != string::npos) {    // split the string with the delimiter (<>)
                        reactionUserDetails.push_back(postReactionsUser.substr(aPrev, aNext - aPrev));
                        aPrev = aNext + tertiarydelimiter.size();
                    }
                    reactionUserDetails.push_back(postReactionsUser.substr(aPrev));

                    for (string userdetails : reactionUserDetails) {                                        // Storing the username and password extracted into user object and add them to the list of reaction users
                        string quaternarydelimiter = "|";
                        size_t pos = userdetails.find(quaternarydelimiter);
                        string usernameString = userdetails.substr(0, pos);
                        string passwordString = userdetails.substr(pos + quaternarydelimiter.length());
                        User reactionUser = User();
                        reactionUser.setUsername(usernameString);
                        reactionUser.setPassword(passwordString);
                        extractPost.addReactionUsers(reactionUser);
                    }
                }

                topicDictionary.search(topicResult)->addPost(extractPost);                                  // Add post to the topic in the topic dictionary
                postCounter++;
            }
            else {
                                                                                                            // Check if the line belongs to a Reply object
                string delimiter = "\\";
                vector<string> replyDetails;                                                                // Vector to store the split strings
                size_t prev = 0;
                size_t next = 0;

                string toRemove = "[Reply]";                                                                // Removing '[Reply]' from the string

                size_t pos = contentLine.find(toRemove);                                                    // Find the position of the string to remove
                if (pos != std::string::npos) {
                    contentLine.erase(pos, toRemove.length());                                              // Erase the string from the original string
                }

                while ((next = contentLine.find(delimiter, prev)) != string::npos) {                        // split the string with the delimiter (\\)
                    replyDetails.push_back(contentLine.substr(prev, next - prev));
                    prev = next + delimiter.size();
                }
                replyDetails.push_back(contentLine.substr(prev));

                Reply extractReply = Reply();                                                               // Create an empty Reply object to store the reply details

                string replyTitle = replyDetails[0];
                extractReply.setRTitle(replyTitle);                                                         // Store the first string as the reply title

                string replyDescription = replyDetails[1];
                extractReply.setRContent(replyDescription);                                                 // Store the second string as the reply description

                string replyDateTime = replyDetails[2];
                extractReply.setRDateTime(replyDateTime);                                                   // Store the third string as the reply datetime

                User replyUser = User();
                string postUsername = replyDetails[3];
                string postPassword = replyDetails[4];
                replyUser.setUsername(postUsername);
                replyUser.setPassword(postPassword);
                extractReply.setRUser(replyUser);                                                           // Store the fourth and fifth string as the reply user

                Post* postPtr = topicDictionary.search(topicResult)->getPostList()->get(postCounter-1);     // Add reply to the post in the topic dictionary
                postPtr->addReply(extractReply);

            }
        }
    }

    ifstream userfile;                                                                                      // Getting the users and storing them into a user list
    userfile.open("Assets/Users/userlist.txt");
    string line;
    while (getline(userfile, line)) {                                                                       // Splitting the string with the delimiter (,)
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




/*  #####################################################################################
    ##     Display the options for the topic menu such as add topic and view topic     ##
    ##     1. View topics in the topic dictionary                                      ##
    ##     2. Add topics to the topic dictionary                                       ##
    ##     3. Search for the current users in the user list                            ##
    ##     4. Search topics in the topic dictionary                                    ##
    ##     5. Display the post menu                                                    ##
    ##     0. Exit the program                                                         ##
    #####################################################################################   */
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



/*  ##################################################################################
    ##     Display the options for the post menu such as add post and add reply     ##
    ##     1. View post and reply in the topic                                      ##
    ##     2. Add post to the topic                                                 ##
    ##     3. Edit the post in the topic                                            ##
    ##     4. Delete post from the topic                                            ##
    ##     5. Add reply to the post                                                 ##
    ##     6. Add reaction to the post                                              ##
    ##     7. Search for post in the topic                                          ##
    ##     8. Display the topic menu                                                ##
    ##     0. Exit the program                                                      ##
    ##################################################################################   */
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



/*  ########################################################
    ##     Display the options for the reactions menu     ##
    ##     1. Upvote (like)                               ##
    ##     2. Downvote (dislike)                          ##
    ##     3. Happy Emoji                                 ##
    ##     4. Sad Emoji                                   ##
    ##     5. Chock Emoji                                 ##
    ########################################################   */
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



/*  ################################################################################
    ##     Display the options for the login menu such as sign in and sign up     ##
    ##     1. Sign in                                                             ##
    ##     2. Sign up                                                             ##
    ##     0. Exit the program                                                    ##
    ################################################################################   */
void displayMainMenu() {
    cout << "+------------------------------------------------------------------------+" << endl;
    cout << "|  Options                                                               |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << "|  1  | Sign In         |  2  | Sign Up         |  0  | Exit Program     |" << endl;
    cout << "+-----+-----------------+-----+-----------------+-----+------------------+" << endl;
    cout << endl;
};



/*  ┌────────────────────────────────────────────────────────────────────────┐
    |                                                                        |
    |                      Welcome [firstUsername] to                        |
    |                        Discussion Forum 2023                           |
    |                                                                        |
    └────────────────────────────────────────────────────────────────────────┘  */
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

/*  ####################################################################################
    ##     Retrieve the user's username and password to log in for authentication     ##
    ####################################################################################   */
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
    if (validateUser(username, password)) {                                                                 // Checking the username and password inputted corresponds to any of the users in the list of users 
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



/*  ##############################################################################################################
    ##     Retrieve the user's username and password to register for new account to authenticate themselves     ##
    ##############################################################################################################   */
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
        usernameClear = validateUsernameInput(username);                                                    // Get the user input for the username and validate it (check if it exist in the user list)
    }

    while (passwordClear == false) {
        cout << char(175) << char(175) << " New Password:  ";
        cin >> password;
        cout << endl;
        passwordClear = validatePasswordInput(password);                                                    // Get the user input for the password and validate it (check if it exist in the user list)
    }
    currentUser.setUsername(username);                                                                      // Set the global user with the username and password details
    currentUser.setPassword(password);
    saveUsers(currentUser);                                                                                 // Saving user to the text files

    return true;
}

/*  #########################################################################################################################
    ##     Retrieve the user's integer input from the menu options (Topic Menu, Post Menu, Reaction Menu, Log In Menu)     ##
    #########################################################################################################################   */
int getOptionInput() {
    bool isInteger = false;
    string input;
    while (!isInteger) {
        cout << char(175) << char(175) << " Select an option to continue:  ";
        cin >> input;
        cout << endl;
        isInteger = checkInteger(input);
        if (checkInteger(input) == false) {
            cout << "[ERROR] Only (integer) numbers are accepted. Pls try again." << endl;                  // Checking if the input given by the user is a positive numerical digit
        }
    }

    return stoi(input);                                                                                     // tranforming the string to an int and returning it
}



/*  #################################################
    ##     Check if the given input is a digit     ##
    #################################################   */
bool checkInteger(string input)
{
    bool isNeg = false;
    int itr = 0;
    if (input.size() == 0)                                                                                  // Check if there is any input
        return false;
    if (input[0] == '-')                                                                                    // Check if input is negative
    {
        isNeg = true;
        itr = 1;
    }

    for (int i = itr; i < (int)input.size(); i++)                                                           // Check if each position of the input is a positive numerical digit
    {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}



/*  #######################################################################################
    ##     Checking if the user details correspond to the users inside the user list     ##
    #######################################################################################   */
bool validateUser(string usernameInput, string passwordInput) {
    User tempUser = User();
    tempUser.setUsername(usernameInput);                                                
    tempUser.setPassword(passwordInput);
    return userList.searchFound(tempUser);                                                                  // Check if the username log in details matches with that in the user list
}


/*  #############################################################################
    ##     Checking if the username string mets the necessary requirements     ##
    #############################################################################   */
bool validateUsernameInput(string u) {
    if (u.length() > 30 || u.length() < 5) {
        cout << "[ERROR] Your username needs to be between 5 to 30 characters. Please try again.\n" << endl;            // Checking if the string input between 5 to 30 characters
        return false;
    }
    for (char c : u) {
        if (iswalnum(c) == false) {
            cout << "[ERROR] Your username can only consists of alphabets and numbers. Please try again.\n" << endl;    // Checking if the string input is alphanumeric
            return false;
        }
    }
    return true;
}



/*  #############################################################################
    ##     Checking if the password string mets the necessary requirements     ##
    #############################################################################   */
bool validatePasswordInput(string p) {
    if (p.length() > 20 || p.length() < 8) {
        cout << "[ERROR] Your password needs to be between 8 to 20 characters. Please try again.\n" << endl;                                                // Checking if the string input between 8 to 20 characters
        return false;
    }
    if (checkSpecialCharacters(p) == false) {
        cout << "[ERROR] Your password need to include these special characters - !@#$%&. Please try again.\n" << endl;                                     // Checking if the string input contains special characters
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
            cout << "[ERROR] Your password can only consists of alphabets, numbers and these special characters - !@#$%&. Please try again.\n" << endl;     // Checking if the string input is alphanumeric
            return false;
        }
    }
    return true;
}



/*  ###############################################################################################################
    ##     Checking if the input string contains any special characters (from the vector<string> specialchar)    ##
    ###############################################################################################################   */
bool checkSpecialCharacters(string p) {
    for (char character1 : p) {
        for (char character2 : specialchar) {
            if (character1 == character2) {                                                                                                                 //Check if any part of the string input contains special characters
                return true;
            }
        }
    }
    return false;
}



/*  #####################################################################################
    ##     Checking if the topic number is a digit and return a topic when searched    ##
    #####################################################################################   */
bool validateTopicNumber(int topicNum) {
    if (isdigit(topicNum)) {
        return false;
    }
    else if (topicNum <= 0) {
        return false;
    }
    currentTopicName = topicDictionary.returnSearchOption(topicNum).getTopicName();                         // Checking if the topic index retrieve any topic object from the topic dictionary
    if (currentTopicName != "") {
        return true;
    }
    else {
        cout << "[ERROR] Invalid number inputted. Pls try again." << endl;
        return false;
    }
};



/*  ########################################################################
    ##     Checking if the input string mets the necessary requirement    ##
    ########################################################################   */
bool validateTopicName(string nameOfTopic) {
    if (iswalnum(nameOfTopic[0]) && nameOfTopic.length() >= 1 && nameOfTopic.length() <= 60) {              // Checking if the new topic name does not contain spacing at the start and is between 1 to 60 characters
        return true;
    }
    else {
        cout << "The first character needs to be an alphanumeric character and only 1 to 60 characters are allowed." << endl;
        return false;
    }
}



/*  ##############################################################################
    ##     Retrieve the user's input for the post title and post description    ##
    ##############################################################################   */
Post getNewPost() {
    string title;
    string description;
    Post newPost = Post();
    cout << char(175) << char(175) << " Enter post title:  ";                                               // Get user input for the new post title
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);                                                                                    
    cout << char(175) << char(175) << " Enter post description:  ";                                         // Get user input for the new post description
    getline(cin, description);                                                                              
    newPost.setPTitle(title);                                                                               // Populate the post object with the necessary detials
    newPost.setPContent(description);
    newPost.setPDateTime();
    newPost.setPUser(currentUser);
    return newPost;                                                                                         
}



/*  ###############################################################################
    ##     Retrieve the user's input for the reply title and post description    ##
    ###############################################################################   */
Reply getNewReply() {
    string title;
    string description;
    Reply newReply = Reply();
    cout << char(175) << char(175) << " Enter reply title:  ";                                              // Get the user input for the title of the reply
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);
    cout << char(175) << char(175) << " Enter reply description:  ";                                        // Get the user input for the content of the reply                       
    getline(cin, description);
    newReply.setRTitle(title);                                                                              // Populate the reply object with the necessary detials
    newReply.setRContent(description);
    newReply.setRDateTime();
    newReply.setRUser(currentUser);
    return newReply;
}



/*  ################################################################
    ##     Edit the current post and returning the post object    ##
    ################################################################   */
Post editCurrentPost() {
    return Post();
}


/*  #########################################################################
    ##     Checking if the input option mets the necessary requirements    ##
    #########################################################################   */
bool validatePostNumber(int postNum, LinkedList<Post> postListing) {

    if (isdigit(postNum)) {                                                                                 // Checking if the post index is a digit
        return false;
    }
    else if (postNum <= 0) {
        cout << "[ERROR] Invalid number inputted. Pls try again." << endl;                                  // Checking if the post index retrieve any post object from the post list
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


/*  ###########################################################################
    ##     Saving the new topic into the directory (folder) as text files    ##
    ###########################################################################   */
void saveTopicAddition(Topic t) {
    //creating file for writing
    string filename = "Assets/Content/" + t.getTopicName() + ".txt";                                        // Save the topic name as the file name with the .txt extension
    ofstream file;
    file.open(filename.c_str());                                                                            // Open the file
    file.close();                                                                                           // Close the file
};



/*  ##############################################################################
    ##     Saving the new post into the text file with the name of the topic    ##
    ##############################################################################   */
void savePostAddition(Post p, string topicName) {
    fstream file;
    string filename = "Assets/Content/" + topicName + ".txt";                                               // Open the file for reading and writing
    file.open(filename, ios::in | ios::out | ios::app);
    
    vector<string> contents;                                                                                // Read the existing contents of the file into a vector of strings
    string line;
    while (getline(file, line)) {
        contents.push_back(line);
    }

    string new_string = "[Post]" + p.getPTitle() + "\\" + p.getPContent() + "\\" + p.getPDateTime() + "\\" + p.getPUser().getUsername() + "\\" + p.getPUser().getPassword() + "\\";         // Add the new string with the post details to the end of the vector
    for (int i = 0; i < p.getReactions().getLength(); i++) {                                                // Looping through to store the reactions into a string                                                                                                                     
        Reaction* react = p.getReactions().get(i);
        new_string = new_string + to_string(react->getEmojiCount()) + ",";
    }
    new_string.pop_back();                                                                                  //removing the last symbol (,)
    new_string = new_string + "\\";
    if (p.returnReactionUsers().getLength() != 0) {                                                         // Looping through to store the reaction users into a string
        for (int i = 0; i < p.returnReactionUsers().getLength(); i++) {
            User* us = p.returnReactionUsers().get(i);
            new_string = new_string + us->getUsername() + "|" + us->getPassword() + "<>";
        }
        new_string.pop_back();                                                                              //removing the last symbol (>)
        new_string.pop_back();                                                                              //removing the last symbol (<)
    }
    else {
        new_string.pop_back();                                                                              //removing the last symbol (\)
    }
    contents.push_back(new_string);

    file.close();                                                                                           // Close the file

    file.open(filename, ios::out | ios::trunc);                                                             // Open the file again in write mode

    for (const string& s : contents) {                                                                      // Write the contents of the vector to the file
        file << s << endl;
    }

    file.close();                                                                                           // Close the file
};



/*  ######################################################################################
    ##     Removing the post and reply from the text file with the name of the topic    ##
    ######################################################################################   */
void savePostDeletion(Post* p, string topicName, int replyNum) {
    vector<string> lines;
    string filename = "Assets/Content/" + topicName + ".txt";                                               // Open the file for reading and writing
    ifstream inputFile(filename);
    if (inputFile.is_open()) {                                                                              
        string line;
        while (std::getline(inputFile, line)) {                                                             // Read the existing contents of the file into a vector of strings
            lines.push_back(line);
        }
        inputFile.close();                                                                                  // Close the file
    
    }

    string old_string = "[Post]" + p->getPTitle() + "\\" + p->getPContent() + "\\" + p->getPDateTime() + "\\" + p->getPUser().getUsername() + "\\" + p->getPUser().getPassword() + "\\";  // Add the new string with the post details 
    for (int i = 0; i < p->getReactions().getLength(); i++) {                                               // Looping through to store the reactions into a string
        Reaction* react = p->getReactions().get(i);
        old_string = old_string + to_string(react->getEmojiCount()) + ",";
    }

    old_string.pop_back();                                                                                  //removing the last symbol (,)
    old_string = old_string + "\\";
    if (p->returnReactionUsers().getLength() != 0) {
        for (int i = 0; i < p->returnReactionUsers().getLength(); i++) {                                    // Looping through to store the reaction users into a string
            User* us = p->returnReactionUsers().get(i);
            old_string = old_string + us->getUsername() + "|" + us->getPassword() + "<>";
        }
        old_string.pop_back();                                                                              //removing the last symbol (>)
        old_string.pop_back();                                                                              //removing the last symbol (<)
    }
    else {
        old_string.pop_back();                                                                              //removing the last symbol (\)
    }

    int numOfLines;                                                                                         // Obtain the number of replies to remove
    if (replyNum == 0){
        numOfLines = 1;
    }
    else {
        numOfLines = replyNum + 1;
    }
    

    for (int i = 0; i < (int)lines.size(); i++) {                                                           // Removing the post and reply lines
        if (lines[i].find(old_string) != string::npos) {
            lines.erase(lines.begin() + i, lines.begin() + i + numOfLines);
            break;
        }
    }
    ofstream outputFile(filename);
    if (outputFile.is_open()) {                                                                             // Open the file
        for (const auto& line : lines) {
            outputFile << line << endl;                                                                     // Write the contents of the vector to the file
        }
        outputFile.close();                                                                                 // Close the file
    }
};





/*  ################################################################################
    ##     Saving the new reply into the text files with the name of the topic    ##
    ################################################################################   */
void saveReplyAddition(Reply r, Post *p, string topicName) {
    vector<string> lines;
    string filename = "Assets/Content/" + topicName + ".txt";                                               // Open the file for reading and writing
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {                                                                  // Read the existing contents of the file into a vector of strings
            lines.push_back(line);
        }
        inputFile.close();                                                                                  // Close the file
    }
    
    string targetLine = "[Post]" + p->getPTitle() + "\\" + p->getPContent() + "\\" + p->getPDateTime() + "\\" + p->getPUser().getUsername() + "\\" + p->getPUser().getPassword() + "\\";    // Find the line insert the new string
    for (int i = 0; i < p->getReactions().getLength(); i++) {                                               // Looping through to store the reactions into a string
        Reaction* react = p->getReactions().get(i);
        targetLine = targetLine + to_string(react->getEmojiCount()) + ",";
    }

    targetLine.pop_back(); 
    targetLine = targetLine + "\\";
    if (p->returnReactionUsers().getLength() != 0) {
        for (int i = 0; i < p->returnReactionUsers().getLength(); i++) {                                    // Looping through to store the reaction users into a string
            User* us = p->returnReactionUsers().get(i);
            targetLine = targetLine + us->getUsername() + "|" + us->getPassword() + "<>";
        }

        targetLine.pop_back(); 
        targetLine.pop_back(); 
    }
    else {
        targetLine.pop_back(); 
    }

    int targetIndex = -1;
    for (int i = 0; i < (int)lines.size(); i++) {
        if (lines[i] == targetLine) {
            targetIndex = i;
            break;
        }
    }
    

    int num_of_line = p->getRStack()->getSize();

    string new_string = "[Reply]" + r.getRTitle() + "\\" + r.getRContent() + "\\" + r.getRDateTime() + "\\" + r.getRUser().getUsername() + "\\" + r.getRUser().getPassword();       // Insert the new string after the target line
    if (targetIndex != -1) {
        lines.insert(lines.begin() + targetIndex + num_of_line, new_string);
    }
    ofstream outputFile(filename);
    if (outputFile.is_open()) {                                                                             // Open the file to write
        for (const auto& line : lines) {
            outputFile << line << '\n';                                                                     // Write the contents of the vector to the file
        }
        outputFile.close();                                                                                 // Close the file
    }
};




/*  ###################################################################################
    ##     Saving the updated post into the text files with the name of the topic    ##
    ###################################################################################   */
void savePostRevision(Post *newPost, Post* oldPost, string topicName) {
    vector<string> lines;
    string filename = "Assets/Content/" + topicName + ".txt";
    ifstream inputFile(filename);
    if (inputFile.is_open()) {                                                                              // Open the file for reading and writing
        string line;
        while (getline(inputFile, line)) {                                                                  // Read the existing contents of the file inot a vector of things
            lines.push_back(line);
        }
        inputFile.close();                                                                                  // Close the file
    }
    for (auto& line : lines) {
        string oldString = "[Post]" + oldPost->getPTitle() + "\\" + oldPost->getPContent() + "\\" + oldPost->getPDateTime() + "\\" + oldPost->getPUser().getUsername() + "\\" + oldPost->getPUser().getPassword() + "\\";       // Gather all the OLD post details into a string
        for (int i = 0; i < oldPost->getReactions().getLength(); i++) {                                     // Looping through to store the reactons into the string                              
            Reaction* react = oldPost->getReactions().get(i);
            oldString = oldString + to_string(react->getEmojiCount()) + ",";
        }
        oldString.pop_back(); 
        oldString = oldString + "\\";
        if (oldPost->returnReactionUsers().getLength() != 0) {
            for (int i = 0; i < oldPost->returnReactionUsers().getLength(); i++) {                          // Looping through to store the reacton users into the string     
                User* us = oldPost->returnReactionUsers().get(i);
                oldString = oldString + us->getUsername() + "|" + us->getPassword() + "<>";
            }
            oldString.pop_back(); 
            oldString.pop_back(); 
        }
        else {
            oldString.pop_back(); 
        }
        

        string newString = "[Post]" + newPost->getPTitle() + "\\" + newPost->getPContent() + "\\" + newPost->getPDateTime() + "\\" + newPost->getPUser().getUsername() + "\\" + newPost->getPUser().getPassword() + "\\";       // Gather all the NEW post details into a string
        for (int i = 0; i < newPost->getReactions().getLength(); i++) {                                     // Looping through to store the reactons into the string 
            Reaction* react = newPost->getReactions().get(i);
            newString = newString + to_string(react->getEmojiCount()) + ",";
        }
        newString.pop_back(); 
        newString = newString + "\\";
        if (newPost->returnReactionUsers().getLength() != 0) {                                              // Looping through to store the reacton users into the string     
            for (int i = 0; i < newPost->returnReactionUsers().getLength(); i++) {
                User* us = newPost->returnReactionUsers().get(i);
                newString = newString + us->getUsername() + "|" + us->getPassword() + "<>";
            }
            newString.pop_back(); 
            newString.pop_back(); 
        }
        else {
            newString.pop_back();
        }
        
        if (line.find(oldString) != string::npos) {
            line.replace(line.find(oldString), oldString.length(), newString);                              // Replace the old string with the new string in the text file
        }
    }
    ofstream outputFile(filename);
    if (outputFile.is_open()) {                                                                             // Open the file for writing purposes
        for (const auto& line : lines) {
            outputFile << line << endl;                                                                     // Write the contents of the vector to the file
        }
        outputFile.close();                                                                                 // Close the file
    }
};


/*  ##################################################
    ##     Saving the users into the text files     ##
    ##################################################   */
void saveUsers(User u) {
    string filename = "Assets/Users/userlist.txt";                                                          
    ofstream file;
    file.open(filename.c_str(), ios::app);                                                                  // Open the user file 


    if (file.is_open()) {
        string inputUser = u.getUsername() + "," + u.getPassword();                                         // Add new user string into the text file
        file << inputUser << endl;
        file.close();                                                                                       // Close the file
    }
    else {
        std::cout << "Error in opening file." << std::endl;
    }
};


void exitProgram() {
    cout << "Exiting program. See you again!" << endl;
    exit(0);
}