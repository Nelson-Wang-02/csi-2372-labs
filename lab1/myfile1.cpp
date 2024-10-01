#include "myfile1.h"

using namespace std;

// main function: output results to console.
int main() {

	int user_int; 
	double user_double;
	char user_char;

	cout << "Size in bytes of a character: " << sizeof(char) << endl;
	cout << "Size in bytes of an integer: " << sizeof(int) << endl;
	cout << "Size in bytes of a float: " << sizeof(float) << endl;
	cout << "Size in bytes of a double: " << sizeof(double) << endl;
	cout << "Size in bytes of a short integer: " << sizeof(short int) << endl;
	cout << "Size in bytes of an unsigned integer: " << sizeof(unsigned int) << endl;

	cout << "Enter an Integer: ";
	cin >> user_int; 

	cout << "Number in decimal: " << user_int << endl; 
	cout << "Number in octal: " << oct << user_int << endl;
	cout << "Number in hexa: " << hex << user_int << endl;

	printf("Number in decimal: %d \n", user_int);
	printf("Number in octal: %o \n", user_int);
	printf("Number in hexa: %x \n", user_int);

	cout << "Enter a real number: ";
	cin >> user_double;

	// Set three significant figures.
	cout << setprecision(3) << user_double << endl;
	cout << setprecision(2) << scientific << user_double << endl;

	cout << "Enter a character: ";
	cin >> user_char;

	cout << user_char << endl;
	printf("%d\n", user_char);

	return 0;
}