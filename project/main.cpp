#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"
#include "CardFactory.h"

void saveGame(const Table& table, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << table;
        file.close();
        std::cout << "Game saved to " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to save game to " << filename << std::endl;
    }
}

int main() {
    // Setup
    std::string player1Name, player2Name;
    CardFactory* factory = CardFactory::getFactory();
    Table* table = nullptr;

    std::cout << "Do you want to start a new game or load a saved game? (new/load): ";
    std::string choice;
    std::cin >> choice;

    if (choice == "new") {
        // Input player names
        std::cout << "Enter name for Player 1: ";
        std::cin >> player1Name;
        std::cout << "Enter name for Player 2: ";
        std::cin >> player2Name;

        // Initialize table and draw initial hands
        Deck deck = factory->getDeck();
        Player player1(player1Name);
        Player player2(player2Name);

        for (int i = 0; i < 5; ++i) {
            player1 += deck.draw();
            player2 += deck.draw();
        }

        table = new Table(player1, player2, deck);
    }
    else if (choice == "load") {
        std::ifstream file("saved_game.txt");
        if (file.is_open()) {
            table = new Table(file, factory);
            file.close();
        }
        else {
            std::cerr << "No saved game found. Starting a new game." << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Invalid input. Exiting game." << std::endl;
        return 1;
    }

    // Main game loop
    while (!table->getDeck().empty()) {
        std::cout << *table;

        // Pause and save game
        std::cout << "Do you want to pause the game and save? (yes/no): ";
        std::cin >> choice;
        if (choice == "yes") {
            saveGame(*table, "saved_game.txt");
            delete table;
            return 0;
        }

        // Player turns
        for (int i = 0; i < 2; ++i) {
            Player& currentPlayer = (i == 0) ? table->getPlayer1() : table->getPlayer2();
            std::cout << "It's " << currentPlayer.getName() << "'s turn!" << std::endl;

            // Draw top card from deck
            currentPlayer += table->getDeck().draw();

            // If TradeArea is not empty
            if (!table->getTradeArea().empty()) {
                table->resolveTradeArea(currentPlayer);
            }

            // Play cards from hand
            while (true) {
                Card* topCard = currentPlayer.playTopCard();
                if (!topCard) break;

                std::cout << "Playing card: " << *topCard << std::endl;
                bool chainEnded = currentPlayer.addCardToChain(topCard);
                if (chainEnded) {
                    std::cout << "Chain completed. Coins earned: " << currentPlayer.sellChain() << std::endl;
                }

                // Ask if the player wants to play again
                std::cout << "Do you want to play the next card? (yes/no): ";
                std::cin >> choice;
                if (choice != "yes") break;
            }

            // Show the player's hand and discard a card
            currentPlayer.printHand(std::cout, true);
            std::cout << "Do you want to discard a card? (yes/no): ";
            std::cin >> choice;
            if (choice == "yes") {
                int index;
                std::cout << "Enter the index of the card to discard: ";
                std::cin >> index;
                Card* discardedCard = currentPlayer.discardCard(index);
                if (discardedCard) {
                    table->getDiscardPile() += discardedCard;
                }
            }

            // Draw three cards to TradeArea
            table->drawToTradeArea();

            // Resolve matches between discard pile and TradeArea
            table->resolveDiscardPile();

            // Let the player decide what to do with the TradeArea cards
            table->processTradeArea(currentPlayer);

            // Draw two cards to player's hand
            currentPlayer += table->getDeck().draw();
            currentPlayer += table->getDeck().draw();
        }
    }

    std::string winnerName;
    if (table->win(winnerName)) {
        std::cout << "Game Over! Winner: " << winnerName << std::endl;
    }
    else {
        std::cout << "Game Over! It's a tie!" << std::endl;
    }

    delete table;
    return 0;
}
