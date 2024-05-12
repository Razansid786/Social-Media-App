#ifndef SOCIALNETWORKAPP_HPP
#define SOCIALNETWORKAPP_HPP
#include "page.h"
#include "post.h"
#include "user.h"
#include "comment.h"
#include "date.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;

class User;
class Page;
class Post;
class Activity;
class comment;
class Date;

class SocialNetworkApp {
private:
    User* currentUser;
    User** users;
    Page** pages;
    Post** posts; 
    int maxUsers;
    int maxPages;
    int maxPosts;
    int numUsers;
    int numPosts;
    int numPages;
    Date currentDate;

public:
    SocialNetworkApp(int maxUsers = 20, int maxPages = 12, int maxPosts = 12)
        : currentUser(nullptr), maxUsers(maxUsers), maxPages(maxPages), maxPosts(maxPosts), numUsers(0), numPosts(0), numPages(0) {
        setDate(1,1,2000);
        users = new User*[maxUsers];
        pages = new Page*[maxPages];
        posts = new Post*[maxPosts];
        initializeUsersFromFile("Users.txt");
        initializePagesFromFile("Pages.txt");
        initializePostsFromFile("Posts.txt");
        readCommentsFromFile("Comments.txt");
    }
    ~SocialNetworkApp() {
        for (int i = 0; i < numUsers; ++i) {
            delete users[i];
        }
        delete[] users;

        for (int i = 0; i < numPages; ++i) {
            delete pages[i];
        }
        delete[] pages;

        for (int i = 0; i < numPosts; ++i) {
            delete posts[i];
        }
        delete[] posts;
    };
    //getters
    int getMaxUsers() {return maxUsers;}
    int getMaxPages() {return maxPages;}
    User** getUsers() {return users;}
    Page** getPage() {return pages;}

