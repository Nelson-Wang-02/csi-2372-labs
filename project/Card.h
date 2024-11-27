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

// Derived classes for each type of bean card
class Blue : public Card {
public:
    Blue() = default; // Add default constructor
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Chili : public Card {
public:
    Chili() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Stink : public Card {
public:
    Stink() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Green : public Card {
public:
    Green() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Soy : public Card {
public:
    Soy() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Black : public Card {
public:
    Black() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Red : public Card {
public:
    Red() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class Garden : public Card {
public:
    Garden() = default;
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

class IllegalType : public std::exception {
public:
    const char* what() const noexcept override {
        return "Illegal card type for this chain.";
    }
};