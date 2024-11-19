#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <list>
#include <string>
#include <stdexcept>
#include <iostream>

class TradeArea {
private:
    std::list<Card*> cards;

public:
    //Constructor for loading game from file
    TradeArea(std::istream& in, const CardFactory* cardFactory) {
        std::string cardType;
        while (in >> cardType) {
            cards.push_back(cardFactory->createCard(cardType));
        }
    }

    TradeArea& operator+=(Card* card) {
        cards.push_back(card);
        return *this;
    }

    //Checks if a card is allowed to be added
    bool legal(Card* card) const {
        for (const auto& c : cards) {
            if (c->getName() == card->getName()) {
                return true;
            }
        }
        return false;
    }

    //Removes and returns a card of the specified bean name from the TradeArea
    Card* trade(const std::string& beanName) {
        for (auto it = cards.begin(); it != cards.end(); ++it) {
            if ((*it)->getName() == beanName) {
                Card* card = *it;
                cards.erase(it);
                return card;
            }
        }
        throw std::runtime_error("TradeArea: No card of the specified bean type found.");
    }

    int numCards() const {
        return cards.size();
    }

    //Prints all cards in TradeArea
    void print(std::ostream& out) const {
        for (const auto& card : cards) {
            out << *card << " ";
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea) {
        tradeArea.print(out);
        return out;
    }
};