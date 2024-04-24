#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include "post.h"
using namespace std;

class User; // Forward declaration

class Page {
private:
    string id;
    User* owner;
    string title;
    Post** pposts;
    int maxPosts;
    int currPosts;
    int likes;
    int max = 12;

public:
    Page(string id = "", User* owner = nullptr, string title = "") : id(id), owner(owner), title(title), maxPosts(100), currPosts(0), likes(0) {}
    ~Page(){};
    // getters
    string getId() {return id;};
    string getTitle() {return title;};
    // Declare other methods
};

#endif /* PAGE_HPP */