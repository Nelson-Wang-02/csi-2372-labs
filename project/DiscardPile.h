#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <vector>
#include <iostream>
#include <stdexcept>

class DiscardPile {
private:
    std::vector<Card*> pile;

public:
    //Constructor for loading game from file
    DiscardPile(std::istream& in, const CardFactory* factory);

    DiscardPile& operator+=(Card* card);

    Card* pickUp();

    Card* top() const;

    void print(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& pile);
};