#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Hand.h"
#include "Chain.h"
#include "CardFactory.h"

class NotEnoughCoins : public std::exception {
public:
    const char* what() const noexcept override {
        return "Not enough coins to buy third chain.";
    }
};

class Player {
private:
    std::string name;
    int coins;
    int maxChains;
    std::vector<Chain_Base*> chains;
    Hand hand;

public:
    Player(const std::string& name);
    Player(std::istream& in, const CardFactory* factory);
    std::string getName() const;
    int getNumCoins() const;
    Player& operator+=(int coinsToAdd);
    int getMaxNumChains() const;
    int getNumChains() const;
    Chain_Base& operator[](int i);
    void buyThirdChain();
    void printHand(std::ostream& out, bool printAll) const;
    friend std::ostream& operator<<(std::ostream& out, const Player& player);
    ~Player();
    // Getter for hand.
    Hand& getHand();
    // Getter for chains.
    std::vector<Chain_Base*>& getChains();

};