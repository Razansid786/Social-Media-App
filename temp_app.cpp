#ifndef SOCIALNETWORKAPP_HPP
#define SOCIALNETWORKAPP_HPP

#include <iostream>
#include "User.h"
#include "Page.h"
#include "Post.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class SocialNetworkApp {
private:
    User* currentUser;
    User** users;
    Page** pages;
    Post** posts; 
    int maxUsers;
    int maxPages;
    int maxPosts;
    int numUsers;
    int numPosts;
    int numPages;

public:
    SocialNetworkApp(int maxUsers = 20, int maxPages = 12, int maxPosts = 12)
        : currentUser(nullptr), maxUsers(maxUsers), maxPages(maxPages), maxPosts(maxPosts), numUsers(0), numPosts(0), numPages(0) {
        users = new User*[maxUsers];
        pages = new Page*[maxPages];
        posts = new Post*[maxPosts];
        initializeUsersFromFile("Users.txt");
        initializePagesFromFile("Pages.txt");
    }
    ~SocialNetworkApp(){};
    //getters
    int getMaxUsers() {return maxUsers;}
    int getMaxPages() {return maxPages;}
    User** getUsers() {return users;}
    Page** getPage() {return pages;}
    void run()
    {
        // User u1("u1","razan");
        // currentUser = &u1;
        // cout<<currentUser->getName()<<endl;
        // Posts[1] = new Post;
        // Posts[1]->setId("post1");
        // cout<<Posts[1]->getId()<<endl;
        // likePost("post1");

        /* for (int i = 0; i < maxUsers; i++)
        {
            cout<<users[i]->getId()<<endl;
        } */

        for (int i = 0; i < maxPages; i ++)
        {
            cout<<pages[i]->getId()<<endl;
        }

    }
    void setCurrentUser(const string& userId)
    {
        for (int i = 0; i < maxUsers; ++i) {
            if (users[i] != nullptr && users[i]->getId() == userId) {
                currentUser = users[i];
                return;
            }
        }
        // If the user is not found, set currentUser to nullptr
        currentUser = nullptr;
    }

    void viewHome(){};

    void likePost(const string& postId){
            // Check if the currentUser is valid
        if (currentUser == nullptr) {
            cout << "Error: Current user not set." << endl;
            return;
        }

        // Find the post with the given postId
        Post* postToLike = nullptr;
        for (int i = 0; i < maxPosts; ++i) {
            if (posts[i] != nullptr && posts[i]->getId() == postId) {
                postToLike = posts[i];
                break;
            }
        }

        // Check if the post was found
        if (postToLike == nullptr) {
            cout << "Error: Post with ID " << postId << " not found." << endl;
            return;
        }

        // Check if the post has already been liked by the currentUser
        for (int i = 0; i < postToLike->getCurrLikedBy(); ++i) {
            if (postToLike->getLikedBy()[i] == currentUser) {
                cout << "You have already liked this post." << endl;
                return;
            }
        }

        // Check if the post has reached the maximum number of likes
        if (postToLike->getCurrLikedBy() >= postToLike->getMaxLikedBy()) {
            cout << "Error: This post has reached the maximum number of likes." << endl;
            return;
        }

        // Like the post
        postToLike->addLike(currentUser);
        cout << "Post liked successfully." << endl;
    }
            
    void viewLikes(const string& postId){};
    void commentOnPost(const string& postId, const string& commentText){};
    void viewPost(const string& postId){};
    void shareMemory(const string& postId, const string& memoryText){};
    void viewUserTimeline(const string& userId){};
    void viewFriendList(const string& userId){};
    void viewPage(const string& pageId){};

            // File handeling for user
    void addUser(User* newUser) {
        // Check if there is enough space to add a new user
        if (numUsers < maxUsers) {
            // Add the new user to the array
            users[numUsers] = newUser;
            // Increment the count of current users
            numUsers++;
        } else {
            // Handle the case where the array is full
            cout << "Error: Maximum number of users reached." << endl;
        }
    }
    void initializeUsersFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string userId, userName;
            iss >> userId >> userName;

            // Create a new User object
            User* newUser = new User(userId, userName);

            // Parse friends
            string friendId;
            while (iss >> friendId && friendId != "-1") {
                // Add friend to the user
                newUser->addFriend(friendId);
            }

            // Parse liked pages
            string pageId;
            while (iss >> pageId && pageId != "-1") {
                // Add liked page to the user
                newUser->addLikedPage(pageId);
            }

            // Store the new user in the users array
            // (You need to implement a method to add users to the array)
            addUser(newUser);
        }

        file.close();
    }

                // File handeling for Pages

