/* 
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

// // #endif /* USER_HPP */
/* 
// #ifndef USER_HPP
// #define USER_HPP

// #include <string>
// #include "page.h"

// class User {
// private:
//     string id;
//     string name;
//     string* friends;
//     string* likedPages;
//     Post** posts;
//     int maxUposts;
//     int maxFriends;
//     int maxLikedPages;
//     int currFriends;
//     int currLikedPages;
//     int max = 20;

// public:
//     User(string i = "", string n = "", int maxFriends = 10, int maxLikedPages = 10)
//         : id(i), name(n), maxFriends(maxFriends), maxLikedPages(maxLikedPages), currFriends(0), currLikedPages(0), maxUposts(100) {
//         // Allocate memory for friends and likedPages arrays
//         friends = new string[maxFriends];
//         likedPages = new string[maxLikedPages];
//     }

//     ~User() {
//         // Deallocate memory for friends and likedPages arrays
//         delete[] friends;
//         delete[] likedPages;
//     }

//     // Getters
//     string getName() const { return name; }
//     string getId() const { return id; }

//     // Add a friend to the user
//    void addFriend(const string& friendId) {
//         // Ensure there is space to add a new friend
//         if (currFriends < maxFriends) {
//             friends[currFriends++] = friendId;
//         } else {
//             // Handle error: No space to add more friends
//             cout << "Error: Maximum number of friends reached for user " << id << endl;
//         }
//     }

//     // Add a liked page to the user
//     void addLikedPage(const string& pageId) {
//         // Ensure there is space to add a new liked page
//         if (currLikedPages < maxLikedPages) {
//             likedPages[currLikedPages++] = pageId;
//         } else {
//             // Handle error: No space to add more liked pages
//             cout << "Error: Maximum number of liked pages reached for user " << id << endl;
//         }
//     }

//     void addPost(Post* post) {
//         if (currPosts < maxPosts) {
//             posts[currPosts++] = post;
//         } else {
//             cout << "Error: Maximum number of posts reached for user " << id << endl;
//         }
//     }
// };

// #endif /* USER_HPP /* */
/* 
#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "page.h"
#include "post.h" // Include the Post header file
#include <iostream>
using namespace std;

class Post;

class User {
private:
    string id;
    string name;
    string* friends;
    string* likedPages;
    Post** posts;
    int maxFriends;
    int maxLikedPages;
    int maxPosts;
    int currFriends;
    int currLikedPages;
    int currPosts;
    int max = 20;

public:
    User(string i = "", string n = "", int maxFriends = 10, int maxLikedPages = 10)
        : id(i), name(n), maxFriends(maxFriends), maxLikedPages(maxLikedPages), currFriends(0), currLikedPages(0), maxPosts(100), currPosts(0) {
        // Allocate memory for friends, likedPages, and posts arrays
        friends = new string[maxFriends];
        likedPages = new string[maxLikedPages];
        posts = new Post*[maxPosts];
    }

    ~User() {
        // Deallocate memory for friends, likedPages, and posts arrays
        delete[] friends;
        delete[] likedPages;
        for (int i = 0; i < currPosts; ++i) {
            delete posts[i];
        }
        delete[] posts;
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

    // Add a post to the user
    void addPost(Post* post) {
        if (currPosts < maxPosts) {
            posts[currPosts++] = post;
        } else {
            cout << "Error: Maximum number of posts reached for user " << id << endl;
        }
    }
};

#endif /* USER_HPP */

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "page.h"
#include "post.h" // Include the Post header file
#include "comment.h" // Include the Comment header file
#include <iostream>
using namespace std;

class Post; // Forward declaration
class Comment; // Forward declaration

class User {
private:
    string id;
    string name;
    string* friends;
    string* likedPages;
    Post** posts;
    Comment** comments; // Array of Comment objects
    int maxFriends;
    int maxLikedPages;
    int maxPosts;
    int maxComments; // Maximum number of comments
    int currFriends;
    int currLikedPages;
    int currPosts;
    int currComments; // Current number of comments
    int max = 20;

public:
    User(string i = "", string n = "", int maxFriends = 10, int maxLikedPages = 10, int maxComments = 10)
        : id(i), name(n), maxFriends(maxFriends), maxLikedPages(maxLikedPages), currFriends(0), currLikedPages(0),
          maxPosts(100), currPosts(0), maxComments(maxComments), currComments(0) {
        // Allocate memory for friends, likedPages, posts, and comments arrays
        friends = new string[maxFriends];
        likedPages = new string[maxLikedPages];
        posts = new Post*[maxPosts];
        comments = new Comment*[maxComments];
    }

    ~User() {
        // Deallocate memory for friends, likedPages, posts, and comments arrays
        delete[] friends;
        delete[] likedPages;
        for (int i = 0; i < currPosts; ++i) {
            delete posts[i];
        }
        delete[] posts;
        for (int i = 0; i < currComments; ++i) {
            delete comments[i];
        }
        delete[] comments;
    }

    // Getters
    string getName() const { return name; }
    string getId() const { return id; }
    Post** getPosts() {return posts;}
    int getCurrPosts() {return currPosts;}

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

    // Add a post to the user
    void addPost(Post* post) {
        if (currPosts < maxPosts) {
            posts[currPosts++] = post;
        } else {
            cout << "Error: Maximum number of posts reached for user " << id << endl;
        }
    }

    // Add a comment to the user
    void addComment(Comment* comment) {
        if (currComments < maxComments) {
            comments[currComments++] = comment;
        } else {
            cout << "Error: Maximum number of comments reached for user " << id << endl;
        }
    }
};

#endif /* USER_HPP */