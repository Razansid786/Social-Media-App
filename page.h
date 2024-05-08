#ifndef PAGE_HPP
#define PAGE_HPP

#include <iostream>
#include <string>
#include "post.h"
using namespace std;

class User; // Forward declaration
class Post;

class Page {
private:
    string id;
    User* owner;
    string title;
    Post** posts;
    int maxPosts;
    int currPosts;
    int likes;
    int max = 12;

public:
    Page(string id = "", User* owner = nullptr, string title = "") : id(id), owner(owner), title(title), maxPosts(100), currPosts(0), likes(0) {
        posts = new Post*[maxPosts]; 
        for (int i = 0; i < maxPosts; ++i) {
            posts[i] = nullptr; 
        }
    }
    ~Page(){};
    // getters
    string getId() {return id;};
    string getTitle() {return title;}
    Post** getPosts() {return posts;}
    int getCurrPosts() {return currPosts;}

    void addPost(Post* post) {
        if (currPosts < maxPosts) {
            posts[currPosts++] = post;
        } else {
            cout << "Error: Maximum number of posts reached for this page." << endl;
        }
    }
};

#endif /* PAGE_HPP */