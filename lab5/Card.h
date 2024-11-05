#include <iostream>
using namespace std;
#include <cassert> //for assert()

enum color { club, diamond, heart, spade };

class Card {
public:
    Card(color c = club, int v = 1);
    int value() { return val; }
    void write();
private:
    color col;
    int val;
};

/*Constructor*/
Card::Card(color c, int v) {
    assert(v >= 1 && v <= 13); //we use a standard function void assert (int expression)
    //which indicates an error message if the expression is false.
    col = c;
    val = v;
}

void Card::write() {
    string out;
    string suit;
    if (col == 0) {
        suit = "Clubs";
    }
    else if (col == 1) {
        suit = "Diamonds";
    }
    else if (col == 2) {
        suit = "Hearts";
    }
    else {
        suit = "Spades";
    }


    if (val == 11) {
        out = "Jack";
        cout << out << " of " << suit << endl;
    }
    else if (val == 12) {
        out = "Queen";
        cout << out << " of " << suit << endl;
    }
    else if (val == 13) {
        out = "King";
        cout << out << " of " << suit << endl;
    }
    else if (val == 1) {
        out = "Ace";
        cout << out << " of " << suit << endl;
    }
    else {
        cout << val << " of " << suit << endl;
    }
}