void addPage(Page* newPage) {
    // Check if there is enough space to add a new page
    if (numPages < maxPages) {
        // Add the new page to the array
        pages[numPages++] = newPage;
        cout << "Page added: " << newPage->getId() << " - " << newPage->getTitle() << endl; // Debugging output
    } else {
        // Handle the case where the array is full
        cout << "Error: Maximum number of pages reached. Page not added: " << newPage->getId() << endl;
        delete newPage; // Delete the newly created page since it's not added to the array
    }
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void initializePagesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Trim leading and trailing whitespace from the line
        line = trim(line);
        if (line.empty()) {
            continue; // Skip empty lines
        }

        istringstream iss(line);
        string pageId, pageTitle;
        if (!(iss >> pageId) || !getline(iss >> ws, pageTitle)) {
            cout << "Error: Invalid data format in file." << endl;
            continue;
        }

        // Create a new Page object
        Page* newPage = new Page(pageId, nullptr, pageTitle);

        // Add the new page to the pages array
        addPage(newPage);
    }

    file.close();
}

        //File handeling for Posts

void initializePostsFromFile(const string& filename, Post** posts, int& numPosts, const int maxPosts, User** users, const int numUsers, Page** pages, const int numPages) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Parse post data
        string postId, description, activityTypeStr, activityValue, ownerId;
        int day, month, year, activityType;
        
        istringstream iss(line);
        iss >> postId >> day >> month >> year;
        getline(file, description);
        getline(file, line);
        istringstream activityStream(line);
        activityStream >> activityTypeStr >> ws;
        getline(activityStream, activityValue);
        activityType = stoi(activityTypeStr);
        getline(file, ownerId);

        // Create a new Post object
        Post* newPost = new Post(postId, description, day, month, year);
        newPost->addActivity(activityType, activityValue);

        // Determine owner (user or page) and set it
        bool isPageOwner = false;
        for (int i = 0; i < numUsers; ++i) {
            if (users[i]->getId() == ownerId) {
                newPost->setOwner(users[i]);
                break;
            }
        }
        if (!newPost->getOwner()) {
            for (int i = 0; i < numPages; ++i) {
                if (pages[i]->getId() == ownerId) {
                    newPost->setOwner(pages[i]);
                    isPageOwner = true;
                    break;
                }
            }
        }
        newPost->setIsPageOwner(isPageOwner);

        // Read liked users/pages
        while (getline(file, line)) {
            if (line == "-1") {
                break; // End of liked users/pages
            }
            if (isPageOwner) {
                // Assuming the line contains the ID of the user who liked the post
                for (int i = 0; i < numUsers; ++i) {
                    if (users[i]->getId() == line) {
                        newPost->addLikedBy(users[i]);
                        break;
                    }
                }
            } else {
                // Assuming the line contains the ID of the page that liked the post
                for (int i = 0; i < numPages; ++i) {
                    if (pages[i]->getId() == line) {
                        newPost->addLikedBy(pages[i]);
                        break;
                    }
                }
            }
        }

        // Add the new post to the posts array
        if (numPosts < maxPosts) {
            posts[numPosts++] = newPost;
        } else {
            cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
            delete newPost; // Free memory to prevent memory leaks
        }
    }

    file.close();
}


};

#endif /* SOCIALNETWORKAPP_HPP */

int main()
{
    SocialNetworkApp app;
    app.run();
}