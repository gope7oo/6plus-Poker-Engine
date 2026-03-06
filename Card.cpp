

#include "Card.h"

// constructor 
Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

// convert card to readable string '
std::string Card::toString() const {
    const std::string suits[] = {"♠", "♥", "♦", "♣"};
    const std::string ranks[] = {"Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    return ranks[static_cast<int>(rank) - 6] + " of " + suits[static_cast<int>(suit)];
}


