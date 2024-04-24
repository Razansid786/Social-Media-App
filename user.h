// #ifndef USER_HPP
// #define USER_HPP

// #include <string>
// #include "page.h"
// using namespace std;

// class User {
// private:
//     string id;
//     string name;
//     User** friends;
//     Page** likedPages;
//     int maxFriends;
//     int maxLikedPages;
//     int currFriends;
//     int currLikedPages;

// public:
//     User(string i = "", string n = "", int maxFriends = 100, int maxLikedPages = 100)
//     {
//         id = i;
//         name = n;
//     }
//     ~User(){}
//     // getters
//     string getName() {return name;}
//     string getId() {return id;}
//     // Declare other methods
// };

// #endif /* USER_HPP */

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "page.h"

class User {
private:
    string id;
    string name;
    string* friends;
    string* likedPages;
    Post** uposts;
    int maxUposts;
    int maxFriends;
    int maxLikedPages;
    int currFriends;
    int currLikedPages;
    int max = 20;

public:
    User(string i = "", string n = "", int maxFriends = 10, int maxLikedPages = 10)
        : id(i), name(n), maxFriends(maxFriends), maxLikedPages(maxLikedPages), currFriends(0), currLikedPages(0), maxUposts(100) {
        // Allocate memory for friends and likedPages arrays
        friends = new string[maxFriends];
        likedPages = new string[maxLikedPages];
    }

    ~User() {
        // Deallocate memory for friends and likedPages arrays
        delete[] friends;
        delete[] likedPages;
    }

    // Getters
    string getName() const { return name; }
    string getId() const { return id; }

    // Add a friend to the user
   void addFriend(const string& friendId) {
        // Ensure there is space to add a new friend
        if (currFriends < maxFriends) {
            friends[currFriends++] = friendId;
        } else {
            // Handle error: No space to add more friends
            cout << "Error: Maximum number of friends reached for user " << id << endl;
        }
    }

    // Add a liked page to the user
    void addLikedPage(const string& pageId) {
        // Ensure there is space to add a new liked page
        if (currLikedPages < maxLikedPages) {
            likedPages[currLikedPages++] = pageId;
        } else {
            // Handle error: No space to add more liked pages
            cout << "Error: Maximum number of liked pages reached for user " << id << endl;
        }
    }
};

#endif /* USER_HPP */