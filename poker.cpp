#include <bits/stdc++.h>
#include <thread> 
#include <chrono>

using namespace std;

enum class Suit {
    Spades,
    Hearts,
    Diamonds,
    Clubs
};

enum class Rank {
    Six = 6, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
};

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

class Card {
public:
    Suit suit;
    Rank rank;
    
    Card(Suit s, Rank r) : suit(s), rank(r) {}
    
    std::string toString() const {
        const std::string suits[] = {"♠", "♥", "♦", "♣"};
        const std::string ranks[] = {"Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
        return ranks[static_cast<int>(rank) - 6] + " of " + suits[static_cast<int>(suit)];
    }
};

vector<Card> createDeck() {
    vector<Card> deck;
    for (int s = 0; s < 4; ++s) {
        for (int r = 6; r <= 14; ++r) {
            deck.emplace_back(Card(static_cast<Suit>(s), static_cast<Rank>(r)));
        }
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);

    return deck;
}

void printDeck(const vector<Card>& deck) {
    for (const auto& card : deck) {
        cout << card.toString() << endl;
    }
}

class HandEvaluator {
public:
    static bool isFlush(const vector<Card>& cards) {
        if (cards.size() < 5) return false;
        map<Suit, int> suitCount;
        for (const auto& card : cards) suitCount[card.suit]++;
        for (const auto& entry : suitCount) if (entry.second >= 5) return true;
        return false;
    }

    static bool isStraight(const vector<Card>& cards) {
        if (cards.size() < 5) return false;
        set<int> ranks;
        for (const auto& card : cards) ranks.insert(static_cast<int>(card.rank));
        if (ranks.size() < 5) return false;
        vector<int> sortedRanks(ranks.begin(), ranks.end());
        for (size_t i = 0; i <= sortedRanks.size() - 5; ++i) {
            bool consecutive = true;
            for (size_t j = 0; j < 4; ++j)
                if (sortedRanks[i + j + 1] - sortedRanks[i + j] != 1) { consecutive = false; break; }
            if (consecutive) return true;
        }
        return sortedRanks.size() >= 5 && sortedRanks[0] == 6 && sortedRanks[1] == 7 &&
               sortedRanks[2] == 8 && sortedRanks[3] == 9 && sortedRanks.back() == 14;
    }

    static bool isFourOfAKind(const map<int, int>& rankCount) {
        for (const auto& entry : rankCount) if (entry.second == 4) return true;
        return false;
    }

    static bool isFullHouse(const map<int, int>& rankCount) {
        bool hasThree = false, hasTwo = false;
        for (const auto& entry : rankCount) {
            if (entry.second == 3) hasThree = true;
            if (entry.second == 2) hasTwo = true;
        }
        return hasThree && hasTwo;
    }

    static bool isThreeOfAKind(const map<int, int>& rankCount) {
        for (const auto& entry : rankCount) if (entry.second == 3) return true;
        return false;
    }

    static bool isTwoPair(const map<int, int>& rankCount) {
        int pairCount = 0;
        for (const auto& entry : rankCount) if (entry.second == 2) pairCount++;
        return pairCount >= 2;
    }

    static bool isPair(const map<int, int>& rankCount) {
        for (const auto& entry : rankCount) if (entry.second == 2) return true;
        return false;
    }

    static HandRanks evaluateHand(const vector<Card>& hand, const vector<Card>& board) {
        vector<Card> allCards = hand;
        allCards.insert(allCards.end(), board.begin(), board.end());

        map<int, int> rankCount;
        for (const auto& card : allCards) rankCount[static_cast<int>(card.rank)]++;

        bool flush = isFlush(allCards);
        bool straight = isStraight(allCards);

        if (flush && straight) return HandRanks::StraightFlush;
        if (isFourOfAKind(rankCount)) return HandRanks::FourOfAKind;
        if (isFullHouse(rankCount)) return HandRanks::FullHouse;
        if (flush) return HandRanks::Flush;
        if (straight) return HandRanks::Straight;
        if (isThreeOfAKind(rankCount)) return HandRanks::ThreeOfAKind;
        if (isTwoPair(rankCount)) return HandRanks::TwoPair;
        if (isPair(rankCount)) return HandRanks::Pair;

        return HandRanks::HighCard;
    }
};

string handRankToString(HandRanks rank) {
    switch (rank) {
        case HandRanks::HighCard: return "High Card";
        case HandRanks::Pair: return "Pair";
        case HandRanks::TwoPair: return "Two Pair";
        case HandRanks::ThreeOfAKind: return "Three of a Kind";
        case HandRanks::Straight: return "Straight";
        case HandRanks::Flush: return "Flush";
        case HandRanks::FullHouse: return "Full House";
        case HandRanks::FourOfAKind: return "Four of a Kind";
        case HandRanks::StraightFlush: return "Straight Flush";
        default: return "Unknown Hand";
    }
}

class PokerGame {
private:
    vector<Card> deck;
    vector<Card> playersHand;
    vector<Card> dealersHand;
    vector<Card> board;
    int playerMoney = 100;
    int computerMoney = 100;
    int pot; 

public:
    PokerGame() : deck(createDeck()) {
        deck = createDeck();
        dealInitialHands();
    }

