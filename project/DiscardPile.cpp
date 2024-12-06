#include "DiscardPile.h"

//Constructor for reconstructing DiscardPile from file
DiscardPile::DiscardPile(std::istream& in, const CardFactory* factory) {
    std::string line;

    in >> line;

    if (line != "discardpile") {
        throw std::runtime_error("Expected 'discardpile' but found: " + line);
    }

    while (in >> line && line != ".") {
        if (line == "e") {
            continue;
        }

        Card* card = factory->createCard(line);

        if (card) {
            pile.push_back(card);
        }
    }
}

DiscardPile& DiscardPile::operator+=(Card* card) {
    pile.push_back(card);
    return *this;
}

// Removes and returns top card from discard pile
Card* DiscardPile::pickUp() {
    if (pile.empty()) {
        throw std::runtime_error("DiscardPile empty");
    }
    Card* topCard = pile.back();
    pile.pop_back();
    return topCard;
}

// Returns top card from discard pile (without remove)
Card* DiscardPile::top() const {
    if (pile.empty()) {
        //throw std::runtime_error("DiscardPile empty");
        return nullptr;
    }
    return pile.back();
}

// Print function used for outputting to file.
void DiscardPile::print(std::ostream& out) const {
    out << "discardpile" << std::endl;

    if (!pile.empty()) {
        for (const auto& card : pile) {
            card->print(out);
            out << " ";
        }
    }
    else {
        out << "e";
    }

    out << std::endl;
}

// Top-level output to console.
std::ostream& operator<<(std::ostream& out, const DiscardPile& pile) {

    out << "Discard Pile: ";

    if (!pile.top()) {
        out << "empty" << std::endl;
    }
    else {
        out << pile.top()->getName() << std::endl;
    }

    return out;
}
