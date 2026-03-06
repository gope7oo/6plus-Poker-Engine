

#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

// Deck class for creating and managing the card deck
class Deck {
private:
    std::vector<Card> deck; 

public: 
    Deck();

    // creates and shuffles the deck
    void createDeck();

    // deal the top card 
    Card dealCard();
};

#endif