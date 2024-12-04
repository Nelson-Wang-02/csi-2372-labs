#pragma once
#include "Card.h"
#include "CardFactory.h"
#include <list>
#include <string>
#include <stdexcept>
#include <iostream>

class TradeArea {
private:
    std::list<Card*> cards;

public:
    TradeArea(std::istream& in, const CardFactory* factory);
    //Default constructor
    TradeArea() = default;
    TradeArea& operator+=(Card* card);
    bool legal(Card* card) const;
    Card* trade(const std::string& beanName);
    int numCards() const;
    friend std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea);

    // Getter
    std::list<Card*>& getCards();
};