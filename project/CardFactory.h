#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include "Card.h"
#include "Deck.h"

class CardFactory {
private:
    static CardFactory* instance;

    std::vector<Card*> cards;

    CardFactory();

public:
    // Prevent copying and assignment
    CardFactory(const CardFactory&) = delete;
    CardFactory& operator=(const CardFactory&) = delete;
    ~CardFactory();
    static CardFactory* getFactory();
    Card* createCard(const std::string& cardType) const;
    Deck getDeck();
};