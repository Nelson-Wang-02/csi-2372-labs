#pragma once
#include <iostream>
#include <string>

class Card {
public:
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream& out) const = 0;

    virtual ~Card() = default;

    // Friend function for stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const Card& card) {
        card.print(out);
        return out;
    }
};

//Derived bean card classes
class Blue : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 4;
        if (coins == 2) return 6;
        if (coins == 3) return 8;
        if (coins == 4) return 10;
        return -1;
    }

    std::string getName() const override {
        return "Blue";
    }

    void print(std::ostream& out) const override {
        out << "B";
    }
};

class Chili : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 3;
        if (coins == 2) return 6;
        if (coins == 3) return 8;
        if (coins == 4) return 9;
        return -1;
    }

    std::string getName() const override {
        return "Chili";
    }

    void print(std::ostream& out) const override {
        out << "C";
    }
};

class Stink : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 3;
        if (coins == 2) return 5;
        if (coins == 3) return 7;
        if (coins == 4) return 8;
        return -1;
    }

    std::string getName() const override {
        return "Stink";
    }

    void print(std::ostream& out) const override {
        out << "S";
    }
};

class Green : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 3;
        if (coins == 2) return 5;
        if (coins == 3) return 6;
        if (coins == 4) return 7;
        return -1;
    }

    std::string getName() const override {
        return "Green";
    }

    void print(std::ostream& out) const override {
        out << "G";
    }
};

class Soy : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 2;
        if (coins == 2) return 4;
        if (coins == 3) return 6;
        if (coins == 4) return 7;
        return -1;
    }

    std::string getName() const override {
        return "soy";
    }

    void print(std::ostream& out) const override {
        out << "s";
    }
};

class Black : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 2;
        if (coins == 2) return 4;
        if (coins == 3) return 5;
        if (coins == 4) return 6;
        return -1;
    }

    std::string getName() const override {
        return "black";
    }

    void print(std::ostream& out) const override {
        out << "b";
    }
};

class Red : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return 2;
        if (coins == 2) return 3;
        if (coins == 3) return 4;
        if (coins == 4) return 5;
        return -1;
    }

    std::string getName() const override {
        return "Red";
    }

    void print(std::ostream& out) const override {
        out << "R";
    }
};

class Garden : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        if (coins == 1) return -1;
        if (coins == 2) return 2;
        if (coins == 3) return 3;
        if (coins == 4) return -1;
        return -1;
    }

    std::string getName() const override {
        return "garden";
    }

    void print(std::ostream& out) const override {
        out << "g";
    }
};