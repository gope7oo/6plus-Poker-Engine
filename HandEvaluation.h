

#ifndef HANDEVALUATION_H
#define HANDEVALUATION_H

#include <vector>
#include <map>
#include <set>
#include "Card.h"

// Enum representing all poker hands strength
enum class HandRanks {
    HighCard, 
    Pair, 
    TwoPair,
    ThreeOfAKind,
    Straight,
    FullHouse, 
    Flush,
    FourOfAKind, 
    StraightFlush
};

// class for evaluating hands 
class HandEvaluation {
public:
    static HandRanks evaluateHand(const std::vector<Card>& hand, const std::vector<Card>& board);

private:
    static bool isFlush(const std::vector<Card>& cards);
    static bool isStraight(const std::vector<Card>& cards);
    static bool isFourOfAKind(const std::map<int, int>& rankCount);
    static bool isFullHouse(const std::map<int, int>& rankCount);
    static bool isThreeOfAKind(const std::map<int, int>& rankCount);
    static bool isTwoPair(const std::map<int, int>& rankCount);
    static bool isPair(const std::map<int, int>& rankCount);
};

std::string handRankToString(HandRanks rank);


#endif