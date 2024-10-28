/*myFile1a, Ex1 a4 CSI2372A*/

#include <iostream>
using namespace std;

class Course {
    int num;
    int hours;
public:
    Course(int, int); 	//constructor
    int getNum();
    int getHours();
};

Course::Course(int n, int h) {
    num = n;
    hours = h;
}

int Course::getNum() {
    return num;
}

int Course::getHours() {
    return hours;
}



