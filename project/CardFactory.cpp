#include "CardFactory.h"

CardFactory* CardFactory::instance = nullptr;

CardFactory::CardFactory() {
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

CardFactory::~CardFactory() {
    for (Card* card : cards) {
        delete card;
    }
}

CardFactory* CardFactory::getFactory() {
    if (!instance) {
        instance = new CardFactory();
    }
    return instance;
}

Deck CardFactory::getDeck() const {
    Deck deck;

    for (Card* card : cards) {
        deck.push_back(card);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    return deck;
}

Card* CardFactory::createCard(const std::string& cardName) const {
    if (cardName == "B") return new Blue();
    if (cardName == "C") return new Chili();
    if (cardName == "S") return new Stink();
    if (cardName == "G") return new Green();
    if (cardName == "s") return new Soy();
    if (cardName == "b") return new Black();
    if (cardName == "R") return new Red();
    if (cardName == "g") return new Garden();

    throw std::runtime_error("Unknown card type: " + cardName);
}