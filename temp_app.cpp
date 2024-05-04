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
    ~SocialNetworkApp(){};
    //getters
    int getMaxUsers() {return maxUsers;}
    int getMaxPages() {return maxPages;}
    User** getUsers() {return users;}
    Page** getPage() {return pages;}
    void run()
    {
        // User u1("u1","razan");
        // currentUser = &u1;
        // cout<<currentUser->getName()<<endl;
        // Posts[1] = new Post;
        // Posts[1]->setId("post1");
        // cout<<Posts[1]->getId()<<endl;
        // likePost("post1");

        /* for (int i = 0; i < maxUsers; i++)
        {
            cout<<users[i]->getId()<<endl;
        } */

        // for (int i = 0; i < maxPages; i ++)
        // {
        //     cout<<pages[i]->getId()<<endl;
        // }

    //     for (int i = 0; i < maxPosts; i++)
    //     {
    //         cout<<"a"<<endl;
    //         cout<<posts[i]->getId()<<endl;
    //     }
    //     cout<<"----------"<<endl;
    //     for (int i = 0; i < maxPosts; i++)
    //     {
    //         cout<<posts[i]->getLikes();
    //     }
        
    //     cout<<"----------"<<endl;   

        
    //     // for (int i = 0; i < maxPosts; i++)
    //     // {
    //     //     cout<<posts[i]->getLikedBy()[1]->getId()<<endl;
    //     // }

    //     for (int i = 0; i < numPosts; i++) {
    //         User** likedBy = posts[i]->getLikedBy();
    //         if (likedBy != nullptr && likedBy[0] != nullptr) {
    //             cout << likedBy[0]->getId() << endl;
    //         } else {
    //             cout << "No users liked post " << posts[i]->getId() << endl;
    //         }
    // }   
        setCurrentUser("u1");
        likePost("post3");
        viewLikes("post3");
        commentOnPost("post1","what is this");
        setCurrentUser("u2");
        commentOnPost("post1", "how would i know?");
        viewPost("post1");
        shareMemory("post2", "Messed up the project");
        cout<<endl<<endl;
        setCurrentUser("u3");
        Post* tempPost = findPostById("post2");
        cout<<endl<<endl;
        if (tempPost)
            cout<<"owner: "<<tempPost->getOwnerId()<<endl;
        else
            cout<<"shit";
        cout<<"Descriprtion: "<<tempPost->getDescription()<<endl<<endl;
        viewUserTimeline();
        cout<<"-----------------------"<<endl;
        viewFriendList(currentUser->getId());
        cout<<"-----------------------"<<endl;
        viewPage("p1");
        cout<<"-----------------------"<<endl;
        viewPost("post1");
        setCurrentUser("u1");
        setDate(15,11,2017);
        viewHome();



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
    return nullptr; // Return nullptr if page with given ID is not found
}

        //Function to find a post by its Id
    Post* findPostById(const string& postId) {
        for (int i = 0; i < maxPosts; ++i) {
            if (posts[i]->getId() == postId) {
                return posts[i];
            }
        }
        return nullptr; // Post not found
    }

        // Function to view posts of friends shared in the last 24 hours
    void viewPostsOfFriendsInLast24Hours() {
        std::string* friendIds = currentUser->getFriends(); // Get array of friend IDs
        int numFriends = currentUser->getCurrFriends(); // Get the number of friends

        for (int i = 0; i < numFriends; ++i) {
            User* friendUser = findUserById(friendIds[i]); // Find the friend user by ID
            if (friendUser) { // Check if the friend user exists
                std::cout << "Posts from " << friendUser->getName() << ":" << std::endl;
                Post** posts = friendUser->getPosts(); // Get array of posts of the friend user
                int numPosts = friendUser->getCurrPosts(); // Get the number of posts
                for (int j = 0; j < numPosts; ++j) {
                    Post* post = posts[j]; // Get the post at index j
                    if (isPostSharedInLast24Hours(post)) {
                        // std::cout << post->getDescription() << std::endl;
                        viewPost(post->getId());

                    }
                }
            } else {
                std::cout << "Error: Friend with ID " << friendIds[i] << " not found." << std::endl;
            }
        }
    }

    // Function to view posts of liked pages shared in the last 24 hours
    void viewPostsOfLikedPagesInLast24Hours() {
        std::string* likedPageIds = currentUser->getLikedPages(); // Get array of liked page IDs
        int numLikedPages = currentUser->getCurrLikedPages(); // Get the number of liked pages

        for (int i = 0; i < numLikedPages; ++i) {
            Page* likedPage = findPageById(likedPageIds[i]); // Get the liked page by ID
            if (likedPage) { // Check if the liked page exists
                std::cout << "Posts from " << likedPage->getTitle() << ":" << std::endl;
                Post** posts = likedPage->getPosts(); // Get array of posts of the liked page
                int numPosts = likedPage->getCurrPosts(); // Get the number of posts
                for (int j = 0; j < numPosts; ++j) {
                    Post* post = posts[j]; // Get the post at index j
                    if (isPostSharedInLast24Hours(post)) {
                        // std::cout << post->getDescription() << std::endl;
                        viewPost(post->getId());
                    }
                }
            } else {
                std::cout << "Error: Liked page with ID " << likedPageIds[i] << " not found." << std::endl;
            }
        }
    }
    // Function to check if a post is shared in the last 24 hours
    bool isPostSharedInLast24Hours(Post* post) {
        // Date currentDate = currentUser->getCurrentDate();
        Date postDate = post->getDate();
        
        // Calculate the difference in days between post date and current date
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
        // If the user is not found, set currentUser to nullptr
        currentUser = nullptr;
    }

        // Task 2

    void viewHome(){
        std::cout << "Posts from friends shared in last 24 hours:" << std::endl;
        viewPostsOfFriendsInLast24Hours();

        std::cout << "\nPosts from liked pages shared in last 24 hours:" << std::endl;
        viewPostsOfLikedPagesInLast24Hours();
    }

    

        //Task 3
    void likePost(const string& postId){
            // Check if the currentUser is valid
        if (currentUser == nullptr) {
            cout << "Error: Current user not set." << endl;
            return;
        }

        // Find the post with the given postId
        Post* postToLike = nullptr;
        for (int i = 0; i < maxPosts; ++i) {
            if (posts[i] != nullptr && posts[i]->getId() == postId) {
                postToLike = posts[i];
                break;
            }
        }

        // Check if the post was found
        if (postToLike == nullptr) {
            cout << "Error: Post with ID " << postId << " not found." << endl;
            return;
        }

        // Check if the post has already been liked by the currentUser
        for (int i = 0; i < postToLike->getCurrLikedBy(); ++i) {
            if (postToLike->getLikedBy()[i] == currentUser) {
                cout << "You have already liked this post." << endl;
                return;
            }
        }

        // Check if the post has reached the maximum number of likes
        if (postToLike->getCurrLikedBy() >= postToLike->getMaxLikedBy()) {
            cout << "Error: This post has reached the maximum number of likes." << endl;
            return;
        }

        // Like the post
        postToLike->addLike(currentUser);
        //cout << "Post liked successfully." << endl;
    }
            // Task 4

    void viewLikes(const string& postId) {
            // Search for the post with the given Post ID
        Post* post = findPostById(postId);
        if (post != nullptr) {
            User** likedBy = post->getLikedBy();
            int numLikedBy = post->getCurrLikedBy();

            // Check if any users have liked the post
            if (numLikedBy > 0) {
                cout << "List of people who liked the post:" << endl;
                for (int i = 0; i < numLikedBy; ++i) {
                    cout << likedBy[i]->getName() << endl;
                }
            } else {
                cout << "No users have liked the post." << endl;
            }
        } else {
            cout << "Post with ID " << postId << " not found." << endl;
        }
    };

            //Task 5

    void commentOnPost(const string& postId, const string& commentText) {
        // Find the post with the given postId
        Post* targetPost = findPostById(postId);
        // for (int i = 0; i < numPosts; ++i) {
        //     if (posts[i]->getId() == postId) {
        //         targetPost = posts[i];
        //         break;
        //     }
        // }

        // If the post is found, proceed to add the comment
        if (targetPost) {
            // Create a new Comment object
            Comment* newComment = new Comment(commentText, currentUser, targetPost);

            // Add the comment to the post
            targetPost->addComment(newComment);

            // Add the comment to the user who posted it
            currentUser->addComment(newComment);

            // cout << "Comment added successfully!" << endl;
        } else {
            cout << "Error: Post not found with ID " << postId << endl;
        }
    }

        // Task 6

    void viewPost(const string& postId){
        // Retrieve the post by its ID
        Post* post = findPostById(postId);

        //check if the post exists
        if (post) {
        // Display post details
        cout << "Post ID: " << post->getId() << endl;
        cout << "Description: " << post->getDescription() << endl;
        cout << "Likes: " << post->getLikes() << endl;

        // Display activities
        cout << "Activity: ";
        pair<int, string>* activity = post->getActivities();
        if (activity) {
            cout << activity->second << endl;
        } else {
            cout << "No activity." << endl;
        }

        // Display comments
        cout << "Comments:" << endl;
        Comment** comments = post->getComments();
        int numComments = post->getCurrComments();
        for (int i = 0; i < numComments; ++i) {
            Comment* comment = comments[i];
            if (comment) {
                cout << comment->getCommentOwner()->getName() <<": ";
                cout << comment->getComment() << endl;
                cout << "----------------------------------" << endl;
            }
        }
    } else {
        // Handle the case where the post with the given ID does not exist
        cout << "Post with ID " << postId << " does not exist." << endl;
    }

    };

        //          Task 7
        
    void shareMemory(const string& postId, const string& text) {
        // Find the post by ID
        Post* post = findPostById(postId);
        
        // Check if the post exists
        if (post) {
            // Change the description of the post
            post->setDescription(text);
            
            // Call viewPost function to display the updated post
            viewPost(postId);
        } else {
            cout << "Post with ID " << postId << " not found." << endl;
        }
    }   

        //      Task 8

    void viewUserTimeline(){
            // Check if currentUser is set
        if (currentUser) {
            // Display user's name
            cout << "User Name: " << currentUser->getName() << endl;
            
            // Display user's posts
            Post** tempPosts = currentUser->getPosts();
            int numPosts = currentUser->getCurrPosts();
            cout<<"NumPost: "<<numPosts<<endl;
            if (numPosts != 0)
            {
                cout << "User's Posts:" << endl;
                for (int i = 0; i < numPosts; ++i) {
                    cout << "Post ID: " << tempPosts[i]->getId() << endl;
                    cout << "Description: " << tempPosts[i]->getDescription() << endl;
                    cout << "Likes: " << tempPosts[i]->getLikes() << endl;
                    cout << "Date: " << tempPosts[i]->getDate().getDay() << "/" << posts[i]->getDate().getMonth() << "/" << posts[i]->getDate().getYear() << endl;
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
        // Find the user with the given userId
    User* user = findUserById(userId);

        // If the user is found, display their list of friends
        if (user) {
            cout << "Friend List for User " << user->getName() << ":" << endl;
            string* friendIds = user->getFriends();
            int numFriends = user->getCurrFriends();
            for (int i = 0; i < numFriends; ++i) {
                // Find the friend with the current friendId
                User* friendUser = findUserById(friendIds[i]);
                if (friendUser) {
                    cout << "- " << friendUser->getName() << endl;
                }
            }
        } else {
            cout << "User with ID " << userId << " not found." << endl;
        }

    };

        //Task 10

    void viewPage(const string& pageId) {
            // Find the page with the given pageId
        Page* page = findPageById(pageId);

    // If the page is found, display its posts
    if (page) {
        cout << "Posts on Page " << page->getTitle() << ":" << endl<<endl;
        Post** posts = page->getPosts();
        int numPosts = page->getCurrPosts();
        for (int i = 0; i < numPosts; ++i) {
            cout << "Post ID: " << posts[i]->getId() << endl;
            cout << "Description: " << posts[i]->getDescription() << endl;
            cout << "Date: " << posts[i]->getDate().getDay() << "-" << posts[i]->getDate().getMonth() << "-" << posts[i]->getDate().getYear() << endl;

            // Display activity if available
            pair<int, string>* activities = posts[i]->getActivities();
            // int numActivities = posts[i]->getCurrActivities();
            if (activities) {
                cout << "Activity: " << activities[0].second << endl;
            } else {
                cout << "No activity" << endl;
            }

            cout << endl; // Add a blank line for separation
        }
    } else {
        cout << "Page with ID " << pageId << " not found." << endl;
    }
    };

            // File handeling for user
    void addUser(User* newUser) {
        // Check if there is enough space to add a new user
        if (numUsers < maxUsers) {
            // Add the new user to the array
            users[numUsers] = newUser;
            // Increment the count of current users
            numUsers++;
        } else {
            // Handle the case where the array is full
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

        // Combine the first name and last name into the full name
        string userName = firstName + " " + lastName;

            // Create a new User object
            User* newUser = new User(userId, userName);

            // Parse friends
            string friendId;
            while (iss >> friendId && friendId != "-1") {
                // Add friend to the user
                newUser->addFriend(friendId);
            }

            // Parse liked pages
            string pageId;
            while (iss >> pageId && pageId != "-1") {
                // Add liked page to the user
                newUser->addLikedPage(pageId);
            }

            // Store the new user in the users array
            // (You need to implement a method to add users to the array)
            addUser(newUser);
        }

        file.close();
    }

                // File handeling for Pages

void addPage(Page* newPage) {
    // Check if there is enough space to add a new page
    if (numPages < maxPages) {
        // Add the new page to the array
        pages[numPages++] = newPage;
        //cout << "Page added: " << newPage->getId() << " - " << newPage->getTitle() << endl; // Debugging output
    } else {
        // Handle the case where the array is full
        cout << "Error: Maximum number of pages reached. Page not added: " << newPage->getId() << endl;
        delete newPage; // Delete the newly created page since it's not added to the array
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
        // Trim leading and trailing whitespace from the line
        line = trim(line);
        if (line.empty()) {
            continue; // Skip empty lines
        }

        istringstream iss(line);
        string pageId, pageTitle;
        if (!(iss >> pageId) || !getline(iss >> ws, pageTitle)) {
            cout << "Error: Invalid data format in file." << endl;
            continue;
        }

        // Create a new Page object
        Page* newPage = new Page(pageId, nullptr, pageTitle);

        // Add the new page to the pages array
        addPage(newPage);
    }

    file.close();
}

        //File handeling for Posts
/* 
// void initializePostsFromFile(const string& filename, Post** posts, int& numPosts, const int maxPosts, User** users, const int numUsers, Page** pages, const int numPages) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cout << "Error: Unable to open file " << filename << endl;
//         return;
//     }

//     string line;
//     while (getline(file, line)) {
//         // Skip empty lines
//         if (line.empty()) {
//             continue;
//         }

//         // Parse post data
//         string postId, description, activityTypeStr, activityValue, ownerId;
//         int day, month, year, activityType;
        
//         istringstream iss(line);
//         iss >> postId >> day >> month >> year;
//         getline(file, description);
//         getline(file, line);
//         istringstream activityStream(line);
//         activityStream >> activityTypeStr >> ws;
//         getline(activityStream, activityValue);
//         activityType = stoi(activityTypeStr);
//         getline(file, ownerId);

//         // Create a new Post object
//         Post* newPost = new Post(postId, description, day, month, year);
//         newPost->addActivity(activityType, activityValue);

//         // Determine owner (user or page) and set it
//         bool isPageOwner = false;
//         for (int i = 0; i < numUsers; ++i) {
//             if (users[i]->getId() == ownerId) {
//                 newPost->setOwner(users[i]);
//                 break;
//             }
//         }
//         if (!newPost->getOwner()) {
//             for (int i = 0; i < numPages; ++i) {
//                 if (pages[i]->getId() == ownerId) {
//                     newPost->setOwner(pages[i]);
//                     isPageOwner = true;
//                     break;
//                 }
//             }
//         }
//         newPost->setIsPageOwner(isPageOwner);

//         // Read liked users/pages
//         while (getline(file, line)) {
//             if (line == "-1") {
//                 break; // End of liked users/pages
//             }
//             if (isPageOwner) {
//                 // Assuming the line contains the ID of the user who liked the post
//                 for (int i = 0; i < numUsers; ++i) {
//                     if (users[i]->getId() == line) {
//                         newPost->addLikedBy(users[i]);
//                         break;
//                     }
//                 }
//             } else {
//                 // Assuming the line contains the ID of the page that liked the post
//                 for (int i = 0; i < numPages; ++i) {
//                     if (pages[i]->getId() == line) {
//                         newPost->addLikedBy(pages[i]);
//                         break;
//                     }
//                 }
//             }
//         }

//         // Add the new post to the posts array
//         if (numPosts < maxPosts) {
//             posts[numPosts++] = newPost;
//         } else {
//             cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
//             delete newPost; // Free memory to prevent memory leaks
//         }
//     }

//     file.close();
// }
 */
/* 
//     void initializePostsFromFile(const string& filename, Post** posts, int& numPosts, const int maxPosts, User** users, const int numUsers, Page** pages, const int numPages) {
//         ifstream file(filename);
//         if (!file.is_open()) {
//             cout << "Error: Unable to open file " << filename << endl;
//             return;
//         }

//         string line;
//         while (getline(file, line)) {
//             // Skip empty lines
//             if (line.empty()) {
//                 continue;
//             }

//         // Parse post data
//         string postId, description, activityTypeStr, activityValue, ownerId;
//         int day, month, year, activityType;
        
//         istringstream iss(line);
//         iss >> postId >> day >> month >> year;
//         getline(file, description);
//         getline(file, line);
//         istringstream activityStream(line);
//         activityStream >> activityTypeStr >> ws;
//         getline(activityStream, activityValue);
//         activityType = stoi(activityTypeStr);
//         getline(file, ownerId);

//         // Create a new Post object
//         Post* newPost = new Post(postId, description, day, month, year);
//         newPost->addActivity(activityType, activityValue);

//         // Add the new post to the posts array
//         if (numPosts < maxPosts) {
//             posts[numPosts++] = newPost;
//         } else {
//             cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
//             delete newPost; // Free memory to prevent memory leaks
//         }

//         // Add the post to the owner's posts array
//         newPost->addPostToOwner(users, numUsers, pages, numPages);
//     }

//     file.close();
// }
 */
 /* 
    // void initializePostsFromFile(const string& filename) {
    //     ifstream file(filename);
    //     if (!file.is_open()) {
    //         cout << "Error: Unable to open file " << filename << endl;
    //         return;
    //     }

    //     string line;
    //     while (getline(file, line)) {
    //         // Skip empty lines
    //         if (line.empty()) {
    //             continue;
    //         }

    //         // Parse post data
    //         string postId, description, activityTypeStr, activityValue, ownerId;
    //         int day, month, year, activityType;

    //         istringstream iss(line);
    //         iss >> postId >> day >> month >> year;
    //         cout<<postId<<"--"<<day<<"--"<<month<<"--"<<year<<endl;
    //         getline(file, description);
    //         cout<<description<<endl;
    //         getline(file, line);
    //         cout<<line<<endl;
    //         istringstream activityStream(line);
    //         activityStream >> activityTypeStr >> ws;
    //         getline(activityStream, activityValue);
    //         activityType = stoi(activityTypeStr);
    //         getline(file, ownerId);
    //         cout<<ownerId;

    //         // Create a new Post object
    //         Post* newPost = new Post(postId, description, day, month, year);
    //         newPost->addActivity(activityType, activityValue);

    //         // Find the owner based on the ownerId and add the post to the owner
    //         for (int i = 0; i < numPages; ++i) {
    //             if (pages[i] && pages[i]->getId() == ownerId) {
    //                 // Add the post to the page
    //                 pages[i]->addPost(newPost);
    //                 break; // Exit the loop after adding the post
    //             }
    //         }
    //         // If owner is not found among pages, search among users
    //         for (int i = 0; i < numUsers; ++i) {
    //             if (users[i] && users[i]->getId() == ownerId) {
    //                 // Add the post to the user
    //                 users[i]->addPost(newPost);
    //                 break; // Exit the loop after adding the post
    //             }
    //         }

    //         // Add the new post to the posts array
    //         if (numPosts < maxPosts) {
    //             posts[numPosts++] = newPost;
    //         } else {
    //             cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
    //             delete newPost; // Free memory to prevent memory leaks
    //         }
    //     }

    //     file.close();
    // }
 */
/*    
    void initializePostsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines and the line indicating end of post
        if (line.empty() || line == "-1") {
            continue;
        }

        // Parse post data
        string postId, description, activityTypeStr, activityValue, ownerId;
        int day, month, year, activityType;

        // Post ID
        postId = line;
        getline(file, line); // Read next line (Day, Month, Year)
        istringstream dateStream(line);
        dateStream >> day >> month >> year;

        // Description
        getline(file, description);

        // Activity Type and Value
            getline(file, line);
    istringstream activityStream(line);
    activityStream >> activityTypeStr >> activityValue;

    // Check if activityTypeStr is empty before converting it to an integer
    if (!activityTypeStr.empty()) {
        activityType = stoi(activityTypeStr);
    } else {
        // Handle the case where activityTypeStr is empty
        continue; // Skip to the next iteration of the loop
    }

        // Owner ID
        getline(file, ownerId);


        // Create a new Post object
        Post* newPost = new Post(postId, description, day, month, year);
        newPost->addActivity(activityType, activityValue);

        // Find the owner based on the ownerId and add the post to the owner
        for (int i = 0; i < numPages; ++i) {
            if (pages[i] && pages[i]->getId() == ownerId) {
                // Add the post to the page
                pages[i]->addPost(newPost);
                break; // Exit the loop after adding the post
            }
        }
        // If owner is not found among pages, search among users

        for (int i = 0; i < numUsers; ++i) {
            if (users[i] && users[i]->getId() == ownerId) {
                // Add the post to the user
                users[i]->addPost(newPost);
                break; // Exit the loop after adding the post
            }
        }

        // Add the new post to the posts array
        if (numPosts < maxPosts) {
            posts[numPosts++] = newPost;
        } else {
            cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
            delete newPost; // Free memory to prevent memory leaks
        }
    }

    file.close();
}
 */

    void initializePostsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            // Skip empty lines and the line indicating end of post
            if (line.empty() || line == "-1") {
                continue;
            }

            // Parse post data
            string postId, description, activityTypeStr, activityValue, ownerId;
            int day, month, year, activityType;

            line = line.substr(0, line.find_first_of('\r')); // Remove any carriage return characters
            size_t found = line.find_last_not_of(" \t"); // Find the index of the last non-whitespace character
            if (found != string::npos) {
                line = line.substr(0, found + 1); // Remove trailing whitespace characters
            }

            postId = line;
            getline(file, line); // Read next line (Day, Month, Year)
            istringstream dateStream(line);
            dateStream >> day >> month >> year;

            // Description
            getline(file, description);

            // Activity Type and Value
            // getline(file, line);
            // istringstream activityStream(line);
            // activityStream >> activityTypeStr >> activityValue;

            // Activity Type and Value
            getline(file, line);
            istringstream activityStream(line);
            activityStream >> activityTypeStr;
            getline(activityStream, activityValue); // Read the entire line as the activity value


            // Check if activityTypeStr is empty before converting it to an integer
            if (!activityTypeStr.empty()) {
                activityType = stoi(activityTypeStr);
            } else {
                // Handle the case where activityTypeStr is empty
                continue; // Skip to the next iteration of the loop
            }
            // Owner ID
            getline(file, ownerId);
            // Create a new Post object
            Post* newPost = new Post(postId, description, day, month, year,ownerId);
            newPost->addActivity(activityType, activityValue);

            // Find the owner based on the ownerId and add the post to the owner
            for (int i = 0; i < numPages; ++i) {
                if (pages[i] && pages[i]->getId() == ownerId) {
                    // Add the post to the page
                    pages[i]->addPost(newPost);
                    break; // Exit the loop after adding the post
                }
            }
            // If owner is not found among pages, search among users

            for (int i = 0; i < numUsers; ++i) {
                if (users[i] && users[i]->getId() == ownerId) {
                    // Add the post to the user
                    users[i]->addPost(newPost);
                    break; // Exit the loop after adding the post
                }
            }

            // Add the new post to the posts array
            if (numPosts < maxPosts) {
                // cout<<newPost->getId()<<" "<<newPost->getOwnerId()<<endl;
                posts[numPosts++] = newPost;
                int temp = numPosts - 1;
                // cout<<posts[temp]->getOwnerId()<<endl;
            } else {
                cout << "Warning: Maximum number of posts reached. Some posts may not be added." << endl;
                delete newPost; // Free memory to prevent memory leaks
            }

            // Read the line containing user IDs who liked the post
            getline(file, line);
            if (line == "0") {
                newPost->setLikedBy(nullptr);
                continue; // Skip to the next iteration of the loop
            }
            istringstream likedByStream(line);
            string likedById;
            while (likedByStream >> likedById) {
                // Set the current user using the likedById
                setCurrentUser(likedById);
                // Like the post using the postId
                likePost(postId);
            }

        }
        file.close();
    }

    // Function to read comments from file and store them in the posts
    void readCommentsFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string postId, userId, commentText;
            if (!(iss >> postId >> userId)) {
                std::cerr << "Error reading file: " << filename << std::endl;
                continue;
            }
            std::getline(iss, commentText);

            // Find the post
            Post* post = findPostById(postId);
            if (!post) {
                std::cerr << "Post with ID " << postId << " not found." << std::endl;
                continue;
            }

            // Find the user
            User* user = findUserById(userId);
            if (!user) {
                std::cerr << "User with ID " << userId << " not found." << std::endl;
                continue;
            }

            // Create a new Comment object
            Comment* comment = new Comment(commentText,user,post);

            // Add the comment to the post
            post->addComment(comment);
        }

        file.close();
    }

};

#endif /* SOCIALNETWORKAPP_HPP */

int main()
{
    SocialNetworkApp app;
    app.run();
}