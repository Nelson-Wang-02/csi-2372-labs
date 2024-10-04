/*code*/
#include <iostream>
using namespace std;
int main(void) {
	int tab[10];
	int* p;
	for (int i = 0; i < 10; i++) {
		tab[i] = i * i;
	}

	cout << tab[2] << endl;
	cout << tab[1] << endl;

	tab[2] = tab[1];

	cout << tab[2] << endl;

	tab[2] = *(tab + 1);

	*(tab + 2) = tab[1];

	cout << *(tab + 2) << endl;

	*(tab + 2) = *(tab + 1);

	cout << *(tab + 2) << endl;

	p = &tab[0];
	p = tab + 1;

	tab[4] = *p;

	cout << tab[4] << endl;

}