    void clearInputBuffer() {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    void run()
    {
        cout<<"Set current date:- "<<endl;
        cout<<"Enter day: ";
        int d,m,y;
        cin>>d;
        currentDate.setDay(d);
        cout<<"Enter Month: ";
        cin>>m;
        currentDate.setMonth(m);
        cout<<"Enter Year: ";
        cin>>y;
        currentDate.setYear(y);
        cout<<"-------------"<<endl;
        string u;
        cout<<"\tSet current user\n";
        cout<<"Enter user ID: ";
        cin>>u;
        setCurrentUser(u);
        cout<<"-------------";
        int choice;

        do {
            cout << "\n\nChoose an option:" << endl;
            cout << "1. Change Current User" << endl;
            cout << "2. View Home of Current User" << endl;
            cout << "3. Like a Post" << endl;
            cout << "4. View the List of People who Liked a Post" << endl;
            cout << "5. Comment on a post" << endl;
            cout << "6. View a post" << endl;
            cout << "7. Share a memory" << endl;
            cout << "8. View user's timeline" << endl;
            cout << "9. View user's friend list" << endl;
            cout << "10. View a page" << endl;
            cout << "Enter your choice (0 to exit): ";
            
            if (!(cin >> choice)) {
                cout << "\n---Invalid input. Please enter a valid integer.---" << endl;
                clearInputBuffer(); 
                continue;
            }
            
            if (choice != 0) {
                switch (choice) {
                        case 1: {
                            string i;
                            cout<<"Enter the user ID";
                            cin>>i;
                            setCurrentUser(i);
                            break;
                        }
                        case 2: {
                            viewHome();
                            break;
                        }
                        case 3: {
                            string i;
                            cout<<"Enter the post ID: ";
                            cin>> i;
                            likePost(i);
                            break;
                        }
                        case 4: {
                            string i;
                            cout<<"Enter the post ID: ";
                            cin>> i;
                            viewLikes(i);
                            break;
                        }
                        case 5: {
                            string i,t;
                            cout<<"Enter post ID: ";
                            cin>>i;
                            cout<<"Enter the comment: ";
                            cin.ignore();
                            getline(cin,t);
                            commentOnPost(i,t);
                            break;
                        }
                        case 6: {
                            string i;
                            cout<<"Enter the post ID: ";
                            cin>> i;
                            viewPost(i);
                            break;
                        }
                        case 7: {
                            string i,t;
                            cout<<"Enter post ID: ";
                            cin>>i;
                            cout<<"Enter the memory text: ";
                            cin.ignore();
                            getline(cin,t);
                            shareMemory(i,t);
                            break;
                        }
                        case 8: {
                            viewUserTimeline();
                            break;
                        }
                        case 9: {
                            string i;
                            cout<<"Enter user ID: ";
                            cin>>i;
                            viewFriendList(i);
                            break;
                        }
                        case 10: {
                            string i;
                            cout<<"Enter page ID: ";
                            cin>>i;
                            viewPage(i);
                            break;
                        }
                        default:
                            cout << "\n---Invalid choice. Please try again.---" << endl;
                            break;
                }
            } else {
                cout << "\nExiting.......";
                break; 
            }
        } while (true);
    }

    // setters
    void setDate(int d, int m , int y){
        currentDate.setDay(d);
        currentDate.setMonth(m);
        currentDate.setYear(y);
    }


        // Function to find a user by their ID
    User* findUserById(const string& userId) {
        for (int i = 0; i < numUsers; ++i) {
            if (users[i]->getId() == userId) {
                return users[i];
            }
        }
        return nullptr; // User not found
    }

        //Function to find a page by id
    Page* findPageById(const string& pageId) {
    for (int i = 0; i < numPages; ++i) {
        if (pages[i]->getId() == pageId) {
            return pages[i];
        }
    }
    return nullptr;
}

        //Function to find a post by its Id
    Post* findPostById(const string& postId) {
        for (int i = 0; i < maxPosts; ++i) {
            if (posts[i]->getId() == postId) {
                return posts[i];
            }
        }
        return nullptr; 
    }

        
    void viewPostsOfFriendsInLast24Hours() {
        string* friendIds = currentUser->getFriends(); 
        int numFriends = currentUser->getCurrFriends(); 

        for (int i = 0; i < numFriends; ++i) {
            User* friendUser = findUserById(friendIds[i]); 
            if (friendUser) { 
                cout << "\n\nPosts from " << friendUser->getName() << ":" << endl;
                Post** posts = friendUser->getPosts(); 
                int numPosts = friendUser->getCurrPosts(); 

                if (numPosts == 0){
                    cout<<"\n\t---No posts in last 24 hours!---\n";
                    continue;
                }

                for (int j = 0; j < numPosts; ++j) {
                    Post* post = posts[j]; 
                    if (isPostSharedInLast24Hours(post)) {
                        viewPost(post->getId());
                    }
                }
            } else {
                cout << "Error: Friend with ID " << friendIds[i] << " not found." << endl;
            }
        }
    }

   
    void viewPostsOfLikedPagesInLast24Hours() {
        string* likedPageIds = currentUser->getLikedPages();
        int numLikedPages = currentUser->getCurrLikedPages(); 

        for (int i = 0; i < numLikedPages; ++i) {
            Page* likedPage = findPageById(likedPageIds[i]); 
            if (likedPage) { 
                cout << "\n\nPosts from " << likedPage->getTitle() << ":" << endl;
                Post** posts = likedPage->getPosts(); 
                int numPosts = likedPage->getCurrPosts(); 
                if (numPosts == 0){
                    cout<<"\n\t---No Posts in last 24 hours!---\n";
                    continue;
                }
                for (int j = 0; j < numPosts; ++j) {
                    Post* post = posts[j]; 
                    if (isPostSharedInLast24Hours(post)) {
                        viewPost(post->getId());
                    }
                }
            } else {
                cout << "Error: Liked page with ID " << likedPageIds[i] << " not found." << endl;
            }
        }
    }
   
    bool isPostSharedInLast24Hours(Post* post) {
       
        Date postDate = post->getDate();
        int daysDifference = currentDate.calculateDaysDifference(postDate);

        return daysDifference <= 1;
    }

        // Task 1

    void setCurrentUser(const string& userId)
    {
        for (int i = 0; i < maxUsers; ++i) {
            if (users[i] != nullptr && users[i]->getId() == userId) {
                currentUser = users[i];
                return;
            }
        }
        currentUser = nullptr;
    }

        // Task 2

    void viewHome(){
        cout << "\n\tPosts from friends shared in last 24 hours:" << endl;
        viewPostsOfFriendsInLast24Hours();

        cout << "\n\n\tPosts from liked pages shared in last 24 hours:" << endl;
        viewPostsOfLikedPagesInLast24Hours();
    }

    

        //Task 3

    void likePost(const string& postId){
        if (currentUser == nullptr) {
            cout << "Error: Current user not set." << endl;
            return;
        }

        Post* postToLike = nullptr;
        for (int i = 0; i < maxPosts; ++i) {
            if (posts[i] != nullptr && posts[i]->getId() == postId) {
                postToLike = posts[i];
                break;
            }
        }

        if (postToLike == nullptr) {
            cout << "\n---Error: Post with ID " << postId << " not found.---" << endl;
            return;
        }

        for (int i = 0; i < postToLike->getCurrLikedBy(); ++i) {
            if (postToLike->getLikedBy()[i] == currentUser) {
                cout << "\n---You have already liked this post.---" << endl;
                return;
            }
        }

        if (postToLike->getCurrLikedBy() >= postToLike->getMaxLikedBy()) {
            cout << "\n---Error: This post has reached the maximum number of likes.---" << endl;
            return;
        }

        postToLike->addLike(currentUser);
    }
            // Task 4

    void viewLikes(const string& postId) {
        Post* post = findPostById(postId);
        if (post != nullptr) {
            User** likedBy = post->getLikedBy();
            int numLikedBy = post->getCurrLikedBy();

            if (numLikedBy > 0) {
                cout << "\nList of people who liked the post:" << endl;
                for (int i = 0; i < numLikedBy; ++i) {
                    cout <<likedBy[i]->getId()<<"---"<< likedBy[i]->getName() << endl;
                }
            } else {
                cout << "\n---No users have liked the post.---" << endl;
            }
        } else {
            cout << "\n---Post with ID " << postId << " not found.---" << endl;
        }
    };

            //Task 5

    void commentOnPost(const string& postId, const string& commentText) {

        Post* targetPost = findPostById(postId);
        if (targetPost) {
            // Create a new Comment object
            Comment* newComment = new Comment(commentText, currentUser, targetPost);

            targetPost->addComment(newComment);

            currentUser->addComment(newComment);

        } else {
            cout << "Error: Post not found with ID " << postId << endl;
        }
    }

        // Task 6

    void viewPost(const string& postId){
        Post* post = findPostById(postId);

        if (post) {
        cout << "\nPost ID: " << post->getId() << endl;
        cout << "Description: " << post->getDescription() << endl;
        cout << "Likes: " << post->getLikes() << endl;

        cout << "Activity: ";
        pair<int, string>* activity = post->getActivities();
        if (activity->second != "" ) {
            cout << activity->second << endl;
        } else  {
            cout << "No activity." << endl;
        }
        cout<<"Shared date: "<<post->getDate().getDay()<<"/"<<post->getDate().getMonth()<<"/"<<post->getDate().getYear()<<endl;
        cout << "Comments:" << endl;
        Comment** comments = post->getComments();
        int numComments = post->getCurrComments();
        
        if (numComments == 0)
            cout<<" No comments! ";

        for (int i = 0; i < numComments; ++i) {
            Comment* comment = comments[i];
            if (comment) {
                cout << comment->getCommentOwner()->getName() <<": ";
                cout << comment->getComment() << endl;
                cout << "----------------------------------" << endl;
            }
        }
    } else {
        cout << "Post with ID " << postId << " does not exist." << endl;
    }

    };

        //          Task 7
        
    void shareMemory(const string& postId, const string& text) {
        
        Post** tempPost = currentUser->getPosts();
        for (int i = 0; i < currentUser->getCurrPosts(); i++)
        {
            if (tempPost[i] == findPostById(postId))
            {
                if (currentDate.getDay() == tempPost[i]->getDate().getDay() && currentDate.getMonth() == tempPost[i]->getDate().getMonth() )
                {
                    tempPost[i]->setMemoryText(text);
                    int diff = currentDate.getYear() - tempPost[i]->getDate().getYear();
                    tempPost[i]->setYearDiff(diff);
                    cout<<"\t\tMemory added successfully!!\n\n";
                    return;
                }
                else {
                    cout<<"\n---Error: The dates don't match!---\n ";
                }
            }
        }
        cout<<"\n---Invalid post id entered---\n";

    }   

        //      Task 8

    void viewUserTimeline(){
        if (currentUser) {
            cout << "User Name: " << currentUser->getName() << endl;
            
            Post** tempPosts = currentUser->getPosts();
            int numPosts = currentUser->getCurrPosts();
            cout<<"NumPost: "<<numPosts<<endl;
            if (numPosts != 0)
            {
                cout << "\n\t\tUser's Posts:\n" << endl;
                for (int i = 0; i < numPosts; ++i) {
                    cout << "Post ID: " << tempPosts[i]->getId() << endl;
                    cout << "Description: " << tempPosts[i]->getDescription() << endl;
                    cout << "Likes: " << tempPosts[i]->getLikes() << endl;
                    cout << "Date: " << tempPosts[i]->getDate().getDay() << "/" << posts[i]->getDate().getMonth() << "/" << posts[i]->getDate().getYear() << endl;
                    cout<<endl;
                    if (tempPosts[i]->getMemoryText() != "")
                    {
                        cout<<"("<<tempPosts[i]->getYearDiff()<<" years ago "<<currentUser->getName()<<" posted)\n";
                        cout<<tempPosts[i]->getMemoryText()<<endl;
                    }
                    cout << "-----------------------" << endl;
                }
            }
            else{
                cout<<"\tNo Posts Found!!\n\n";
            }
            
        } else {
            cout << "No user is logged in." << endl;
        }
    };

        //Task 9

    void viewFriendList(const string& userId){
    User* user = findUserById(userId);

        if (user) {
            cout << "\n---Friend List for User " << user->getName() << "---" << endl;
            string* friendIds = user->getFriends();
            int numFriends = user->getCurrFriends();
            for (int i = 0; i < numFriends; ++i) {
                User* friendUser = findUserById(friendIds[i]);
                if (friendUser) {
                    cout <<friendUser->getId()<< "--- " << friendUser->getName() << endl;
                }
            }
        } else {
            cout << "\n---User with ID " << userId << " not found.---" << endl;
        }

    };

        //Task 10

    void viewPage(const string& pageId) {
        Page* page = findPageById(pageId);

    if (page) {
        cout << "\nPosts on Page " << page->getTitle() << ":" << endl<<endl;
        Post** posts = page->getPosts();
        int numPosts = page->getCurrPosts();
        if (numPosts == 0)
        {
            cout<<"---No posts!!---"<<endl;
        }
        for (int i = 0; i < numPosts; ++i) {
            cout << "Post ID: " << posts[i]->getId() << endl;
            cout << "Description: " << posts[i]->getDescription() << endl;
            cout << "Shared Date: " << posts[i]->getDate().getDay() << "-" << posts[i]->getDate().getMonth() << "-" << posts[i]->getDate().getYear() << endl;

            pair<int, string>* activities = posts[i]->getActivities();
            if (activities) {
                cout << "Activity: " << activities[0].second << endl;
            } else {
                cout << "No activity" << endl;
            }

            cout << endl; 
        }
    } else {
        cout << "\n---Page with ID " << pageId << " not found.---" << endl;
    }
    };

    void addUser(User* newUser) {
        if (numUsers < maxUsers) {
            users[numUsers] = newUser;
            numUsers++;
        } else {
            cout << "Error: Maximum number of users reached." << endl;
        }
    }
    void initializeUsersFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string userId, firstName, lastName;
            iss >> userId >> firstName >> lastName;

        string userName = firstName + " " + lastName;

            User* newUser = new User(userId, userName);

            string friendId;
            while (iss >> friendId && friendId != "-1") {
                newUser->addFriend(friendId);
            }
            string pageId;
            while (iss >> pageId && pageId != "-1") {
                // Add liked page to the user
                newUser->addLikedPage(pageId);
            }

            addUser(newUser);
        }

