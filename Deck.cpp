

#include "Deck.h"
#include <algorithm>
#include <random> 

// Constructor for deck creating
Deck::Deck() { 
    createDeck();
}

// Create and shuffle the deck
void Deck::createDeck() {
    deck.clear();

    for (int s = 0; s < 4; ++s) {
        for (int r = 6; r <= 14; ++r) {
            deck.emplace_back(static_cast<Suit>(s), static_cast<Rank>(r));
        }
    }
    
    // shuffle 
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
}

// Deal a card from the top of the deck 
Card Deck::dealCard() {
    Card topCard = deck.back();
    deck.pop_back();
    return topCard;
}
