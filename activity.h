#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <string>
using namespace std;

class Activity {
private:
    int type;
    string value;

public:
    Activity(int t = 0, string val = ""): type(t), value(val) {};
    ~Activity(){};

     // Getters
     
    int getType() {return type;};
    string getValue() {return value;};
    
};

#endif /* ACTIVITY_HPP */