    void dealInitialHands() {
        playersHand.push_back(deck.back()); deck.pop_back();
        dealersHand.push_back(deck.back()); deck.pop_back();
        playersHand.push_back(deck.back()); deck.pop_back();
        dealersHand.push_back(deck.back()); deck.pop_back();
    }

    void playGame() {
        cout << "Starting a new game of Poker!" << endl;
        while (playerMoney > 0 && computerMoney > 0) {
            pot = 0;
            playRound();
            if (playerMoney <= 0) {
                cout << "You are out of money! Game over." << endl;
                break;
            } else if (computerMoney <= 0) {
                cout << "The computer is out of money! You win!" << endl;
                break;
            }
        }
    }

    void playRound() {
        playersHand.clear();
        dealersHand.clear();
        board.clear();
        deck = createDeck();
        dealInitialHands();

        cout << "Your hand: " << playersHand[0].toString() << ", " << playersHand[1].toString() << endl;
        pot = 0;
        pot += 10;
        playerMoney -= 5;
        computerMoney -= 5;
        cout << "Starting pot: $" << pot << endl;

        if (!bettingRound("Pre-flop")) return;
        dealFlop();
        if (!bettingRound("Flop")) return;
        dealTurn();
        if (!bettingRound("Turn")) return;
        dealRiver();
        if (!bettingRound("River")) return;

        HandRanks playerRank = HandEvaluator::evaluateHand(playersHand, board);
        HandRanks dealerRank = HandEvaluator::evaluateHand(dealersHand, board);

        cout << "Showdown! Computer's hand was: " << dealersHand[0].toString() << ", " << dealersHand[1].toString() << endl;
        cout << "Your hand rank: " << handRankToString(playerRank) << ", Computer's hand rank: " << handRankToString(dealerRank) << endl;

        if (playerRank > dealerRank) {
            cout << "You win the pot of $" << pot << "!" << endl;
            playerMoney += pot;
        } else if (dealerRank > playerRank) {
            cout << "Computer wins the pot of $" << pot << "." << endl;
            computerMoney += pot;
        } else {
            cout << "It's a tie! The pot is split." << endl;
            playerMoney += pot / 2;
            computerMoney += pot / 2;
        }
    }

    void dealFlop() {
        for (int i = 0; i < 3; ++i) {
            board.push_back(deck.back());
            deck.pop_back();
        }
        cout << "Flop: ";
        for (const auto& card : board) cout << card.toString() << ", ";
        cout << endl;
    }

    void dealTurn() {
        board.push_back(deck.back());
        deck.pop_back();
        cout << "Turn: " << board.back().toString() << endl;
    }

    void dealRiver() {
        board.push_back(deck.back());
        deck.pop_back();
        cout << "River: " << board.back().toString() << endl;
    }

