#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include "Card.h"
#include "Deck.h"

class CardFactory {
private:
    std::vector<Card*> cards;

    CardFactory() {
        for (int i = 0; i < 20; ++i) {
            cards.push_back(new Blue());
        }

        for (int i = 0; i < 18; ++i) {
            cards.push_back(new Chili());
        }

        for (int i = 0; i < 16; ++i) {
            cards.push_back(new Stink());
        }

        for (int i = 0; i < 14; ++i) {
            cards.push_back(new Green());
        }

        for (int i = 0; i < 12; ++i) {
            cards.push_back(new Soy());
        }

        for (int i = 0; i < 10; ++i) {
            cards.push_back(new Black());
        }

        for (int i = 0; i < 8; ++i) {
            cards.push_back(new Red());
        }

        for (int i = 0; i < 6; ++i) {
            cards.push_back(new Garden());
        }
    }

    //Preventing copying
    CardFactory(const CardFactory&) = delete;
    CardFactory& operator=(const CardFactory&) = delete;

    ~CardFactory() {
        for (auto card : cards) {
            delete card;
        }
    }

public:
    static CardFactory* getFactory() {
        static CardFactory instance; //Single instance of CardFactory
        return &instance;
    }

    Deck getDeck() {
        Deck deck;
        deck.reserve(cards.size());

        for (auto card : cards) {
            deck.push_back(card);
        }

        //Shuffle the deck
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);

        return deck;
    }

    Card* createCard(const std::string& cardName) const {
        if (cardName == "Blue") return new Blue();
        if (cardName == "Chili") return new Chili();
        if (cardName == "Stink") return new Stink();
        if (cardName == "Green") return new Green();
        if (cardName == "soy") return new Soy();
        if (cardName == "black") return new Black();
        if (cardName == "Red") return new Red();
        if (cardName == "garden") return new Garden();

        throw std::runtime_error("Unknown card type: " + cardName);
    }
};