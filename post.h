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
    #include "user.h" 
    #include "comment.h" 
    #include "date.h"
    using namespace std;

    class User; 
    class Comment; 
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
        int maxActivities;
        int currActivities;
        pair<int, string>* activities; 
        Comment** comments; 
        int maxComments;
        int currComments;
        string ownerId;
        string memoryText;
        int yearDiff;

    public:
        Post(string i = "", string des = "", int d = 0, int m = 0, int y = 0, string o = "", int maxLikedBy = 10, int maxActivities = 10, int maxComments = 10)
            : id(i), description(des),ownerId(o), maxLikedBy(maxLikedBy),
            currLikedBy(0), likes(0), maxActivities(maxActivities), currActivities(0),
            maxComments(maxComments), currComments(0),memoryText("") {
            setDate(d,m,y);
            likedBy = new User*[maxLikedBy];
            activities = new pair<int, string>[maxActivities];
            comments = new Comment*[maxComments];
        }

        ~Post() {
            delete[] likedBy;
            delete[] activities;
            for (int i = 0; i < currComments; ++i) {
                delete comments[i]; 
            }
            delete[] comments;
        }

        // Getters
        string getId() const { return id; }
        string getDescription() const { return description; }
        int getLikes() const { return likes; }
        Date getDate() {return date;}
        int getCurrLikedBy() const { return currLikedBy; }
        int getMaxLikedBy() const { return maxLikedBy; }
        User** getLikedBy() const { return likedBy; }
        pair<int, string>* getActivities() const { return activities; }
        Comment** getComments() const { return comments; }
        int getCurrComments() const { return currComments; }
        int getMaxComments() const { return maxComments; }
        string getMemoryText() const { return memoryText; }
        string getOwnerId() {return ownerId;}
        int getYearDiff() {return yearDiff;}


        // Setters
        void setId(const string& i) { id = i; }
        void setDescription(const string& des) { description = des; }
        void setDate(int d, int m , int y){
            date.setDay(d);
            date.setMonth(m);
            date.setYear(y);
        }

        void setMaxLikedBy(int max) {
            maxLikedBy = max;
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
        void setMemoryText(string mem) { memoryText = mem; }

        void setYearDiff(int d) {yearDiff = d;}

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

        void addComment(Comment* comment) {
            if (currComments < maxComments) {
                comments[currComments++] = comment;
            }
        }

    };

    #endif /*  POST_HPP  */