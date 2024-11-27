#include "TradeArea.h"

//Constructor for loading game from file
TradeArea::TradeArea(std::istream& in, const CardFactory* factory) {
    std::string cardName;
    while (in >> cardName) {
        Card* card = factory->createCard(cardName);
        if (card) {
            cards.push_back(card);
        }
    }
}

TradeArea& TradeArea::operator+=(Card* card) {
    cards.push_back(card);
    return *this;
}

//Checks if a card is allowed to be added
bool TradeArea::legal(Card* card) const {
    for (const auto& c : cards) {
        if (c->getName() == card->getName()) {
            return true;
        }
    }
    return false;
}

//Removes and returns a card of the specified bean name from the TradeArea
Card* TradeArea::trade(const std::string& beanName) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if ((*it)->getName() == beanName) {
            Card* card = *it;
            cards.erase(it);
            return card;
        }
    }
    throw std::runtime_error("TradeArea: No card of the specified bean type found.");
}

int TradeArea::numCards() const {
    return cards.size();
}

std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea) {
    for (const auto& card : tradeArea.cards) {
        card->print(out);
        out << " ";
    }
    return out;
}
