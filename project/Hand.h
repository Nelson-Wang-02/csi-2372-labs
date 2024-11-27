#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <list>
#include <iostream>
#include <stdexcept>

class Hand {
private:
    std::list<Card*> cards;

public:
    Hand(std::istream& in, const CardFactory* factory);
    Hand& operator+=(Card* card);
    Card* play();
    Card* top() const;
    Card* operator[](int index);
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
};