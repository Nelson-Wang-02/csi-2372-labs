#include "Player.h" 
#include <sstream>

Player::Player(const std::string& name)
    : name(name), coins(0), maxChains(2) {

    chains.resize(maxChains, nullptr);
}

//Constructor for loading game from file
Player::Player(std::istream& in, const CardFactory* factory) {
    in >> name >> coins >> maxChains;

    std::string line;

    in >> line;

    if (line != "chains") {
        throw std::runtime_error("Expected header 'chains' but got " + line);
    }

    // Read chains.
    chains.resize(maxChains, nullptr);

    for (int i = 0; i < maxChains; ++i) {
        in >> line;

        if (line != "e") {
            chains.push_back(new Chain<Card>(in, factory));
        }  
    }

    // Read hand.
    in >> line;

    if (line != "hand") {
        throw std::runtime_error("Expected header 'hand' but got " + line);
    }

    while (in >> line && line != ".") {
        Card* card = factory->createCard(line);

        if (card) {
            hand += card;
        }
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
        if (chain != nullptr){// && !chain->empty()) {
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
    out << "Hand: ";

    if (printAll) {
        out << hand << std::endl;
    }
    else if (Card* topCard = hand.top()) {
        out << topCard->getName();
        out << std::endl;
    }
}

// Top level output to console.
std::ostream& operator<<(std::ostream& out, const Player& player) {
    
    out << player.name << " " << player.coins << " coins" << std::endl;

    out << "Chains: " << std::endl;

    int i = 0;
    for (auto& chain : player.chains) {
        out << "[" << i << "] ";

        if (chain == nullptr) {
            out << "empty";
        } 
        else {
            out << chain->getChainType() << " ";
            chain->print(out);
        }

        out << std::endl;

        i++;
    }

    return out;
}

//Destructor to delete dynamically allocated chains
Player::~Player() {
    for (auto& chain : chains) {
        delete chain;
    }
}

Hand& Player::getHand() {
    return hand;
}

std::vector<Chain_Base*>& Player::getChains() {
    return chains;
}

int const Player::getHandCount(){
    return hand.getCards().size();
}

// Print function used to output to file.
void Player::print(std::ostream& out) const {
    out << name << " " << coins << " " << maxChains << std::endl;

    out << "chains" << std::endl;

    for (const auto& chain : chains) {
        if (chain != nullptr) {
            out << *chain << std::endl;
        }
        else {
            out << "e" << std::endl;
        }
    }

    out << "hand" << std::endl;
    out << hand << std::endl;

}

Card* Player::discardCard(int index) {

    auto cards = hand.getCards();
    Card* card;

    if (index >= 0 && index < cards.size()) {
        auto it = cards.begin();

        for (int i = 0; i < index; i++) {
            it++;
        }

        card = *it;

        cards.erase(it);

    }
    else {
        throw std::out_of_range("Index not valid. Skipping discard.");
    }

    return card;
}