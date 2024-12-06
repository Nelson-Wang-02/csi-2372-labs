#include "Card.h"

//Derived bean card classes
//Blue
int Blue::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 4;
    case 2: return 6;
    case 3: return 8;
    case 4: return 10;
    default: return 0;
    }
}

std::string Blue::getName() const {
    return "Blue";
}

void Blue::print(std::ostream& out) const {
    out << "B";
}

//Chili
int Chili::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 3;
    case 2: return 6;
    case 3: return 8;
    case 4: return 9;
    default: return 0;
    }
}

std::string Chili::getName() const {
    return "Chili";
}

void Chili::print(std::ostream& out) const {
    out << "C";
}

//Stink
int Stink::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 3;
    case 2: return 5;
    case 3: return 7;
    case 4: return 8;
    default: return 0;
    }
}

std::string Stink::getName() const {
    return "Stink";
}

void Stink::print(std::ostream& out) const {
    out << "S";
}

//Green
int Green::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 3;
    case 2: return 5;
    case 3: return 6;
    case 4: return 7;
    default: return 0;
    }
}

std::string Green::getName() const {
    return "Green";
}

void Green::print(std::ostream& out) const {
    out << "G";
}

//Soy
int Soy::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 2;
    case 2: return 4;
    case 3: return 6;
    case 4: return 7;
    default: return 0;
    }
}

std::string Soy::getName() const {
    return "Soy";
}

void Soy::print(std::ostream& out) const {
    out << "s";
}

//Black
int Black::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 2;
    case 2: return 4;
    case 3: return 5;
    case 4: return 6;
    default: return 0;
    }
}

std::string Black::getName() const {
    return "Black";
}

void Black::print(std::ostream& out) const {
    out << "b";
}

//Red
int Red::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 2;
    case 2: return 3;
    case 3: return 4;
    case 4: return 5;
    default: return 0;
    }
}

std::string Red::getName() const {
    return "Red";
}

void Red::print(std::ostream& out) const {
    out << "R";
}

//Garden
int Garden::getCardsPerCoin(int coins) const {
    switch (coins) {
    case 1: return 105; // A number larger than deck size. Mitigates a bug in Chain::sell() where numCards >= 0 on i = 4, returning 4 coins.
    case 2: return 2;
    case 3: return 3;
    case 4: return 105;
    default: return 0;
    }
}

std::string Garden::getName() const {
    return "Garden";
}

void Garden::print(std::ostream& out) const {
    out << "g";
}