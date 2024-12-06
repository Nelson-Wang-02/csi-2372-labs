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
        table.print(file);
        file.close();
        cout << "Game saved to " << filename << endl;
    }
    else {
        cerr << "Unable to save game to " << filename << endl;
    }
}

void loadGame(Table*& table, const string& filename, const CardFactory* factory) {
    ifstream file(filename);

    if (file.is_open()) {
        try {
            table = new Table(file, factory);

        }
        catch (runtime_error e) {
            cout << e.what() << endl;
        }

        file.close();
        cout << "Game loaded from " << filename << endl << endl;

    } 
    else {
        cout << "Failed to load game from file. Starting new game." << endl << endl;
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
        cout << endl;

        // Initialize table and draw initial hands
        table = new Table(player1Name, player2Name, factory);

        for (int i = 0; i < 5; ++i) {
            table->getPlayer1().getHand() += table->getDeck().draw();
            table->getPlayer2().getHand() += table->getDeck().draw();
        }

    }
    // Load game from file.
    else if (choice == "load") {
        
        loadGame(table, "saved_game.txt", factory);

    }
    else {
        cerr << "Invalid input. Exiting game." << endl;
        return 1;
    }

    // Main game loop
    while (!table->getDeck().empty()) {
        cout << *table;

        // Pause and save game
        cout << "Do you want to pause the game and save? (yes/no): ";
        cin >> choice;
        cout << endl;

        if (choice == "yes") {
            saveGame(*table, "saved_game.txt");
            delete table;
            return 0;
        }

        // Player turns
        for (int i = 0; i < 2; i++) {
            // Get the current player from via table object
            Player& currentPlayer = (i == 0) ? table->getPlayer1() : table->getPlayer2();
            cout << "***** It's " << currentPlayer.getName() << "'s turn! *****" << endl << endl;

            // Draw top card from deck
            currentPlayer.getHand() += table->getDeck().draw();

            // If the tradeArea is not empty, add bean cards from the TradeArea to chains or discard them.
            // 1. If the other player has left cards in the trade area from the previous turn (in Step 5), the player may add these cards to his/her chains or discard them.
            if (table->getTradeArea().numCards() > 0) {
                
                cout << *table;

                // Choose if you want to add cards to your hand, otherwise discard the field into the discard pile.
                cout << "Do you want to add cards from the trade area into your chains? (yes/no)";
                cin >> choice;

                cout << endl;
                
                if (choice == "yes") {
                    // For each card in trading area, check chains if there exists the same bean type.
                    auto tradeAreaCards = table->getTradeArea().getCards();
                    for (auto it = tradeAreaCards.begin(); it != tradeAreaCards.end(); it++) {

                        Card* card = *it;

                        Card* tradedCard = table->getTradeArea().trade(card->getName());

                        table->addCardtoPlayerChain(currentPlayer, tradedCard);
                    }

                } else {

                    cout << "Trading Area has been cleared." << endl << endl;

                    auto tradeAreaCards = table->getTradeArea().getCards();

                    for (auto it = tradeAreaCards.begin(); it != tradeAreaCards.end(); it++) {
                        Card* card = *it;

                        try {
                            table->getDiscardPile() += table->getTradeArea().trade(card->getName());
                        }
                        catch (runtime_error e) {
                            cout << e.what() << endl;
                        }
                        
                    }
                }

            }

            /*2. The player then plays the topmost card from his/her hand. The card must be added to a chain with
            the same beans. If the player has currently no such chain on the table, an old chain on the table
            will have to be tied and sold, and a new chain must be started. If the chain has not reached a
            sufficient length, a player may receive 0 coins.*/

            Card* topCard = currentPlayer.getHand().play();
            
            cout << "Player " << currentPlayer.getName() << " plays card: " << topCard->getName() << endl << endl;

            table->addCardtoPlayerChain(currentPlayer, topCard);

            //3. The player has the option to repeat step 2. Ask if the player wants to play again.
            if (currentPlayer.getHand().top()) {
                topCard = currentPlayer.getHand().top();

                cout << "Do you want to play the next card: " << topCard->getName() << "? (yes/no) ";
                cin >> choice;

                cout << endl;

                if (choice == "yes") {
                    topCard = currentPlayer.getHand().play();

                    table->addCardtoPlayerChain(currentPlayer, topCard);
                }

                // 4. Discard one arbitrary card to the discard pile face up (revealed).
                currentPlayer.printHand(cout, false);
                cout << endl;

                cout << "Do you want to discard a card? You hold: " << currentPlayer.getHandCount() << " cards. (yes/no)";
                cin >> choice;
                cout << endl;

                if (choice == "yes") {
                    int index;
                    cout << "Enter the index of the card to discard (starting from 0): ";
                    cin >> index;
                    cout << endl;

                    try {
                        Card* discardedCard = currentPlayer.discardCard(index);

                        table->getDiscardPile() += discardedCard;
                    }
                    catch (out_of_range e) {
                        cout << e.what() << endl;
                    }

                }
            }
            else {
                cout << "No more cards in hand! Proceeding." << endl << endl;
            }
  
            // 5. Draw three cards to TradeArea, draw from discard pile as long as the card matches one of the beans in trade area.
            // Once top card does not match a bean in trade area or if discard pile is empty:
            // Player can either chain cards from hand or place into trade area. 
            // As with step 2, if attempting to chain but chains are full, then one must be sold and then started. Make a function for this.
             for (int i = 0; i < 3; i++) {
                 table->getTradeArea() += table->getDeck().draw();
             }

             cout << "Drew 3 cards to Trade Area." << endl << endl;

             // While top card of discard pile matches an existing card in the trade area or the pile is not empty.
             while (table->getDiscardPile().top() && table->getTradeArea().legal(table->getDiscardPile().top())) {
                 // Draw the top-most card from the discard pile and place it in the trade area.
                 cout << "Drew " << table->getDiscardPile().top()->getName() << " from Discard Pile to Trade Area." << endl;
                 table->getTradeArea() += table->getDiscardPile().pickUp();
             }

             // Player can either chain the cards or leave them in the trade area for the next player.
             // As in step 2, if the player has currently no such chain matching the bean of the card, and old chain
             // on the table will have to be tied and sold, and then a new chain is started.
             
             // For all cards in the trade area
             auto tradeAreaCards = table->getTradeArea().getCards();

             for (auto it = tradeAreaCards.begin(); it != tradeAreaCards.end(); it++) {
                 
                 cout << *table;

                 Card* card = *it;

                 // if player wants to chain the card.
                 cout << "Do you want to chain the card: " << card->getName() << "? (yes/no)";
                 cin >> choice;

                 cout << endl;

                 if (choice == "yes") {
                     Card* tradedCard = table->getTradeArea().trade(card->getName());

                     table->addCardtoPlayerChain(currentPlayer, tradedCard);
                 }
                 // Card remains in trade area for the next player.
                 else {
                     continue;
                 }
             }

             // 6. Draw two cards from Deck and add the cards to the player's hand (at the back).
             currentPlayer.getHand() += table->getDeck().draw();

             if (table->getDeck().empty()) {
                 break;
             }

             currentPlayer.getHand() += table->getDeck().draw();
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
