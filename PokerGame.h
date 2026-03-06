


#ifndef POKERGAME_H
#define POKERGAME_H

#include <vector>
#include <string>
#include "Card.h"
#include "Deck.h"
#include "HandEvaluation.h"

// main class for poker game logic
class PokerGame {
private:
    Deck deck; 
    std::vector<Card> playersHand;
    std::vector<Card> dealersHand;
    std::vector<Card> board;

    int playerMoney = 100; // x
    int computerMoney = 100; // x

    int pot;

public:
    PokerGame();

    void playGame();
    void playRound();

    void dealInitialHands();
    void dealFlop();
    void dealTurn();
    void dealRiver();

    bool bettingRound(const std::string& stage); 

    std::string computerDecision(int lastRaise);
};



#endif