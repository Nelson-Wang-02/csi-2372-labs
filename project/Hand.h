#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <list>
#include <iostream>
#include <stdexcept>

class Hand {
private:
    std::list<Card*> cards;

public:
    //Constructor for loading game from file
    Hand(std::istream& in, const CardFactory* cardFactory) {
        std::string cardType;
        while (in >> cardType) {
            cards.push_back(cardFactory->createCard(cardType));
        }
    }

    Hand& operator+=(Card* card) {
        cards.push_back(card);
        return *this;
    }

    // Removes and returns top card from player hand
    Card* play() {
        if (cards.empty()) {
            throw std::runtime_error("Hand is empty. Cannot play a card.");
        }
        Card* topCard = cards.front();
        cards.pop_front();
        return topCard;
    }

    //Returns top card from player hand (without remove)
    Card* top() const {
        if (cards.empty()) {
            throw std::runtime_error("Hand is empty. No top card available.");
        }
        return cards.front();
    }

    //Returns and removes card at given index
    Card* operator[](int index) {
        if (index < 0 || index >= static_cast<int>(cards.size())) {
            throw std::out_of_range("Index out of range.");
        }

        auto it = cards.begin();
        std::advance(it, index);
        Card* card = *it;
        cards.erase(it);
        return card;
    }

    //Prints all cards in Hand
    void print(std::ostream& out) const {
        for (const auto& card : cards) {
            out << *card << " ";
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Hand& hand) {
        hand.print(out);
        return out;
    }
};