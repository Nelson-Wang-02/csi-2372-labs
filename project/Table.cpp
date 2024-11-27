#include "Table.h"

//Constructor for loading game from file
Table::Table(std::istream& in, const CardFactory* factory)
    : player1(in, factory), player2(in, factory), deck(in, factory), discardPile(in, factory), tradeArea(in, factory) {}

bool Table::win(std::string& winnerName) const {
    if (deck.empty()) {
        int coins1 = player1.getNumCoins();
        int coins2 = player2.getNumCoins();

        if (coins1 > coins2) {
            winnerName = player1.getName();
            return true;
        }
        else if (coins2 > coins1) {
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

// Print the hand of both players
void Table::printHand(bool printAll) const {
    std::cout << "Player 1's hand: ";
    player1.printHand(std::cout, printAll);

    std::cout << "Player 2's hand: ";
    player2.printHand(std::cout, printAll);
}

std::ostream& operator<<(std::ostream& out, const Table& table) {
    out << "Player 1: " << table.player1 << std::endl;
    out << "Player 2: " << table.player2 << std::endl;

    out << "Deck: " << table.deck.size() << " cards remaining" << std::endl;

    out << "Discard Pile: ";
    if (!table.discardPile.top()) {
        out << "Empty";
    }
    else {
        table.discardPile.print(out);
    }
    out << std::endl;

    out << "Trade Area: " << table.tradeArea << std::endl;

    return out;
}
