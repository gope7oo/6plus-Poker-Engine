# 6+ Poker Engine (Short Deck Poker)

A C++ implementation of a **Short Deck (6+) Poker engine** that simulates a simplified poker game between a player and a computer opponent. The project focuses on modeling the mechanics of poker using object-oriented design and implementing the logic required to evaluate poker hands and manage gameplay.

This project demonstrates the use of **C++ data structures, algorithms, and object-oriented programming** to simulate a real-world card game system.

---

## Overview

Short Deck Poker (also called **6+ Hold'em**) is a poker variant played with a reduced deck where all cards below six are removed. This project implements the core mechanics of the game including:

* Card and deck management
* Player vs computer gameplay
* Hand evaluation
* Game state management

The goal of the project is to build a **poker engine capable of simulating rounds of play and determining winning hands**.

---

## Features

* Short Deck (6+) poker rules
* Card and deck representation
* Hand evaluation system
* Player vs computer gameplay
* Turn-based decision making
* Object-oriented architecture

---

## Project Structure

The project is organized into multiple classes that model the components of the game:

```
Poker Engine
│
├── Card
│   Represents a single playing card (rank and suit)
│
├── Deck
│   Generates and manages a short deck of cards
│
├── Player
│   Stores player cards and manages player actions
│
├── HandEvaluator
│   Determines the strength of poker hands
│
└── Game Engine
    Controls game flow, dealing cards, and determining the winner
```

---

## Example Gameplay

Example round output:

```
Player cards: Ah Kh
Computer cards: ??

Flop: 9h 8h 6c
Turn: Qd
River: Js

Player hand: Straight
Computer hand: Two Pair

Winner: Player
```

---

## Poker Rules (Short Deck)

Short Deck poker differs from traditional Texas Hold'em in several ways:

* Cards **2 through 5 are removed** from the deck
* The deck contains **36 cards instead of 52**
* Hand rankings are slightly different

Typical ranking order used in Short Deck:

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

---

## Technologies Used

* **C++**
* Standard Template Library (STL)
* Object-Oriented Programming

Key data structures used:

* `vector`
* `array`
* `enumerations`
* custom classes

---

## How to Run

Clone the repository:

```
git clone https://github.com/gope7oo/6plus-Poker-Engine.git
```

Compile the project:

```
g++ main.cpp -o poker
```

Run the program:

```
./poker
```

---

## Future Improvements

Possible future extensions for the engine include:

* Improved computer decision-making
* Betting system implementation
* Multiple player support
* Monte Carlo simulations for hand strength evaluation
* Graphical interface

---

## Learning Goals

This project was created to practice:

* Object-oriented design in C++
* Algorithm implementation
* Game logic modeling
* Working with complex state systems
* Card game simulations

---

