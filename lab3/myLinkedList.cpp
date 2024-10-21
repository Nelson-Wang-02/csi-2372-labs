/*Ex2 - a3 CSI2372A*/

#include "myLinkedList.h"

int main()
{
	int choice; 
	int number;
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
		case 1: 
			display(first);
			break;

		case 2:  
			cout << "After which element do you want to insert into? (0 for start): ";
			cin >> number;

			first = add(first, number);

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

	if (chk_pos(p, number) == false && number != 0) {
		cout << "A preceding element does not exist. Cannot insert." << endl;
		return p;
	}

	// newlines in buffer will skip inputs. Ignore them so this doesn't happen.
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

	if (number == 0) {
		p = eval;
	}
	// Loop through the linked list and insert.
	else {
		Evaluation* current = p;

		for (int i = 0; i < number - 1; i++) {
			current = current->next;
		}

		current->next = eval;
	}

	return p;

}


/**
*remove() Function*
**/

Evaluation* remove(Evaluation* p, int& number)
{
	//YOUR CODE COMES HERE
	return NULL;
}



/**
*display() Function *
**/
void display(Evaluation* p)
{
	//YOUR CODE COMES HERE

	Evaluation* current = p;

	while (current != nullptr) {
		cout << "Student: " << current->student << endl;
		cout << "Grade: " << current->grade << endl; 

		current = current->next;
	}

}



/**
*average() Function *
***/
int average(Evaluation* p, int const& nbre)
{
	//YOUR CODE COMES HERE
	return NULL;
}

/** 
 user-defined chk_pos() Function
 Checks if it is possible to reach the defined index by ensuring that there are preceding elements.
**/

bool chk_pos(Evaluation* head, int& index) {

	int i = 0;

	Evaluation* current = head;

	while (current != nullptr) {

		if (i == index - 1) {
			return true;
		}

		current = current->next;

		i++;
	}

	return false;
}





