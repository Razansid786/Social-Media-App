#include <iostream>
#include <cstring>
using namespace std;

// creating prototypes of upcoming classes
class User;
class Page;
class Post;
class Activity;


class Page
{
    string id;
    //User owner;
    string title;
    Post* posts;
    int likes;
public:

    // getters
    string get_id() {return id;}
    //User& get_owner() {return owner;}
    string get_title() {return title;}
    Post* get_posts() {return posts;}
    int get_likes() {return likes;}
    
    void view_page()
    {

    }
    void add_like()
    {
        likes++;
    }
    
};

class User
{
    string name;
    string id;
    User** friends;
    Page** liked_pages;
    int curr_friends;
    int curr_liked_pages;
public:
    User(string n = "", string i = "")
    {
        name = n;
        id = i;
        friends = nullptr;
        liked_pages = nullptr;
        curr_friends = 0;
    }

    //getters
    string get_name() {return name;}
    string get_id() {return id;}
    User** get_friends() {return friends;}
    Page** get_liked_pages() {return liked_pages;}
    int get_curr_friends() {return curr_friends;}

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
/* 
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
 */
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

    void like_page(Page page)
    {
        page.add_like();
        // Resize the liked_pages array
        Page** new_liked_pages = nullptr;

        if (curr_liked_pages == 0) {
            // If there are no liked pages, create a new array with one element
            new_liked_pages = new Page*[1];
        } else {
            // Otherwise, create a new array with one more element than the current size
            new_liked_pages = new Page*[curr_liked_pages + 1];

            // Copy existing liked pages into the new array
            for (int i = 0; i < curr_liked_pages; i++) {
                new_liked_pages[i] = liked_pages[i];
            }
        }

        // Add the new page
        new_liked_pages[curr_liked_pages] = &page;

        // Deallocate the old liked_pages array
        delete[] liked_pages;

        // Update liked_pages to point to the new array
        liked_pages = new_liked_pages;

        // Increment the count of liked pages
        curr_liked_pages++;
    }

    void view_liked_pages()
    {
        cout<<"\nPage id\t\tPage title\n";
        for (int i = 0; i < curr_liked_pages; i++)
        {
            cout<<liked_pages[i]->get_id()<<"\t\t"<<liked_pages[i]->get_title()<<endl;
        }
    }


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
        // if (liked_pages != nullptr) {
        //     for (int i = 0; i < curr_friends; i++) {
        //         delete liked_pages[i];
        //     }
        //     delete[] liked_pages;
        // }

        // // Allocate memory for new liked_pages array
        // liked_pages = new Page*[curr_friends];

        // // Copy liked_pages from rhs to this object
        // for (int i = 0; i < curr_friends; i++) {
        //     liked_pages[i] = new Page(*rhs.liked_pages[i]); // Deep copy of Page object
        // }

        if (rhs.liked_pages != nullptr) {
        // Allocate memory for new liked_pages array
        curr_liked_pages = rhs.curr_liked_pages;
        liked_pages = new Page*[curr_liked_pages];

        // Copy liked_pages from rhs to this object
        for (int i = 0; i < curr_liked_pages; i++) {
            liked_pages[i] = new Page(*rhs.liked_pages[i]); // Deep copy of Page object
        }
        } else {
            // If rhs has no liked pages, set liked_pages to nullptr
            liked_pages = nullptr;
            curr_liked_pages = 0;
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
        likes++;
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

class SocialNetworkApp
{
    User current_user;
    User** users;
    Page** Pages;
public:

    void Run()
    {  
        User u1;
        current_user = u1;
        Page p1;
        current_user.like_page(p1);
        current_user.view_liked_pages();

    }

    void set_current_user(const User& user)
    {
        current_user = user;
    }

    void view_home()
    {

    }

    void like_page(Page page)
    {
        current_user.like_page(page);
    }

};

int main()
{
    SocialNetworkApp S1;
    S1.Run();
}