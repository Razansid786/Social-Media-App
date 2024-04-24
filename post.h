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

#ifndef POST_HPP
#define POST_HPP

#include <string>
#include "User.h" // Include the User header file
#include "Page.h" // Include the Page header file

using namespace std;

class Post {
private:
    string id;
    string description;
    User** likedBy;
    int day;
    int month;
    int year;
    int maxLikedBy;
    int currLikedBy;
    int likes;
    int maxActivities; // Maximum number of activities
    int currActivities;
    pair<int, string>* activities; // Store activity type and value
    bool isPageOwner; // Indicates if the owner is a Page

public:
    Post(string i = "", string des = "", int d = 0, int m = 0, int y = 0, int maxLikedBy = 10, int maxActivities = 10)
        : id(i), description(des), day(d), month(m), year(y), maxLikedBy(maxLikedBy),
          currLikedBy(0), likes(0), maxActivities(maxActivities), isPageOwner(false), currActivities(0) {
        likedBy = new User*[maxLikedBy];
        activities = new pair<int, string>[maxActivities];
    }

    ~Post() {
        delete[] likedBy;
        delete[] activities;
    }

    // Getters
    string getId() const { return id; }
    string getDescription() const { return description; }
    int getLikes() const { return likes; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getCurrLikedBy() const { return currLikedBy; }
    int getMaxLikedBy() const { return maxLikedBy; }
    User** getLikedBy() const { return likedBy; }
    pair<int, string>* getActivities() const { return activities; }
    bool getIsPageOwner() const { return isPageOwner; }

    // Setters
    void setId(const string& i) { id = i; }
    void setDescription(const string& des) { description = des; }
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
    void setMaxLikedBy(int max) {
        maxLikedBy = max;
        // If the new maxLikedBy is less than currLikedBy, adjust currLikedBy accordingly
        if (maxLikedBy < currLikedBy) {
            currLikedBy = maxLikedBy;
        }
    }
    void setIsPageOwner(bool value) { isPageOwner = value; }

    // Methods
    void addLike(User* user) {
        if (currLikedBy < maxLikedBy) {
            likedBy[currLikedBy++] = user;
            likes++;
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

    // void setOwner(string owner) {
    //     bool flag;                   //if flag is true the owner is user else page
    //     for (int i = 0; i < owner.getMax())
    // }

    void setOwner(const string& ownerId, User** users, int numUsers, Page** pages, int numPages) {
        // Check if the owner ID exists in the list of users
        for (int i = 0; i < numUsers; ++i) {
            if (users[i] != nullptr && users[i]->getId() == ownerId) {
                owner = users[i];
                return; // Owner found and set, exit the loop
            }
        }

        // Check if the owner ID exists in the list of pages
        for (int i = 0; i < numPages; ++i) {
            if (pages[i] != nullptr && pages[i]->getId() == ownerId) {
                owner = pages[i];
                return; // Owner found and set, exit the loop
            }
        }

        // If the owner ID doesn't match any user or page, set owner to nullptr
        owner = nullptr;
    }

    void addLikedBy(string lby) {
        if (currLikedBy < maxLikedBy) {
            likedBy[currLikedBy++] = lby;
        }
    }
};

#endif /* POST_HPP */