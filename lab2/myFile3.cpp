/*myFile3.cpp : Ex3 a2 CSI2372A*/

#include <iostream>
#include <vector>
using namespace std;

int** triangleInf(int n)
{
	//YOUR CODE
	int p = 0;

	vector<vector<int>> grid(n, vector<int>(n));

	for (int i = 0; i <= n; i++) {

		for (int j = 0; j <= p; p++) {

			if (j == 0) {
				cout << 1;
			}

			else {

			}

			

		}
		cout << endl;
		p++;
	}

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