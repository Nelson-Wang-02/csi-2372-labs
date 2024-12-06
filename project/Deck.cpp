#include "Deck.h"
#include "CardFactory.h"

Deck::Deck(const std::vector<Card*>& cards) : std::vector<Card*>(cards) {}

Deck::Deck(std::istream& in, const CardFactory* factory) {
    std::string cardName;
    while (in >> cardName) {
        Card* card = factory->createCard(cardName);
        if (card) {
            this->push_back(card);
        }
    }
}

Card* Deck::draw() {
    if (this->empty()) {
        throw std::runtime_error("Deck empty");
    }
    Card* topCard = this->back();
    this->pop_back();
    return topCard;
}

// The deck is hidden, only used for outputting to file.
std::ostream& operator<<(std::ostream& out, const Deck& deck) {
    for (const auto& card : deck) {
        card->print(out);
        out << *card << " ";
    }
    return out;
}

Deck::~Deck() {
    for (auto card : *this) {
        delete card;
    }
}
