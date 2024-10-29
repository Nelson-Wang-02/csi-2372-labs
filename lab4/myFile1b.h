/*myFile1b.h, Ex1 a4 CSI2372A*/


#include <iostream>
using namespace std;

class Student {
	int numID;
	int nbCourses;
	int maxCourses;
	int* List_grades;
	Course** List_courses;
public:
	Student(int, int); 	//constructor
	~Student(); 		//destructor
	double average();
	int totalHours();
	bool addCourse(Course*, int);
};

Student::Student(int id, int mc) {
	numID = id;
	nbCourses = 0;
	maxCourses = mc;
	List_grades = new int[maxCourses];
	List_courses = new Course * [maxCourses];

	for (int i = 0; i < maxCourses; i++) {
		List_courses[i] = new Course(0, 0);
	}
}

Student::~Student() {
	delete[] List_grades;
	delete[] List_courses;
}

double Student::average() {
	double avg = 0.0; 

	for (int i = 0; i < nbCourses; i++) {
		avg += List_grades[i];
	}

	return (avg / nbCourses);
}

int Student::totalHours() {
	int hrs = 0;
	
	for (int i = 0; i < maxCourses; i++) {

		hrs += List_courses[i]->getHours();

	}

	return hrs;
}

bool Student::addCourse(Course* course, int grade) {

	if (nbCourses == maxCourses) {
		return false;
	}
	
	List_courses[nbCourses] = course;
	List_grades[nbCourses] = grade;

	nbCourses++;

	return true;
}

