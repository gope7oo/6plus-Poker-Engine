#include "Card.h"
#include <string>

Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

// Convert card to readable string (e.g. "Ace of Spades" or "10 of Hearts")
std::string Card::toString() const {
    std::string rankStr;
    std::string suitStr;

    // Convert Rank to string
    switch (rank) {
        case Rank::Six:    rankStr = "6";    break;
        case Rank::Seven:  rankStr = "7";    break;
        case Rank::Eight:  rankStr = "8";    break;
        case Rank::Nine:   rankStr = "9";    break;
        case Rank::Ten:    rankStr = "10";   break;
        case Rank::Jack:   rankStr = "Jack"; break;
        case Rank::Queen:  rankStr = "Queen";break;
        case Rank::King:   rankStr = "King"; break;
        case Rank::Ace:    rankStr = "Ace";  break;
        default:           rankStr = "?";    break;
    }

    // Convert Suit to string
    switch (suit) {
        case Suit::Spades:   suitStr = "Spades";   break;
        case Suit::Hearts:   suitStr = "Hearts";   break;
        case Suit::Diamonds: suitStr = "Diamonds"; break;
        case Suit::Clubs:    suitStr = "Clubs";    break;
        default:             suitStr = "?";        break;
    }

    return rankStr + " of " + suitStr;
}
