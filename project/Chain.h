#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

class Chain_Base {
public:
    virtual int sell() = 0;
    virtual void print(std::ostream& out) const = 0;

    virtual ~Chain_Base() = default;

    friend std::ostream& operator<<(std::ostream& out, const Chain_Base& chain) {
        chain.print(out);
        return out;
    }

    // User Defined Functions
    virtual std::string getChainType() = 0;
    virtual void addCard(Card* card) = 0;
};

//Template for chain types (e.g. Chain<Red>)
template <typename T>
class Chain : public Chain_Base {
private:
    std::vector<Card*> cards;

public:
    Chain() = default;
    
    //Constructor for loading game from file
    Chain(std::istream& in, const CardFactory* cardFactory) {
        std::string cardType;
        while (in >> cardType && cardType != "." && cardType != "e") {
            //Create cards and add them to chain
            cards.push_back(static_cast<T*>(cardFactory->createCard(cardType)));
        }
    }

    //Add card to chain
    Chain<T>& operator+=(Card* card) {
        T* typedCard = dynamic_cast<T*>(card);
        if (typedCard) {
            cards.push_back(typedCard);
        }
        else {
            throw IllegalType();
        }
        return *this;
    }

    int sell() override {
        if (cards.empty()) return 0;

        int num_cards = cards.size();
        int coins = 0;

        //Calculate coins
        for (int i = 4; i >= 1; --i) {
            if (num_cards >= cards[0]->getCardsPerCoin(i)) {
                coins = i;
                break;
            }
        }

        for (auto card : cards) {
            delete card;
        }

        cards.clear();
        return coins;
    }

    void print(std::ostream& out) const override {
        if (cards.empty()) return;

        for (const auto& card : cards) {
            card->print(out);
            out << " ";
        }
        out << ".";
    }

    // User-defined function for getting the bean of card.
    std::string getChainType() {
        return cards.empty() ? "Empty" : cards[0]->getName();
    }

    // External use to add a card to the chain.
    void addCard(Card* card) {
        operator+=(card);

    }
};
