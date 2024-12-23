#include "TradeArea.h"

//Constructor for reconstructing TradeArea from file
TradeArea::TradeArea(std::istream& in, const CardFactory* factory) {
    std::string line;

    in >> line;

    if (line != "tradearea") {
        throw std::runtime_error("Expected 'tradearea' but found " + line);
    }

    while (in >> line && line != ".") {

        if (line == "e"){ 
            continue;
        }

        Card* card = factory->createCard(line);
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
    for (auto it = cards.begin(); it != cards.end(); it++) {
        if ((*it)->getName() == beanName) {
            Card* card = *it;
            cards.erase(it);
            return card;
        }
    }
    throw std::runtime_error("Trade Area: No card of the specified bean type found.");
}

int TradeArea::numCards() const {
    return cards.size();
}

// Top-level output to console.
std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea) {
    out << "Trade Area: ";

    if (tradeArea.cards.empty()) {
        out << "empty" << std::endl;
    }
    else {
        for (const auto& card : tradeArea.cards) {
            card->print(out);
            out << " ";
        }
        out << std::endl;
    }

    return out;
}

// Getter for cards
std::list<Card*>& TradeArea::getCards() {
    return cards;
}

void TradeArea::print(std::ostream& out) const {
    out << "tradearea" << std::endl;

    if (!cards.empty()) {
        for (const auto& card : cards) {
            card->print(out);
            out << " ";
        }
    }
    else {
        out << "e";
    }

    out << std::endl;
}
