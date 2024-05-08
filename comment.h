#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "user.h" 
#include "post.h" 
using namespace std;

class User; 
class Post; 

class Comment {
private:
    string comment;
    User* commentOwner;         //user that posted the comment
    Post* commentPost;          // post on which the comment was done

public:
    Comment(string c = "", User* owner = nullptr, Post* post = nullptr)
        : comment(c), commentOwner(owner), commentPost(post) {}

    // Getters
    string getComment() const { return comment; }
    User* getCommentOwner() const { return commentOwner; }
    Post* getCommentPost() const { return commentPost; }

    // Setters
    void setComment(const string& c) { comment = c; }
    void setCommentOwner(User* owner) { commentOwner = owner; }
    void setCommentPost(Post* post) { commentPost = post; }
};

#endif // COMMENT_H