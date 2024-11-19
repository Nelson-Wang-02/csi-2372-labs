#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

class Deck : public std::vector<Card*> {
public:
    //Constructor for loading game from file
    Deck(std::istream& in, const CardFactory* cardFactory) {
        std::string cardType;
        while (in >> cardType) {
            this->push_back(cardFactory->createCard(cardType));
        }
    }

    //Draw top card from deck
    Card* draw() {
        if (this->empty()) {
            throw std::runtime_error("Deck is empty. Cannot draw a card.");
        }
        Card* topCard = this->back();
        this->pop_back();
        return topCard;
    }

    friend std::ostream& operator<<(std::ostream& out, const Deck& deck) {
        for (const auto& card : deck) {
            out << *card << " ";
        }
        return out;
    }
};