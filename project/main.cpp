#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"
#include "CardFactory.h"

// Note that this program uses C++ 11.
using namespace std;

void saveGame(const Table& table, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << table;
        file.close();
        cout << "Game saved to " << filename << endl;
    }
    else {
        cerr << "Unable to save game to " << filename << endl;
    }
}

int main() {
    // Setup
    CardFactory* factory = CardFactory::getFactory();

    Table* table = nullptr;

    string player1Name, player2Name;


    cout << "Do you want to start a new game or load a saved game? (new/load): ";
    string choice;
    cin >> choice;

    if (choice == "new") {
        // Input player names
        cout << "Enter name for Player 1: ";
        cin >> player1Name;
        cout << "Enter name for Player 2: ";
        cin >> player2Name;

        // Initialize table and draw initial hands
        table = new Table(player1Name, player2Name, factory);

        for (int i = 0; i < 5; ++i) {
            table->getPlayer1().getHand() += table->getDeck().draw();
            table->getPlayer2().getHand() += table->getDeck().draw();
        }

    }
    else if (choice == "load") {
        ifstream file("saved_game.txt");
        if (file.is_open()) {
            table = new Table(file, factory);
            file.close();
        }
        else {
            cerr << "No saved game found. Starting a new game." << endl;
            return 1;
        }
    }
    else {
        cerr << "Invalid input. Exiting game." << endl;
        return 1;
    }

    // Main game loop
    while (!table->getDeck().empty()) {
        cout << *table;

        // Pause and save game
        //cout << "Do you want to pause the game and save? (yes/no): ";
        //cin >> choice;
        //if (choice == "yes") {
        //    saveGame(*table, "saved_game.txt");
        //    delete table;
        //    return 0;
        //}

        // Player turns
        for (int i = 0; i < 2; i++) {
            // Get the current player from via table object
            Player& currentPlayer = (i == 0) ? table->getPlayer1() : table->getPlayer2();
            cout << "It's " << currentPlayer.getName() << "'s turn!" << endl;

            // Draw top card from deck
            currentPlayer.getHand() += table->getDeck().draw();

            // If the tradeArea is not empty, add bean cards from the TradeArea to chains or discard them.
            // 1. If the other player has left cards in the trade area from the previous turn (in Step 5), the player may add these cards to his/her chains or discard them.
            if (table->getTradeArea().numCards() > 0) {
                
                cout << "Trade Area: " << table->getTradeArea() << endl;

                // Choose if you want to add cards to your hand, otherwise discard the field into the discard pile.
                cout << "Do you want to add cards from the trade area into your chains? (yes / no)";
                cin >> choice;
                
                if (choice == "yes") {
                    // For each card in trading area, check chains if there exists the same bean type.
                    for (Card* card : table->getTradeArea().getCards()) {
                        table->addCardtoPlayerChain(currentPlayer, card);
                    }

                } else {

                    cout << "Trading Area has been cleared.";

                    for (Card* c : table->getTradeArea().getCards()) {
                        table->getDiscardPile() += table->getTradeArea().trade(c->getName());
                    }
                }

            }

            /*2. The player then plays the topmost card from his/her hand. The card must be added to a chain with
            the same beans. If the player has currently no such chain on the table, an old chain on the table
            will have to be tied and sold, and a new chain must be started. If the chain has not reached a
            sufficient length, a player may receive 0 coins.*/

            Card* topCard = currentPlayer.getHand().play();

            table->addCardtoPlayerChain(currentPlayer, topCard);

            //3. The player has the option to repeat step 2. Ask if the player wants to play again.
            cout << "Do you want to play the next card? (yes/no): ";
            cin >> choice;

            if (choice != "yes") {
                Card* topCard = currentPlayer.getHand().play();

                table->addCardtoPlayerChain(currentPlayer, topCard);
            }
             

            // 4. Discard one arbitrary card to the discard pile face up (revealed).
             currentPlayer.printHand(cout, true);
             cout << "Do you want to discard a card? (yes/no): ";
             cin >> choice;
             if (choice == "yes") {
                 int index;
                 cout << "Enter the index of the card to discard: ";
                 cin >> index;

                 Card* discardedCard = currentPlayer.getHand()[index];

                 table->getDiscardPile() += discardedCard;
             }

            // 5. Draw three cards to TradeArea, draw from discard pile as long as the card matches one of the beans in trade area.
            // Once top card does not match a bean in trade area or if discard pile is empty:
            // Player can either chain cards from hand or place into trade area. 
            // As with step 2, if attempting to chain but chains are full, then one must be sold and then started. Make a function for this.
            // table->drawToTradeArea();

            // // Resolve matches between discard pile and TradeArea
            // table->resolveDiscardPile();

            // // Let the player decide what to do with the TradeArea cards
            // table->processTradeArea(currentPlayer);

            // // Draw two cards to player's hand
            // currentPlayer += table->getDeck().draw();
            // currentPlayer += table->getDeck().draw();
        }
    }

    string winnerName;
    if (table->win(winnerName)) {
        cout << "Game Over! Winner: " << winnerName << endl;
    }
    else {
        cout << "Game Over! It's a tie!" << endl;
    }

    delete table;
    return 0;
}
