#include <string>
#include "user.h" // Include the User header file
#include "post.h" // Include the Post header file
using namespace std;

class User; // Forward declaration
class Post; // Forward declaration

class Comment {
private:
    std::string comment;
    User* commentOwner;         //user that posted the comment
    Post* commentPost;          // post on which the comment was done

public:
    // Constructor
    Comment(std::string c = "", User* owner = nullptr, Post* post = nullptr)
        : comment(c), commentOwner(owner), commentPost(post) {}

    // Getters
    std::string getComment() const { return comment; }
    User* getCommentOwner() const { return commentOwner; }
    Post* getCommentPost() const { return commentPost; }

    // Setters
    void setComment(const std::string& c) { comment = c; }
    void setCommentOwner(User* owner) { commentOwner = owner; }
    void setCommentPost(Post* post) { commentPost = post; }
};