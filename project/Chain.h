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
};

//Template for chain types (e.g. Chain<Red>)
template <typename T>
class Chain : public Chain_Base {
private:
    std::vector<T*> cards;

public:
    //Constructor for loading game from file
    Chain(std::istream& in, const CardFactory* cardFactory) {
        std::string cardType;
        while (in >> cardType) {
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
            throw std::runtime_error("IllegalType: Card type does not match chain type.");
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

        cards.clear();
        return coins;
    }

    void print(std::ostream& out) const override {
        if (cards.empty()) return;

        out << cards[0]->getName() << " ";

        for (const auto& card : cards) {
            card->print(out);
            out << " ";
        }
    }
};
