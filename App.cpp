#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
#include <conio.h>
using namespace std;

class SocialNetworkApp
{
    User current_user;
    User** users;
    Page** Pages;
public:


    void set_current_user(int user_id)
    {

    }
    void view_home()
    {

    }
    void Run()
    {

    }

};

// creating prototypes of upcoming classes
class User;
class Page;
class Post;
class Activity;

class User
{
    string name;
    string id;
    User** friends;
    Page** liked_pages;
    int curr_friends;
public:
    User(string n = "", string i = "")
    {
        name = n;
        i = id;
        friends = nullptr;
        liked_pages = nullptr;
        curr_friends = 0;
    }

    void view_timeline()
    {

    }

    void view_friend_list()
    {
        cout<<"\n\tFriends list\n";
        cout<<"Name\t\tid"<<endl;
        for (int i = 0; friends[i] != nullptr; i++)
        {
            cout<<friends[i]<<endl;   
        }
    }

    // void add_friend(const User& user)
    // {   
    //     curr_friends++;
    //     friends = new User*[curr_friends];
    //     for (int i = 0; i < curr_friends; i++)
    //     {

    //     }
    // }

    // User& operator=(const User& rhs)
    // {
    //     name = rhs.name;
    //     id = rhs.id;
    //     curr_friends = rhs.curr_friends;
    //     friends = new User*[curr_friends];
    //     for (int i = 0; i < curr_friends; i++)
    //     {

    //     }
    // }

    void add_friend(User& user) {
        // Create a new array with space for one more friend
        User** new_friends = new User*[curr_friends + 1];

        // Copy existing friends into the new array
        for (int i = 0; i < curr_friends; i++) {
            new_friends[i] = friends[i];
        }

        // Add the new friend
        new_friends[curr_friends] = &user;

        // Deallocate the old friends array
        delete[] friends;

        // Update the friends pointer to point to the new array
        friends = new_friends;

        // Increment the number of current friends
        curr_friends++;
    }

    Page** get_liked_pages(){return liked_pages;}

    ~User() {
        delete[] friends;

        // Deallocate liked_pages array and its elements
        if (liked_pages != nullptr) {
            for (int i = 0; i < curr_friends; i++) {
                delete liked_pages[i];
            }
            delete[] liked_pages;
        }
    }

    // Overloaded assignment operator
    User& operator=(const User& rhs) {
        if (this == &rhs) {
            return *this;
        }

        // Copy the name and id
        name = rhs.name;
        id = rhs.id;

        // Deallocate the old friends array
        delete[] friends;

        // Allocate memory for the new friends array
        curr_friends = rhs.curr_friends;
        friends = new User*[curr_friends];

        // Copy the friends from the right-hand side to the left-hand side
        for (int i = 0; i < curr_friends; i++) {
            friends[i] = rhs.friends[i];
        }

        // Deallocate old liked_pages array
        if (liked_pages != nullptr) {
            for (int i = 0; i < curr_friends; i++) {
                delete liked_pages[i];
            }
            delete[] liked_pages;
        }

        // Allocate memory for new liked_pages array
        liked_pages = new Page*[curr_friends];

        // Copy liked_pages from rhs to this object
        for (int i = 0; i < curr_friends; i++) {
            liked_pages[i] = new Page(*rhs.liked_pages[i]); // Deep copy of Page object
        }

        return *this;
    }

    friend ostream& operator<<(ostream& out, const User& user)
    {
        out<<user.name;
        cout<<"\t\t";
        out<<user.id;
        cout<<endl;
    }
};

class Page
{
    string id;
    User owner;
    string title;
    Post* posts;
    int likes;
public:
    void view_page()
    {

    }
    void add_like()
    {
        likes++;

    }
};

class Post
{
    string id;
    string description;
    int likes;
    User* liked_by;
    string* comments;
    // shared_date
    Activity* activity;
public:
    void add_comment()
    {

    }

    void add_like()
    {

    }

    void view_post()
    {

    }


};

class Activity
{
    int type;
    string value;
};




//razan
