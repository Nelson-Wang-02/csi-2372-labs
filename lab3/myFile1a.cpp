/*Ex1a - a3 CSI2372A*/

#include <iostream>
using namespace std;

enum Color { club, diamond, spades, heart };
enum Face { seven, eight, nine, ten, jack, queen, king, ace };

struct Card{
	Color color;
	Face face;
};

int main(){
	Card game[32];
	//YOUR CODE HERE
	int k = 0;

	for (int i = club; i <= heart; i++) {

		for (int j = seven; j <= ace; j++) {
			
			Color color = static_cast<Color>(i);
			Face face = static_cast<Face>(j);

			Card c = {color, face};

			game[k] = c;

			k++;
		}

	}


}

