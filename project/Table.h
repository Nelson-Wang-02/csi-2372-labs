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
    ~Table();
    // User-defined
    Table(const std::string& p1Name, const std::string& p2Name, const CardFactory* cf); // Added Constructor for New Game Creation.
    Deck& getDeck(); // Getter for deck
    Player& getPlayer1(); // Getter for player 1
    Player& getPlayer2(); // Getter for player 2
    DiscardPile& getDiscardPile(); // Getter for DiscardPile
    TradeArea& getTradeArea(); // Getter for TradeArea
    bool addNewChain(Player& player, Card* card); // Add a new chain to player.
    void addCardtoPlayerChain(Player& player, Card* card); // Add a new Card to Chain.
    void print(std::ostream& out) const; // Print to file.
};