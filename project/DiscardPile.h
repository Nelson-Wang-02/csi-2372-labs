#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <vector>
#include <iostream>
#include <stdexcept>

class DiscardPile {
private:
    std::vector<Card*> pile;

public:
    //Constructor for loading game from file
    DiscardPile(std::istream& in, const CardFactory* cardFactory) {
        std::string cardType;
        while (in >> cardType) {
            pile.push_back(cardFactory->createCard(cardType));
        }
    }

    // Discards a card
    DiscardPile& operator+=(Card* card) {
        pile.push_back(card);
        return *this;
    }

    // Removes and returns top card from discard pile
    Card* pickUp() {
        if (pile.empty()) {
            throw std::runtime_error("DiscardPile is empty");
        }
        Card* topCard = pile.back();
        pile.pop_back();
        return topCard;
    }

    // Returns top card from discard pile (without remove)
    Card* top() const {
        if (pile.empty()) {
            throw std::runtime_error("DiscardPile is empty");
        }
        return pile.back();
    }

    void print(std::ostream& out) const {
        for (const auto& card : pile) {
            out << *card << " ";
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& discardPile) {
        if (!discardPile.pile.empty()) {
            out << *(discardPile.pile.back());
        }
        return out;
    }
};