    /* 
    // #ifndef POST_HPP
    // #define POST_HPP
    // #include "user.h" // Include the User header file
    // // #include "page.h" // Include the Page header file
    // #include "activity.h"

    // #include <string>
    // #include <iostream>
    // using namespace std;

    // class User; // Forward declaration
    // class Page; // Forward declaration
    // class Activity;

    // class Post {
    // private:
    //     string id;
    //     string description;
    //     User** likedBy;
    //     int day;
    //     int month;
    //     int year;
    //     int maxLikedBy;
    //     int currLikedBy;
    //     int likes;
    //     int maxActivities; // Maximum number of activities
    //     int currActivities;
    //     pair<int, string>* activities; // Store activity type and value
    //     string ownerId;

    // public:
    //     Post(string i = "", string des = "", int d = 0, int m = 0, int y = 0, int maxLikedBy = 10, int maxActivities = 10)
    //         : id(i), description(des), day(d), month(m), year(y), maxLikedBy(maxLikedBy),
    //           currLikedBy(0), likes(0), maxActivities(maxActivities), currActivities(0) {
    //         likedBy = new User*[maxLikedBy];
    //         activities = new pair<int, string>[maxActivities];
    //     }

    //     ~Post() {
    //         delete[] likedBy;
    //         delete[] activities;
    //     }
    */
    #ifndef POST_HPP
    #define POST_HPP

    #include <string>
    #include "user.h" // Include the User header file
    #include "comment.h" // Include the Comment header file
    #include "date.h"
    using namespace std;

    class User; // Forward declaration
    class Comment; // Forward declaration
    class Date;

    class Post {
    private:
        string id;
        string description;
        User** likedBy;
        Date date;
        int maxLikedBy;
        int currLikedBy;
        int likes;
        int maxActivities; // Maximum number of activities
        int currActivities;
        pair<int, string>* activities; // Store activity type and value
        Comment** comments; // Array to store comments
        int maxComments;
        int currComments;
        string ownerId;
        Post* memory;

    public:
        Post(string i = "", string des = "", int d = 0, int m = 0, int y = 0, string o = "", int maxLikedBy = 10, int maxActivities = 10, int maxComments = 10)
            : id(i), description(des),ownerId(o), maxLikedBy(maxLikedBy),
            currLikedBy(0), likes(0), maxActivities(maxActivities), currActivities(0),
            maxComments(maxComments), currComments(0),memory(nullptr) {
            setDate(d,m,y);
            likedBy = new User*[maxLikedBy];
            activities = new pair<int, string>[maxActivities];
            comments = new Comment*[maxComments]; // Initialize comments array
        }

        ~Post() {
            delete[] likedBy;
            delete[] activities;
            for (int i = 0; i < currComments; ++i) {
                delete comments[i]; // Free memory allocated for comments
            }
            delete[] comments;
        }

        // Getters
        string getId() const { return id; }
        string getDescription() const { return description; }
        int getLikes() const { return likes; }
        // int getDay() const { return day; }
        // int getMonth() const { return month; }
        // int getYear() const { return year; }
        Date getDate() {return date;}
        int getCurrLikedBy() const { return currLikedBy; }
        int getMaxLikedBy() const { return maxLikedBy; }
        User** getLikedBy() const { return likedBy; }
        pair<int, string>* getActivities() const { return activities; }
        Comment** getComments() const { return comments; }
        int getCurrComments() const { return currComments; }
        int getMaxComments() const { return maxComments; }
        Post* getMemory() const { return memory; }
        string getOwnerId() {return ownerId;}


        // Setters
        void setId(const string& i) { id = i; }
        void setDescription(const string& des) { description = des; }
        // void setDay(int d) { day = d; }
        // void setMonth(int m) { month = m; }
        // void setYear(int y) { year = y; }
        void setDate(int d, int m , int y){
            date.setDay(d);
            date.setMonth(m);
            date.setYear(y);
        }

        void setMaxLikedBy(int max) {
            maxLikedBy = max;
            // If the new maxLikedBy is less than currLikedBy, adjust currLikedBy accordingly
            if (maxLikedBy < currLikedBy) {
                currLikedBy = maxLikedBy;
            }
        }
        void setLikedBy(User** likedByArray) {
            likedBy = likedByArray;
        }
        void setActivities(pair<int, string>* activitiesArray) {
            activities = activitiesArray;
        }

        void setComments(Comment** commentsArray) {
            comments = commentsArray;
        }
        void setMemory(Post* mem) { memory = mem; }

        // Methods
        void addLike(User* user) {
            if (currLikedBy < maxLikedBy) {
                likedBy[currLikedBy++] = user;
                likes++;
                // cout<<endl<<likedBy[currLikedBy]<<endl;
            }
        }

        bool isLikedBy(User* user) const {
            for (int i = 0; i < currLikedBy; ++i) {
                if (likedBy[i] == user) {
                    return true;
                }
            }
            return false;
        }

        void addActivity(int type, const string& value) {
            if (currActivities < maxActivities) {
                activities[currActivities++] = make_pair(type, value);
            }
        }

        void addComment(Comment* comment) {
            if (currComments < maxComments) {
                comments[currComments++] = comment;
            }
        }
    /* 
        // void setOwner(string owner) {
        //     bool flag;                   //if flag is true the owner is user else page
        //     for (int i = 0; i < owner.getMax())
        // }

        // void setOwner(const string& ownerId, User** users, int numUsers, Page** pages, int numPages) {
        //     // Check if the owner ID exists in the list of users
        //     for (int i = 0; i < numUsers; ++i) {
        //         if (users[i] != nullptr && users[i]->getId() == ownerId) {
        //             owner = users[i];
        //             return; // Owner found and set, exit the loop
        //         }
        //     }

        //     // Check if the owner ID exists in the list of pages
        //     for (int i = 0; i < numPages; ++i) {
        //         if (pages[i] != nullptr && pages[i]->getId() == ownerId) {
        //             owner = pages[i];
        //             return; // Owner found and set, exit the loop
        //         }
        //     }

        //     // If the owner ID doesn't match any user or page, set owner to nullptr
        //     owner = nullptr;
        // }

        // void addLikedBy(string lby) {
        //     if (currLikedBy < maxLikedBy) {
        //         likedBy[currLikedBy++] = lby;
        //     }
        // }

        // User* getOwner(User** users, int numUsers, Page** pages, int numPages, const string& ownerId) {
        //     for (int i = 0; i < numUsers; ++i) {
        //         if (users[i]->getId() == ownerId) {
        //             return users[i];
        //         }
        //     }
        //     for (int i = 0; i < numPages; ++i) {
        //         if (pages[i]->getId() == ownerId) {
        //             setIsPageOwner(true);
        //             return pages[i];
        //         }
        //     }
        //     return nullptr; // Owner not found
        // }

        // void addPostToOwner(User** users, int numUsers, Page** pages, int numPages, Post* post) {
        //     User* owner = getOwner(users, numUsers, pages, numPages, post->getId());
        //     if (owner) {
        //         owner->addPost(post);
        //     } else {
        //         cout << "Error: Owner not found for post " << post->getId() << endl;
        //     }
        // }
    */
    /*     
        //     void addPostToOwner(User** users, int numUsers, Page** pages, int numPages) {
        //     // Find the owner based on the ownerId
        //         // Find the page with the matching ID
        //     for (int i = 0; i < numPages; ++i) {
        //         if (pages[i] && pages[i]->getId() == ownerId) {
        //             // Add the post to the page
        //             pages[i]->addPost(this);
        //             return; // Exit the loop after adding the post
        //         }
        //     }
        //     // Find the user with the matching ID
        //     for (int i = 0; i < numUsers; ++i) {
        //         if (users[i] && users[i]->getId() == ownerId) {
        //             // Add the post to the user
        //             users[i]->addPost(this);
        //             return; // Exit the loop after adding the post
        //         }
        //     }
        // }
        */
    };

    #endif /*  POST_HPP  */



    /* 
    // #ifndef POST_HPP
    // #define POST_HPP

    // #include <string>
    // using namespace std;


    // class User; // Forward declaration

    // class Post {
    // private:
    //     string id;
    //     string description;
    //     User** likedBy;
    //     int day;
    //     int month;
    //     int year;
    //     int maxLikedBy;
    //     int currLikedBy;
    //     int likes;

    // public:
    //     Post(string i = "",string des = "", int d = 0, int m = 0, int y = 0, int maxLikedBy = 10){
    //         id = i;
    //         description = des;
    //         day = d;
    //         month = m;
    //         year = y;
    //         likedBy = new User*[maxLikedBy];

    //     };
    //     ~Post(){};
    //     // Getters
    //     string getId() {return id;};
    //     string getDescription() {return description;};
    //     int getLikes()  { return likes; }
    //     int getDay() {return day;}
    //     int getMonth() {return month;}
    //     int getyear() {return year;}
    //     int getCurrLikedBy() {return currLikedBy;}
    //     int getMaxLikedBy() {return maxLikedBy;}
    //     User** getLikedBy() {return likedBy;}

    //     // setters
    //     void setId(string i) {id = i;}
    //     // Declare other methods
    //     void addLike(User* user) {
    //         if (currLikedBy < maxLikedBy) {
    //             likedBy[currLikedBy++] = user;
    //             likes++;
    //         }
    //         //  else {
    //         //     cout << "Maximum number of likes reached for this post." << endl;
    //         // }
    //     }

    //     bool isLikedBy(User* user) const {
    //         for (int i = 0; i < currLikedBy; ++i) {
    //             if (likedBy[i] == user) {
    //                 return true;
    //             }
    //         }
    //         return false;
    //     }
    // };

    // #endif /* POST_HPP */