        file.close();
    }

                // File handeling for Pages

    void addPage(Page* newPage) {
        if (numPages < maxPages) {
            pages[numPages++] = newPage;
        } else {
            cout << "Error: Maximum number of pages reached. Page not added: " << newPage->getId() << endl;
            delete newPage; 
        }
    }

    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

void initializePagesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) {
            continue; 
        }

        istringstream iss(line);
        string pageId, pageTitle;
        if (!(iss >> pageId) || !getline(iss >> ws, pageTitle)) {
            cout << "Error: Invalid data format in file." << endl;
            continue;
        }

        Page* newPage = new Page(pageId, nullptr, pageTitle);

        addPage(newPage);
    }

    file.close();
}

        //File handeling for Posts

    void initializePostsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty() || line == "-1") {
                continue;
            }

            string postId, description, activityTypeStr, activityValue, ownerId;
            int day, month, year, activityType;

            line = line.substr(0, line.find_first_of('\r')); 
            size_t found = line.find_last_not_of(" \t"); 
            if (found != string::npos) {
                line = line.substr(0, found + 1); 
            }

            postId = line;
            getline(file, line); 
            istringstream dateStream(line);
            dateStream >> day >> month >> year;

            getline(file, description);

            getline(file, line);
            istringstream activityStream(line);
            activityStream >> activityTypeStr;
            getline(activityStream, activityValue); 


            if (!activityTypeStr.empty()) {
                activityType = stoi(activityTypeStr);
            } else {
                continue; 
            }
            getline(file, ownerId);
            Post* newPost = new Post(postId, description, day, month, year,ownerId);
            newPost->addActivity(activityType, activityValue);

            for (int i = 0; i < numPages; ++i) {
                if (pages[i] && pages[i]->getId() == ownerId) {
                    pages[i]->addPost(newPost);
                    break; 
                }
            }

            for (int i = 0; i < numUsers; ++i) {
                if (users[i] && users[i]->getId() == ownerId) {
                    users[i]->addPost(newPost);
                    break; 
                }
            }

            if (numPosts < maxPosts) {
                posts[numPosts++] = newPost;
                int temp = numPosts - 1;
            } else {
                cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
                delete newPost; 
            }

            getline(file, line);
            if (line == "0") {
                newPost->setLikedBy(nullptr);
                continue; 
            }
            istringstream likedByStream(line);
            string likedById;
            while (likedByStream >> likedById) {
                setCurrentUser(likedById);
                likePost(postId);
            }

        }
        file.close();
    }

    void readCommentsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string postId, userId, commentText;
            if (!(iss >> postId >> userId)) {
                cerr << "Error reading file: " << filename << endl;
                continue;
            }
            getline(iss, commentText);

            // Find the post
            Post* post = findPostById(postId);
            if (!post) {
                cerr << "Post with ID " << postId << " not found." << endl;
                continue;
            }

            // Find the user
            User* user = findUserById(userId);
            if (!user) {
                cerr << "User with ID " << userId << " not found." << endl;
                continue;
            }

            Comment* comment = new Comment(commentText,user,post);

            post->addComment(comment);
        }

        file.close();
    }

};

#endif /* SOCIALNETWORKAPP_HPP */