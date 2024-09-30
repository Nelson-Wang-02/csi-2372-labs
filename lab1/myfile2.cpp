#include "myfile2.h"

using namespace std;

const double Pi = 3.14159;

// Add global count variables so that nsurface and nvolume are passed the proper values.
int count_vol = 0;
int count_sur = 0;

/*
1. 

The main function does the following: 

	if choice == 1: calculate area of disk/circle
	if choice == 2: calculate volume of cylinder
	if choice == 3: exit the program.
	else: nothing.
*/

/* 2. i) Surface function : Calculate area of a circle or surface area of disk. Returns the number of calls to the function.
* Inputs: 
*	- ray: double; constant real number passed by reference.
* 
* Output: 
*	- count_sur : int;
*/
int surface(double const& ray) {

	cout << "The surface is: " << (Pi * ray * ray) << endl;

	return ++count_sur;
}

/* 2. ii) Calculate volume of cylinder. Returns the number of calls to the function.
* Inputs: 
*	- ray : double; constant real number passed by reference.
*	- height : double; constant real number passed by reference.
* 
* Output:
*	- count_vol : int;
*/
int volume(double const& ray, double const& height) {

	cout << "The volume is: " << (Pi * ray * ray * height) << endl;

	return ++count_vol;
}

/* menu Function: displays an option menu and returns the chosen option*/
char menu(void) {
	char choice;
	cout << "What do you want to do?:" << endl << endl;
	cout << "\t-Calculate the area of a disk from a radius (Press 1)" << endl << endl;
	cout << "\t-Calculate the volume of a cylinder from a radius and a height (Press 2)" << endl << endl;
	cout << "\t-Exit the program (press 3)" << endl << endl;
	cout << "Your choice:";
	cin >> choice;
	return (choice);
	cout << endl;
}

/*main Function*/
int main() {
	char choice;
	int nvolume = 0; //number of times the volume function has been executed
	int nsurface = 0; // number of times the surface function has been executed
	double radius, height;
	while (1)
	{
		choice = menu();
		switch (choice)
		{
		case '1': cout << endl << "Surface calculation" << endl;
			cout << "Enter the radius:";
			cin >> radius;
			nsurface = surface(radius);
			break;
		case '2': cout << endl << "Volume calculation" << endl;
			cout << " Enter the radius:";
			cin >> radius;
			cout << " Enter the height:";
			cin >> height;
			nvolume = volume(radius, height);
			break;
		case '3': cout << endl << "Exit the program" << endl;
			cout << "The volume function has been executed" << nvolume << "times" << endl;
			cout << "The surface function has been executed" << nsurface << "times" << endl;
			exit(0);
		default: break;
		}
	}
}