    // Function to handle the betting round
bool bettingRound(const string& stage) {
    cout << "Betting round: " << stage << endl;
    cout << "Your money: $" << playerMoney << ", Computer's money: $" << computerMoney << endl;

    int lastBet = 0;    // Track the last raise amount
    int playerCurrentBet = 0;    // Track the player's current bet for this round
    int computerCurrentBet = 0;  // Track the computer's current bet for this round
    bool playerAllIn = (playerMoney == 0), computerAllIn = (computerMoney == 0); // Start round knowing if either is all-in

    // Skip betting if both players are all-in
    if (playerAllIn && computerAllIn) {
        cout << "Both players are all-in. Proceeding to the next stage." << endl;
        return true;
    }

    while (true) {
        // Player's turn, only if not all-in
        if (!playerAllIn) {
            cout << "Pot: $" << pot << ", Your action (check, call, raise, fold, all-in): ";
            string playerAction;
            cin >> playerAction;

            if (playerAction == "fold") {
                cout << "You folded. Computer wins the pot of $" << pot << "." << endl;
                computerMoney += pot;
                return false;  // End round, player folds
            } else if (playerAction == "all-in") {
                playerCurrentBet += playerMoney;
                pot += playerMoney;
                playerMoney = 0;
                playerAllIn = true;
                cout << "You went all-in with $" << playerCurrentBet << ". Pot is now $" << pot << endl;
            } else if (playerAction == "raise") {
                int raiseAmount;
                cout << "Enter raise amount: ";
                cin >> raiseAmount;

                if (raiseAmount > playerMoney || raiseAmount <= 0) {
                    cout << "Invalid raise amount. Try again." << endl;
                    continue;
                }

                playerCurrentBet += raiseAmount;
                playerMoney -= raiseAmount;
                pot += raiseAmount;
                lastBet = raiseAmount;
                cout << "You raised $" << raiseAmount << ". Pot is now $" << pot << endl;
            } else if (playerAction == "call") {
                int callAmount = lastBet - playerCurrentBet;

                if (callAmount > playerMoney) {
                    callAmount = playerMoney;
                    playerAllIn = true;
                }

                playerCurrentBet += callAmount;
                playerMoney -= callAmount;
                pot += callAmount;
                cout << "You called. Pot is now $" << pot << endl;
            } else if (playerAction == "check" && lastBet == 0) {
                cout << "You checked." << endl;
            } else {
                cout << "Invalid action. Try again." << endl;
                continue;
            }
        }

        // End round immediately if player goes all-in
        if (playerAllIn) {
            // Computer must match or go all-in if it wants to continue
            if (!computerAllIn) {
                if (computerMoney >= playerCurrentBet - computerCurrentBet) {
                    int callAmount = playerCurrentBet - computerCurrentBet;
                    computerCurrentBet += callAmount;
                    computerMoney -= callAmount;
                    pot += callAmount;
                    cout << "Computer calls your all-in. Pot is now $" << pot << endl;
                } else {
                    pot += computerMoney;
                    computerCurrentBet += computerMoney;
                    computerMoney = 0;
                    computerAllIn = true;
                    cout << "Computer goes all-in with $" << computerCurrentBet << ". Pot is now $" << pot << endl;
                }
            }
            cout << "Betting round complete." << endl;
            return true;
        }

        // Computer's turn, only if not all-in
        if (!computerAllIn) {
            string computerAction = computerDecision(lastBet);

            if (computerAction == "fold") {
                cout << "Computer folds. You win the pot of $" << pot << "." << endl;
                playerMoney += pot;
                return false;  // End round, computer folds
            } else if (computerAction == "all-in") {
                computerCurrentBet += computerMoney;
                pot += computerMoney;
                computerMoney = 0;
                computerAllIn = true;
                cout << "Computer goes all-in with $" << computerCurrentBet << ". Pot is now $" << pot << endl;
            } else if (computerAction == "raise") {
                int raiseAmount = min(10 + rand() % 20, computerMoney);
                computerCurrentBet += raiseAmount;
                computerMoney -= raiseAmount;
                pot += raiseAmount;
                lastBet = raiseAmount;
                cout << "Computer raises $" << raiseAmount << ". Pot is now $" << pot << endl;
            } else if (computerAction == "call") {
                int callAmount = lastBet - computerCurrentBet;

                if (callAmount > computerMoney) {
                    callAmount = computerMoney;
                    computerAllIn = true;
                }

                computerCurrentBet += callAmount;
                computerMoney -= callAmount;
                pot += callAmount;
                cout << "Computer calls. Pot is now $" << pot << endl;
            } else if (computerAction == "check" && lastBet == 0) {
                cout << "Computer checks." << endl;
            }
        }

        // End round if both players are all-in or both have called the last bet
        if ((playerAllIn && computerAllIn) || (playerCurrentBet == lastBet && computerCurrentBet == lastBet)) {
            cout << "Betting round complete." << endl;
            return true;  // Move to next stage
        }
    }
}




// Function to handle computer's decision in response to player's all-in
string computerDecisionAllIn(int lastRaise) {
    if (computerMoney >= lastRaise) {
        return (rand() % 2 == 0) ? "call" : "fold";
    } else {
        return "call";  // If computer has less than the all-in amount, it will call with its remaining money
    }
}



    string computerDecision(int lastRaise) {
        HandRanks dealerRank = HandEvaluator::evaluateHand(dealersHand, board);
        bool strongHand = dealerRank >= HandRanks::TwoPair;
        bool mediumHand = dealerRank == HandRanks::Pair;
        
        bool bluff = (rand() % 10 < 1);
        
        if (strongHand || bluff) {
            return lastRaise > 0 ? "call" : "raise";
        } else if (mediumHand) {
            return lastRaise > 0 ? "call" : "check";
        } else {
            return lastRaise > 0 ? (rand() % 2 == 0 ? "fold" : "call") : "check";
        }
    }
};

int main() {
    PokerGame game;
    game.playGame();
    return 0;
}
