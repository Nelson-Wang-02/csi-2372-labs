#include "Table.h"
#include "CardFactory.h"


// Constructor Added for New Game Creation.
Table::Table(const std::string& p1Name, const std::string& p2Name, const CardFactory* cf) 
    : player1(p1Name), player2(p2Name), deck(cf->getDeck()) {}

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
    if (table.discardPile.top()) {
        out << "Empty";
    }
    else {
        table.discardPile.print(out);
    }
    out << std::endl;

    out << "Trade Area: " << table.tradeArea << std::endl;

    return out;
}

// Destructor
Table::~Table() {}

// Getter for Deck.
Deck& Table::getDeck() {
    return deck;
}

// Getter for player 1
Player& Table::getPlayer1() {
    return player1;
} 

// Getter for player 2
Player& Table::getPlayer2() {
    return player2;
}

// Getter for DiscardPile
DiscardPile& Table::getDiscardPile() {
    return discardPile;
} 

// Getter for TradeArea
TradeArea& Table::getTradeArea() {
    return tradeArea;
}

bool Table::addNewChain(Player& player, Card* card, int index) {
    if (player.getChains()[index] == nullptr) {
        // Create new chain at this index
        if (card->getName() == "Blue") {
            player.getChains()[index] = new Chain<Blue>();
        }
        else if (card->getName() == "Chili") {
            player.getChains()[index] = new Chain<Chili>();
        }
        else if (card->getName() == "Stink") {
            player.getChains()[index] = new Chain<Stink>();
        }
        else if (card->getName() == "Green") {
            player.getChains()[index] = new Chain<Green>();
        }
        else if (card->getName() == "Soy") {
            player.getChains()[index] = new Chain<Soy>();
        }
        else if (card->getName() == "Black") {
            player.getChains()[index] = new Chain<Black>();
        }
        else if (card->getName() == "Red") {
            player.getChains()[index] = new Chain<Red>();
        }
        else if (card->getName() == "Garden") {
            player.getChains()[index] = new Chain<Garden>();
        }

        player.getChains()[index]->addCard(card);

        std::cout << "A new chain has been created with card " << card->getName() << ".\n";

        return true;
    }

    return false;
}

void Table::addCardtoPlayerChain(Player& player, Card* card) {
    
    bool beanExists = false;

    // Check if the Bean exists in Chains.
    for (auto chain : player.getChains()) {

        // If there is the same bean, then add it into the chain.
        if (chain != nullptr && card->getName() == chain->getChainType()) {
            chain->addCard(card);
            std::cout << "Card " << card->getName() << " has been added to an existing chain.\n";
            beanExists = true;
            break;
        }

    }
   
    if (!beanExists) {

        bool foundOpenSlot = false;

        for (int i = 0; i < player.getMaxNumChains(); i++) {

            foundOpenSlot = addNewChain(player, card, i);
        }

        // Need to sell.
        if (!foundOpenSlot) {

            std::cout << "There are no more chain slots. Please choose one chain to sell.\n";

            // Show available chains.

            for (int i = 0; i < player.getMaxNumChains(); i++) {
                std::cout << "[" << i << "] ";
                player.getChains()[i]->print(std::cout);
            }

            int userIndex;
            std::cout << "Select the chain you'd like to sell by stating the index.\n";
            std::cin >> userIndex;

            int coins = player.getChains()[userIndex]->sell();

            player += coins;

            delete player.getChains()[userIndex];
            player.getChains()[userIndex] = nullptr;

            std::cout << "Chain [" << userIndex << "] has been sold for " << coins << " coins.\n";

            // Create a new chain with the given card.
            addNewChain(player, card, userIndex);

            std::cout << "New chain created with " << card->getName() << ".\n";

        }

    }




}
