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
    //Constructor for loading game from file
    Table(std::istream& in, const CardFactory* cardFactory)
        : player1(in, cardFactory), player2(in, cardFactory),
        deck(in, cardFactory), discardPile(in, cardFactory), tradeArea(in, cardFactory) {}

    bool win(std::string& winnerName) {
        if (deck.empty()) {
            int coinsPlayer1 = player1.getNumCoins();
            int coinsPlayer2 = player2.getNumCoins();

            if (coinsPlayer1 > coinsPlayer2) {
                winnerName = player1.getName();
                return true;
            }
            else if (coinsPlayer2 > coinsPlayer1) {
                winnerName = player2.getName();
                return true;
            }
            else {
                winnerName = "Tie";
                return true;
            }
        }
        return false;
    }

    //Prints the hand of both players
    void printHand(bool printAll) const {
        std::cout << player1.getName() << "'s hand: ";
        player1.printHand(std::cout, printAll);
        std::cout << std::endl;

        std::cout << player2.getName() << "'s hand: ";
        player2.printHand(std::cout, printAll);
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& out, const Table& table) {
        //Print players
        out << "Player 1: " << table.player1 << std::endl;
        out << "Player 2: " << table.player2 << std::endl;

        //Print discard pile
        out << "Discard Pile: ";
        if (table.discardPile.numCards() > 0) {
            out << table.discardPile << std::endl;
        }
        else {
            out << "Empty" << std::endl;
        }

        //Print trade area
        out << "Trade Area: ";
        if (table.tradeArea.numCards() > 0) {
            out << table.tradeArea << std::endl;
        }
        else {
            out << "Empty" << std::endl;
        }

        return out;
    }

    //Save game state
    void saveGame(std::ostream& out) const {
        out << player1 << std::endl;
        out << player2 << std::endl;
        out << deck << std::endl;
        discardPile.print(out);
        out << std::endl;
        tradeArea.print(out);
        out << std::endl;
    }
};