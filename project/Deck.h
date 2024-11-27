#pragma once
#include "Card.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

class CardFactory;

class Deck : public std::vector<Card*> {
public:
    Deck() = default;
    Deck(const std::vector<Card*>& cards);

    //Constructor for loading game from file
    Deck(std::istream& in, const CardFactory* factory);

    Card* draw();

    friend std::ostream& operator<<(std::ostream& out, const Deck& deck);

    ~Deck();
};