#pragma once
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include <iostream>
#include <string>

class Table {
private:
    Player player1;
    Player player2;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;

public:
    Table(std::istream& in, const CardFactory* factory);
    bool win(std::string& winnerName) const;
    void printHand(bool printAll) const;
    friend std::ostream& operator<<(std::ostream& out, const Table& table);
};