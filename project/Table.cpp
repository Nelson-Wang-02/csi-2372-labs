#include "Table.h"
#include "CardFactory.h"

//Constructor for loading game from file
Table::Table(std::istream& in, const CardFactory* factory)
    : player1(in, factory), 
    player2(in, factory), 
    deck(in, factory), 
    tradeArea(in, factory),
    discardPile(in, factory) {}

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

// Top Level output to console.
std::ostream& operator<<(std::ostream& out, const Table& table) {
    out << "--Table--" << std::endl;
    out << "Deck: " << table.deck.size() << " cards left." << std::endl << std::endl;
    out << table.player1 << std::endl;
    out << table.player2 << std::endl;
    out << table.tradeArea << std::endl;
    out << table.discardPile << std::endl;
    out << "---------" << std::endl;

    return out;
}

// Destructor
Table::~Table() {}

// Constructor Added for New Game Creation.
Table::Table(const std::string& p1Name, const std::string& p2Name, const CardFactory* cf)
    : player1(p1Name), player2(p2Name), deck(cf->getDeck()) {}

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

bool Table::addNewChain(Player& player, Card* card) {
    // Check if there is no other chains with existing bean.

    for (int i = 0; i < player.getMaxNumChains(); i++) {
        if (player.getChains()[i] == nullptr) {
            // Create new chain at this i
            if (card->getName() == "Blue") {
                player.getChains()[i] = new Chain<Blue>();
            }
            else if (card->getName() == "Chili") {
                player.getChains()[i] = new Chain<Chili>();
            }
            else if (card->getName() == "Stink") {
                player.getChains()[i] = new Chain<Stink>();
            }
            else if (card->getName() == "Green") {
                player.getChains()[i] = new Chain<Green>();
            }
            else if (card->getName() == "Soy") {
                player.getChains()[i] = new Chain<Soy>();
            }
            else if (card->getName() == "Black") {
                player.getChains()[i] = new Chain<Black>();
            }
            else if (card->getName() == "Red") {
                player.getChains()[i] = new Chain<Red>();
            }
            else if (card->getName() == "Garden") {
                player.getChains()[i] = new Chain<Garden>();
            }

            try {
                player.getChains()[i]->addCard(card);
            }
            catch (IllegalType e) {
                std::cout << e.what() << std::endl;
            }

            std::cout << "A new chain has been created with card " << card->getName() << "." << std::endl << std::endl;

            return true;
        }
    }

    return false;
}

void Table::addCardtoPlayerChain(Player& player, Card* card) {
    
    bool beanExists = false;

    // If the player does not have the third chain. Choose to buy.
    if (player.getMaxNumChains() < 3) {
        std::cout << "Would you like to buy a third chain slot? (yes/no) ";
        std::string choice;
        std::cin >> choice;

        std::cout << std::endl;

        if (choice == "yes") {
            try {
                player.buyThirdChain();
            }
            catch (NotEnoughCoins e) {
                std::cout << e.what() << std::endl << std::endl;
            }
            
        }
    }

    // Check if the Bean exists in Chains.
    for (auto chain : player.getChains()) {

        // If there is the same bean, then add it into the chain.
        if (chain != nullptr && card->getName() == chain->getChainType()) {
            try {
                chain->addCard(card);
                std::cout << "Card " << card->getName() << " has been added to an existing chain." << std::endl << std::endl;
                beanExists = true;
            }
            catch (IllegalType e) {
                std::cout << e.what() << std::endl;
            }

            break;
        }

    }
   
    if (!beanExists) {

        bool foundOpenSlot = false;

        foundOpenSlot = addNewChain(player, card);
        
        // Need to sell.
        if (!foundOpenSlot) {

            std::cout << "There are no more chain slots. Please sell a chain." << std::endl << std::endl;;

            // Show available chains.

            for (int i = 0; i < player.getMaxNumChains(); i++) {
                std::cout << "[" << i << "] ";
                player.getChains()[i]->print(std::cout);
                std::cout << std::endl;
            }

            int userIndex;
            std::cout << "Select the chain you'd like to sell by stating the index." << std::endl << std::endl;
            std::cin >> userIndex;

            int coins = player.getChains()[userIndex]->sell();

            player += coins;

            delete player.getChains()[userIndex];
            player.getChains()[userIndex] = nullptr;

            std::cout << "Chain [" << userIndex << "] has been sold for " << coins << " coins." << std::endl << std::endl;

            // Create a new chain with the given card.
            addNewChain(player, card);

        }

    }

}

// Print table to a file.
void Table::print(std::ostream& out) const {

    // Print player 1 details.
    player1.print(out);
    out << "." << std::endl;

    // Print player 2 details.
    player2.print(out);
    out << "." << std::endl;

    // Print all contents of Deck
    out << deck << std::endl;
    out << "." << std::endl;

    // Print entirety of Discard Pile 
    discardPile.print(out);
    out << "." << std::endl;

    // Print Trade Area
    tradeArea.print(out);
    out << "." << std::endl;
}
