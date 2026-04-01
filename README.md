# Short Deck Poker Engine (C++)

A modular C++ poker engine implementing the rules of Short Deck (6+) Hold’em, including hand evaluation, game flow, and a basic betting system.
The project models real poker mechanics such as dealing, round progression, player actions, and showdown logic, 
with a focus on clean architecture and extensibility for future AI-based decision making.

---

## Features

- Short Deck (6+) poker rules implementation  
- Card and deck management system  
- Hand evaluation engine with ranking and tie-breaking logic  
- Player vs computer gameplay  
- Basic betting system (Fold, Call, Raise)  
- Turn-based game flow  
- Object-oriented modular design  

---

## Game Flow

1. The deck is initialized and shuffled  
2. Each player is dealt two cards  
3. Game progresses through standard stages:
   - **Preflop**
   - **Flop** (3 community cards)
   - **Turn** (1 card)
   - **River** (1 card)
4. At each stage:
   - Players can take actions (Fold, Call, Raise)
5. At showdown:
   - Hands are evaluated using the HandEvaluator
6. The winner is determined and the round ends  

---

## Betting System

The engine includes a basic betting mechanism:

- **Fold** — player exits the round  
- **Call** — matches the current bet  
- **Raise** — increases the bet size  

This system simulates real decision-making and lays the foundation for future AI improvements.

---

## Architecture

Poker Engine

- Card  
  Represents a playing card (rank and suit)

- Deck  
  Manages the short deck (36 cards), including shuffling and dealing

- HandEvaluator  
  Evaluates and ranks poker hands based on hand strength

- Game Engine  
  Controls overall game flow, betting rounds, and determines the winner

---

### Example ranking (Short Deck):

1. Royal Flush  
2. Straight Flush  
3. Four of a Kind  
4. Flush  
5. Full House  
6. Straight  
7. Three of a Kind  
8. Two Pair  
9. Pair  
10. High Card  

Tie-breaking is handled by comparing:
- Highest card values  
- Secondary combinations (pairs, kickers)  

---

## Example Gameplay

Player cards: Ah 7h  
Computer cards: ??  

Preflop:  
Player: Raise  
Computer: Call  

Flop: 9h 8h 6c  
Turn: Qd  
River: Js  

Player hand: Straight (A-6-7-8-9)
Computer hand: Two Pair  

Winner: Player  

---

## Technologies Used

- C++  
- Standard Template Library (STL)  
- Object-Oriented Programming (OOP)  

### Key Data Structures:
- vector  
- array  
- enums  
- custom classes  

---

## How to Run

Clone the repository:

    git clone https://github.com/gope7oo/6plus-Poker-Engine.git

Compile:

    g++ main.cpp -o poker

Run:

    ./poker


## Future Improvements

- Add kicker logic
- Smarter AI using Monte Carlo simulations
- Advanced betting strategies
- Multiplayer support (multiple players at the table)
- Pot management and side pots
- Graphical user interface (GUI)



