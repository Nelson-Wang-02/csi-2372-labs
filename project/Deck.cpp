#include "Deck.h"
#include "CardFactory.h"

Deck::Deck(const std::vector<Card*>& cards) : std::vector<Card*>(cards) {}

Deck::Deck(std::istream& in, const CardFactory* factory) {
    std::string line;

    in >> line;
    
    if (line != "deck") {
        throw std::runtime_error("Expected header 'deck' but got " + line);
    }

    while (in >> line && line != ".") {
        if (line == "e") {
            break;
        }

        Card* card = factory->createCard(line);


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
    out << "deck" << std::endl;

    if (!deck.empty()) {
        for (const auto& card : deck) {
            card->print(out);
            out << " ";
        }
    }
    else {
        out << "e";
    }


    return out;
}

Deck::~Deck() {
    for (auto card : *this) {
        delete card;
    }
}
