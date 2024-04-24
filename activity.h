#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <string>
using namespace std;

class Activity {
private:
    int type;
    string value;

public:
    Activity(int type = 0, string value = ""){};
    ~Activity(){};
     // Getters
    int getType() {return type;};
    string getValue() {return value;};

    //setters
    
    // Declare other methods
};

#endif /* ACTIVITY_HPP */