class CardsSet {
public:
    CardsSet() : number(0) {}
    void novSet();
    void shuffle();
    int numCards() { return number; }
    Card take();
    void put(Card k);
    Card lookIn(int no);
    void empty() { number = 0; }
private:
    Card set[52];
    int number;
};

// Create a new set that corresponds to the 52 cards.
void CardsSet::novSet() {
    number = 52;

    int k = 0;

    for (int i = club; i <= spade; i++) { 
        for (int j = 1; j < 14; j++) {
            Card c(static_cast<color>(i), j);

            set[k] = c;

            k++;
        }
    }
}

// Shuffle cards.
void CardsSet::shuffle() {
    srand(time(0));

    //fisher-yates shuffle algorithm
    for (int i = number - 1; i > 0; i--) {
        int rand_index = rand() % (i + 1); // Index between 0 and i.

        swap(set[i], set[rand_index]);
    }

}

// Take a card from the set.
Card CardsSet::take() {

    if (number <= 0) {
        cout << "There are no more cards in the set!" << endl;
        return set[number];
    }

    Card c = set[number - 1];

    number--;

    return c;
}

// Put a card on the set.
void CardsSet::put(Card k) {

    set[number] = k;

    number++;
} 

// Find out the card in position "no" in the set. 
// Assumption: "no" is from 1 to 52 inclusive.
Card CardsSet::lookIn(int no){

    if (no > number) {
        cout << "Invalid position: over number of available cards." << endl;

        return set[no];
    }  

    Card c = set[no];

    return c;
}