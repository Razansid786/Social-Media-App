#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "page.h"
#include "post.h" 
#include "comment.h" 
#include <iostream>
using namespace std;

class Post; 
class Comment; 

class User {
private:
    string id;
    string name;
    string* friends;
    string* likedPages;
    Post** posts;
    Comment** comments; 
    int maxFriends;
    int maxLikedPages;
    int maxPosts;
    int maxComments;
    int currFriends;
    int currLikedPages;
    int currPosts;
    int currComments;
    int max = 20;

public:
    User(string i = "", string n = "", int maxFriends = 10, int maxLikedPages = 10, int maxComments = 10)
        : id(i), name(n), maxFriends(maxFriends), maxLikedPages(maxLikedPages), currFriends(0), currLikedPages(0),
          maxPosts(100), currPosts(0), maxComments(maxComments), currComments(0) {
        friends = new string[maxFriends];
        likedPages = new string[maxLikedPages];
        posts = new Post*[maxPosts];
        comments = new Comment*[maxComments];
    }

    ~User() {
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
    int getCurrFriends() {return currFriends;}
    string* getFriends() {return friends;}
    string* getLikedPages() {return likedPages;}
    int getCurrLikedPages() {return currLikedPages;}

    //setters

    void addFriend(const string& friendId) {
        if (currFriends < maxFriends) {
            friends[currFriends++] = friendId;
        } else {
            cout << "Error: Maximum number of friends reached for user " << id << endl;
        }
    }

    void addLikedPage(const string& pageId) {
        if (currLikedPages < maxLikedPages) {
            likedPages[currLikedPages++] = pageId;
        } else {
            cout << "Error: Maximum number of liked pages reached for user " << id << endl;
        }
    }

    void addPost(Post* post) {
        if (currPosts < maxPosts) {
            posts[currPosts++] = post;
        } else {
            cout << "Error: Maximum number of posts reached for user " << id << endl;
        }
    }

    void addComment(Comment* comment) {
        if (currComments < maxComments) {
            comments[currComments++] = comment;
        } else {
            cout << "Error: Maximum number of comments reached for user " << id << endl;
        }
    }
};

#endif /* USER_HPP */