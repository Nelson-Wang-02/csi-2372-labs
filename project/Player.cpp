#include "Player.h"

Player::Player(const std::string& name)
    : name(name), coins(0), maxChains(2), hand(std::cin, nullptr) {}

//Constructor for loading game from file
Player::Player(std::istream& in, const CardFactory* factory)
    : coins(0), maxChains(2), hand(in, factory) {
    in >> name >> coins >> maxChains;

    int numChains;
    in >> numChains;
    for (int i = 0; i < numChains; ++i) {
        std::string chainType;
        in >> chainType;
        chains.push_back(new Chain<Card>(in, factory));
    }
}

std::string Player::getName() const {
    return name;
}

int Player::getNumCoins() const {
    return coins;
}

Player& Player::operator+=(int numCoins) {
    coins += numCoins;
    return *this;
}

int Player::getMaxNumChains() const {
    return maxChains;
}

int Player::getNumChains() const {
    int nonEmptyChains = 0;
    for (const auto& chain : chains) {
        if (chain != nullptr && !chain->empty()) {
            ++nonEmptyChains;
        }
    }
    return nonEmptyChains;
}

Chain_Base& Player::operator[](int i) {
    if (i < 0 || i >= static_cast<int>(chains.size())) {
        throw std::out_of_range("Invalid index.");
    }
    return *chains[i];
}

void Player::buyThirdChain() {
    if (coins < 3) {
        throw NotEnoughCoins();
    }
    coins -= 3;
    maxChains = 3;
    chains.push_back(nullptr);
}

void Player::printHand(std::ostream& out, bool printAll) const {
    if (printAll) {
        out << hand << std::endl;
    }
    else if (Card* topCard = hand.top()) {
        topCard->print(out);
        out << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << player.name << " " << player.coins << " coins" << std::endl;
    for (const auto& chain : player.chains) {
        if (chain != nullptr) {
            out << *chain << std::endl;
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