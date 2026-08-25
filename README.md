# The Dark Arena

A turn-based console RPG written in C++ where memorization and pattern recognition matter more than raw stats. Choose a class, fight four enemies in sequence, and figure out — through trial, error, and careful observation — the exact hidden sequence of moves each enemy demands. Guess wrong, and it's instant death.

## Concept

There are no hints, no tutorials, and no visible clues. Every enemy has a fixed, secret pattern of required actions (**B**asic Attack, **F**inal Attack, **H**eal) that you must reproduce turn-by-turn to win. Deviate from the pattern even once and the enemy punishes you with a one-hit kill.

This turns a simple battler into a memory/deduction puzzle: you'll likely die a few times per enemy while you piece the sequence together, then execute it flawlessly on a later attempt.

## Features

- **Two playable classes** with different stats and abilities:
  - **Warrior** — high HP tank (700 HP), moderate damage
  - **Mage** — glass cannon (400 HP), devastating Final Attack
- **Ability gating system** — Basic Attack unlocks both Final Attack and Heal; using Final locks both again, while Heal only locks itself
- **Four escalating enemies** — Goblin, Orc, Minotaur, and Dragon, each with a unique required move pattern per class
- **Permadeath mechanic** — one wrong move triggers an instant critical kill
- **Partial recovery between levels** — heal a portion of max HP after clearing each stage
- **Polymorphic character system** — shared `Character` base class with `Player` and `Enemy` hierarchies, built with virtual functions and `unique_ptr` for clean memory management

## How to Play

1. Choose your class (Warrior or Mage) and name your character.
2. Each turn, pick one of three actions:
   - `1` — Basic Attack (always available)
   - `2` — Final Attack (only after Basic Attack)
   - `3` — Heal (only after Basic Attack)
3. There's no indicator for which move is "correct" — you have to learn the pattern by observing what happens.
4. A correct move damages the enemy (or heals you) and the enemy counterattacks. A wrong move ends the run immediately.
5. Clear all four enemies to win the game.

## Building

Requires a C++ compiler with C++11 support or later.

```bash
g++ -std=c++11 -o dark_arena main.cpp
./dark_arena
```

## Project Structure

```
.
├── main.cpp     # Full game source (classes, arena logic, main loop)
└── README.md
```

## Class Overview

| Class    | HP  | Basic Attack | Final Attack | Heal |
|----------|-----|---------------|---------------|------|
| Warrior  | 700 | 40            | 120           | 100  |
| Mage     | 400 | 55            | 220           | 100  |

## License

Feel free to fork, modify, and expand this project. Consider adding a license file (e.g. MIT) if you plan to share or accept contributions.
