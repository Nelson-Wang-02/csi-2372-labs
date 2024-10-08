/*myFile3.cpp : Ex3 a2 CSI2372A*/

#include <iostream>
using namespace std;

int** triangleInf(int n)
{
	int** p = new int* [n];

	for (int i = 0; i < n; i++) {
		p[i] = new int[i+1];
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i) {
				p[i][j] = 1;
			}
			else {
				p[i][j] = p[i - 1][j - 1] + p[i - 1][j];
			}
		}
	}
	return p;
}

int main() {
	int** tab;
	const int size = 10;
	tab = triangleInf(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
			cout << tab[i][j] << " ";
		cout << endl;
	}
}