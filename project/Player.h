#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Hand.h"
#include "Chain.h"
#include "CardFactory.h"

class Player {
private:
    std::string name;
    int coins;
    int maxChains;
    std::vector<Chain_Base*> chains;
    Hand hand;

public:
    Player(const std::string& playerName)
        : name(playerName), coins(0), maxChains(2), hand(std::istringstream(""), nullptr) {}

    //Constructor for loading game from file
    Player(std::istream& in, const CardFactory* cardFactory) : hand(in, cardFactory) {
        in >> name >> coins >> maxChains;

        int numChains;
        in >> numChains;
        for (int i = 0; i < numChains; ++i) {
            std::string chainType;
            in >> chainType;
            if (chainType == "Red") {
                chains.push_back(new Chain<Red>(in, cardFactory));
            }
            else if (chainType == "Blue") {
                chains.push_back(new Chain<Blue>(in, cardFactory));
            }
            else if (chainType == "Chili") {
                chains.push_back(new Chain<Chili>(in, cardFactory));
            }
            else if (chainType == "Stink") {
                chains.push_back(new Chain<Stink>(in, cardFactory));
            }
            else if (chainType == "Green") {
                chains.push_back(new Chain<Green>(in, cardFactory));
            }
            else if (chainType == "soy") {
                chains.push_back(new Chain<Soy>(in, cardFactory));
            }
            else if (chainType == "black") {
                chains.push_back(new Chain<Black>(in, cardFactory));
            }
            else if (chainType == "garden") {
                chains.push_back(new Chain<Garden>(in, cardFactory));
            }
            else {
                throw std::runtime_error("Invalid chain type found during game reloading: " + chainType);
            }
        }
    }

    std::string getName() const {
        return name;
    }

    int getNumCoins() const {
        return coins;
    }

    Player& operator+=(int numCoins) {
        coins += numCoins;
        return *this;
    }

    int getMaxNumChains() const {
        return maxChains;
    }

    //Get the number of non-zero chains
    int getNumChains() const {
        int count = 0;
        for (const auto& chain : chains) {
            if (chain != nullptr && chain->sell() > 0) {
                ++count;
            }
        }
        return count;
    }

    Chain_Base& operator[](int i) {
        if (i < 0 || i >= static_cast<int>(chains.size())) {
            throw std::out_of_range("Invalid index");
        }
        return *chains[i];
    }

    void buyThirdChain() {
        if (coins < 3) {
            throw std::runtime_error("NotEnoughCoins");
        }
        if (maxChains == 3) {
            throw std::runtime_error("Player already has max chains.");
        }

        coins -= 3;
        maxChains = 3;
        chains.push_back(nullptr);
    }

    //Print the player hand
    void printHand(std::ostream& out, bool printAll) const {
        if (printAll) {
            out << hand;
        }
        else if (!hand.top()) {
            out << "No cards in hand.";
        }
        else {
            out << *hand.top();
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Player& player) {
        out << player.name << " " << player.coins << " coins" << std::endl;

        for (const auto& chain : player.chains) {
            if (chain != nullptr) {
                out << *chain << std::endl;
            }
            else {
                out << "Empty chain" << std::endl;
            }
        }

        return out;
    }

    //Destructor to delete dynamically allocated chains
    ~Player() {
        for (auto& chain : chains) {
            delete chain;
        }
    }
};