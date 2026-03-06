

#ifndef CARD_H
#define CARD_H

#include <string>

// enum to represent the four suits in a deck
enum class Suit {
    Spades, 
    Hearts,
    Diamonds, 
    Clubs
};

// enum to represent the ranks in deck
enum class Rank {
    Six = 6, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
};

// represent a single playing card
class Card {
public:
    Suit suit; 
    Rank rank;

    // constructor to create a card
    Card(Suit s, Rank r);

    // converts the card to a readable string
    std::string toString() const;
};

#endif