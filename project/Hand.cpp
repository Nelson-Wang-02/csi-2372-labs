#include "Hand.h"

//Constructor for reconstructing hand from file
Hand::Hand(std::istream& in, const CardFactory* factory) {
    std::string cardName;
    while (in >> cardName) {
        Card* card = factory->createCard(cardName);
        if (card) {
            cards.push_back(card);
        }
    }
}

Hand& Hand::operator+=(Card* card) {
    cards.push_back(card);
    return *this;
}

// Removes and returns top card from player hand
Card* Hand::play() {
    if (cards.empty()) {
        throw std::runtime_error("Hand is empty. Cannot play a card.");
    }
    Card* topCard = cards.front();
    cards.pop_front();
    return topCard;
}

//Returns top card from player hand (without remove)
Card* Hand::top() const {
    if (cards.empty()) {
        throw std::runtime_error("Hand is empty. No top card available.");
    }
    return cards.front();
}

//Returns and removes card at given index
Card* Hand::operator[](int index) {
    if (index < 0 || index >= static_cast<int>(cards.size())) {
        throw std::out_of_range("Index out of range.");
    }

    auto it = cards.begin();
    std::advance(it, index);
    Card* card = *it;
    cards.erase(it);
    return card;
}

// This should be top-level but since hand is hidden, we only use this for outputting to a file.
std::ostream& operator<<(std::ostream& out, const Hand& hand) {

    if (hand.top()) {
        for (const auto& card : hand.cards) {
            card->print(out);
            out << " ";
        }
    } 
    else {
        out << "e";
    }



    return out;
}

// Getter for cards
std::list<Card*>& Hand::getCards() {
    return cards;
}