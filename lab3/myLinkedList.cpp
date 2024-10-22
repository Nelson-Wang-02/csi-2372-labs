/*Ex2 - a3 CSI2372A*/

#include "myLinkedList.h"

int main()
{
	int choice; 
	int number = 0; // Size or Number of elements in linked list.
	Evaluation* first = nullptr;

	do
	{
		cout << endl << endl << "1) Display  of the complete linked list.\n";
		cout << "2) Insert an element\n";
		cout << "3) Remove an element.\n";
		cout << "4) Calculation of the class average.\n";
		cout << "5) Exit the program.\n" << endl << endl;
		cout << "Your choice ??:";
		cin >> choice;

		switch (choice)
		{
		case 1: display(first);
			break;

		case 2: first = add(first, number);
			break;
			
		case 3: first = remove(first, number);
			break;

		case 4: average(first, number);
			break;

		case 5: exit(0);

		default:
			break;
		}
	} while (1);
	return 0;
}



/*
*add() Function*
**/
Evaluation* add(Evaluation* p, int& number)
{
	//YOUR CODE COMES HERE
	int user_pos;

	// Based on the output example, we are assuming that the first element of the linked list is index 0. 
	// "After which element" is then interpreted as "At which element" to maintain the behavior seen in the output example.
	cout << "At which element do you want to insert into? (0 for start): ";
	cin >> user_pos;

	if (user_pos < 0 || user_pos > number) {
		cout << endl << "A preceding element does not exist. Cannot insert." << endl;
		return p;
	}

	// newlines in buffer will cause inputs to be skipped. Ignore them so this doesn't happen.
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	char student[20];
	int grade;

	cout << "Enter the student: ";
	cin.getline(student, 20);

	cout << "Enter the grade: ";
	cin >> grade;

	Evaluation* eval = new Evaluation;

	strcpy_s(eval->student, student);
	eval->grade = grade;
	eval->next = nullptr;

	if (user_pos == 0) {
		p = eval;
	}
	// Loop through the linked list and insert.
	else {
		Evaluation* current = p;

		for (int i = 1; i < user_pos; i++) {
			current = current->next;
		}

		current->next = eval;
	}

	// Update the number of existing elements in the linked list.
	number++;

	return p;

}


/**
*remove() Function*
**/

Evaluation* remove(Evaluation* p, int& number)
{
	int user_pos;
	
	// Contrary to adding an element, the behavior seen in the output example now assumes that the first element of the linked list is of index 1.
	cout << "What is the number of the element to delete? ";
	cin >> user_pos;

	if (user_pos < 1 || user_pos > number) {
		cout << "Invalid index" << endl;
		return p;
	}

	Evaluation* current = p;
	Evaluation* prev = nullptr;

	if (user_pos == 1) {
		p = current -> next;
		delete current;
		return p;
	}

	for (int i = 1; i < user_pos; ++i) {
		prev = current;
		current = current->next;
	}

	prev->next = current->next;

	delete current;

	number--;

	return p;
}



/**
*display() Function *
**/
void display(Evaluation* p)
{
	//YOUR CODE COMES HERE

	Evaluation* current = p;

	while (current != nullptr) {
		cout << endl << "Student: " << current->student << endl;
		cout << "Grade: " << current->grade << endl; 

		current = current->next;
	}

}



/**
*average() Function *
***/
int average(Evaluation* p, int const& nbre)
{
	if (nbre == 0 || p == nullptr) {
		cout << "All did not go well" << endl;
		return 0;
	}

	Evaluation* current = p;
	int total = 0;

	while (current != nullptr) {
		total += current->grade;
		current = current->next;
	}

	float avg = static_cast<float>(total) / nbre;
	cout << "The average is : " << avg << endl;

	return 1;
}

