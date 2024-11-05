
#include <iostream>
using namespace std;

#include "myFile.h"
#include "Card.h"
#include "CardsSet.h"
#include "Player.h"

int main() {
	CardsSet packet;
	Player you(packet, false);
	Player me(packet, true);
	char answer[3];
	bool continuous = true;
	cout << "Hello! " << endl;
	while (continuous)
	{
		cout << "A new game? " << endl;
		cin >> answer;
		continuous = answer[0] == 'y';
		if (continuous)
		{
			packet.novSet();
			packet.shuffle();
			packet.take();
			int p1 = you.play();
			if (p1 > 21) {
				cout << "You lost! " << endl;
			}
			else if (p1 == 21) {
				cout << "You won! " << endl;
			}
			else // the computer must play
			{
				int p2 = me.play();
				if (p2 <= 21 && p2 >= p1) {
					cout << "You lost! " << endl;
				}
				else {
					cout << "You won! " << endl;
				}
			}
		}
	}
	return 0;
}

int Player::play() {
	inHand.empty();
	bool hit = true;
	char answer;

	if (computer == true) {
		while (countPoints() < 17 && packet.numCards() > 0) {
			inHand.put(packet.take());
		}
	}
	else {
		do {
			if (packet.numCards() > 0) {
				inHand.put(packet.take());
				Card top = inHand.lookIn(inHand.numCards() - 1);
				cout << "You get Card: ";
				top.write();
				cout << endl;
				cout << "Your score is: " << countPoints() << " points" << endl;
				if (countPoints() > 21) {
					break;
				}
				cout << "Any additional Card ? ";
				cin >> answer;
				hit = (answer == 'y' || answer == 'Y');
			}
			else {
				cout << "No more cards available in the deck " << endl;
				break;
			}
		} while (hit && countPoints() <= 21);
	}
	return countPoints();
}

int Player::countPoints() {
	int total = 0;
	int aces = 0;

	for (int i = 0; i < inHand.numCards(); i++) {
		int val = inHand.lookIn(i).value();

		if (val >= 11 && val <= 13) {
			total += 10;
		}
		else if (val == 1) {
			aces++;
			total += 14;
		}
		else {
			total += val;
		}
	}
	
	while (total > 21 && aces > 0) {
		total -= 13;
		aces--;
	}

	return total;
}

