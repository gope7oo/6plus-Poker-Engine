

#include "HandEvaluation.h"
#include <map>
#include <set>
#include <algorithm>

// check if 5 cards have same suit
bool HandEvaluation::isFlush(const std::vector<Card>& cards) {
    if (cards.size() < 5) return false;

    std::map<Suit, int> suitCount;

    for (const auto& card : cards) {
        suitCount[card.suit]++;
    }

    for (const auto& entry : suitCount) {
        if (entry.second >= 5) {
            return true;
        }
    }
    return false;
}

// check if cards form a straight 
bool HandEvaluation::isStraight(const std::vector<Card>& cards) {
    if (cards.size() < 5) return false;

    std::set<int> ranks;

    for (const auto& card : cards) {
        ranks.insert(static_cast<int>(card.rank));
    }

    if (ranks.size() < 5) return false;

    std::vector<int> sortedRanks(ranks.begin(), ranks.end()); 

    for (size_t i = 0; i + 4 < sortedRanks.size(); i++) {
        bool consecutive = true;
        for (size_t j = 0; j < 4; j++) {
            if (sortedRanks[i + j + 1] - sortedRanks[i + j] != 1) {
                consecutive = false;
                break;
            }
        }
        if (consecutive) return true;
    }
    return false;
}

static std::map<int, int> countRanks(const std::vector<Card>& cards) {
    std::map<int, int> rankCount;
    for (const auto& card : cards) {
        rankCount[static_cast<int>(card.rank)]++;
    }
    return rankCount;
}

bool HandEvaluation::isFourOfAKind(const std::map<int, int>& rankCount) {
    for (const auto& entry : rankCount) {
        if (entry.second == 4) {
            return true;
        }
    }
    return false;
}

bool HandEvaluation::isFullHouse(const std::map<int, int>& rankCount) {
    bool hasThree = false;
    bool hasTwo = false;

    for (const auto& entry : rankCount) {
        if (entry.second == 3) hasThree = true;
        if (entry.second == 2) hasTwo = true;
    }

    return hasThree && hasTwo;
}

bool HandEvaluation::isThreeOfAKind(const std::map<int, int>& rankCount) {
    for (const auto& entry : rankCount) {
        if (entry.second == 3) return true;
    }
    return false;
}

bool HandEvaluation::isTwoPair(const std::map<int, int>& rankCount) {
    int pairCount = 0;
    for (const auto& entry : rankCount) {
        if (entry.second == 2) pairCount++;
    }
    return pairCount >= 2;
}


bool HandEvaluation::isPair(const std::map<int, int>& rankCount) {
    for (const auto& entry : rankCount) {
        if (entry.second == 2) return true;
    }
    return false;
}

// main hand evaluation func
HandRanks HandEvaluation::evaluateHand(const std::vector<Card>& hand, const std::vector<Card>& board) {
    std::vector<Card> allCards = hand;
    allCards.insert(allCards.end(), board.begin(), board.end());    

    auto rankCount = countRanks(allCards);

    bool flush = isFlush(allCards);
    bool straight = isStraight(allCards);

    if (flush && straight) return HandRanks::StraightFlush; 
    if(isFourOfAKind(rankCount)) return HandRanks::FourOfAKind; 
    if (flush) return HandRanks::Flush;
    if (isFullHouse(rankCount)) return HandRanks::FullHouse;

    if (straight) return HandRanks::Straight;

    if (isThreeOfAKind) return HandRanks::ThreeOfAKind;

    if (isTwoPair) return HandRanks::TwoPair;

    if (isPair) return HandRanks::Pair;

    return HandRanks::HighCard;

    
}

std::string handRankToString(HandRanks rank) {
    switch (rank) {
        case HandRanks::HighCard:     return "High Card";
        case HandRanks::Pair:         return "Pair";
        case HandRanks::TwoPair:      return "Two Pair";
        case HandRanks::ThreeOfAKind: return "Three of a Kind";
        case HandRanks::Straight:     return "Straight";
        case HandRanks::FullHouse:    return "Full House";
        case HandRanks::Flush:        return "Flush";
        case HandRanks::FourOfAKind:  return "Four of a Kind";
        case HandRanks::StraightFlush:return "Straight Flush";
        default:                      return "Unknown";
    }
}