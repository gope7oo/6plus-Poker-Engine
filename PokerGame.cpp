

#include "PokerGame.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// constructor initializing the deck
PokerGame::PokerGame() {
    dealInitialHands();
}


// deal hands to player and computer 
void PokerGame::dealInitialHands() {
    playersHand.clear();
    dealersHand.clear();

    playersHand.push_back(deck.dealCard());
    dealersHand.push_back(deck.dealCard());
    playersHand.push_back(deck.dealCard());
    dealersHand.push_back(deck.dealCard());
}

// main game loop 
void PokerGame::playGame() {
    cout << "Starting Short Deck Poker Game!\n";

    while (playerMoney > 0 && computerMoney > 0) {
        playRound();

        if (playerMoney <= 0) {
            cout << "You are out. Game Over. \n";
            break;
        }
        if (computerMoney <= 0) {
            cout << "Computer is out of money. Game Over\n";
            break;
        }
    }
}


// handles the poker round
void PokerGame::playRound() { 
    board.clear();
    deck.createDeck();
    dealInitialHands();

    pot = 10;
    playerMoney -= 5;
    computerMoney -= 5;

    cout << "\nYour Hand: " << playersHand[0].toString() << ", " << playersHand[1].toString() << endl;
    
    if (!bettingRound("Pre-Flop")) return; 
    dealFlop();

    if (!bettingRound("Flop")) return;
    dealTurn();
    if (!bettingRound("Turn")) return; 
    dealRiver();
    if (!bettingRound("River")) return;

    HandRanks playerRank = HandEvaluation::evaluateHand(playersHand, board);
    HandRanks dealerRank = HandEvaluation::evaluateHand(dealersHand, board);

    cout << "\nShowdown!\n";
    cout << "Computer Hand: " << dealersHand[0].toString() << ", " << dealersHand[1].toString() << endl;

    cout << "Your Rank: " << handRankToString(playerRank) << endl;
    cout << "Computer Rank: " << handRankToString(dealerRank) << endl;

    if (playerRank > dealerRank) {
        cout << "You win $" << pot << "!\n"; 
    }
    else if (playerRank < dealerRank) {
        cout << "Computer wins $" << pot << "!\n";
    }
    else {
        cout << "Tie! Pot Split. \n";
        playerMoney += pot / 2;
        computerMoney += pot / 2;
    }
}


// deal the first 3 community cards
void PokerGame::dealFlop() {
    for (int i = 0; i < 3; i++) {
        board.push_back(deck.dealCard());
    }
    cout << "Flop: ";

    for (auto& card : board) {
        cout << card.toString() << ", ";
    }
    cout << endl;
}

void PokerGame::dealTurn() {
    board.push_back(deck.dealCard());
    cout << "Turn: " << board.back().toString() << endl;
}

void PokerGame::dealRiver() {
    board.push_back(deck.dealCard());
    cout << "River: " << board.back().toString() << endl;
}

// Simplified betting logic (cleaned for structure)
bool PokerGame::bettingRound(const string& stage) {
    cout << "\n--- " << stage << " Betting Round ---\n";
    cout << "Pot: $" << pot << " | Your Money: $" << playerMoney << endl;

    string action;
    cout << "Choose action (check/fold): ";
    cin >> action;

    if (action == "fold") {
        cout << "You folded. Computer wins the pot.\n";
        computerMoney += pot;
        return false;
    }

    cout << "You checked.\n";
    return true;
}

// Basic AI decision (can be improved later)
string PokerGame::computerDecision(int lastRaise) {
    int r = rand() % 3;
    if (r == 0) return "fold";
    if (r == 1) return "call";
    return "check";
}