# The Dark Arena ⚔️

A console-based C++ battle game built using Object-Oriented Programming (OOP) concepts.

In **The Dark Arena**, the player chooses between a **Warrior** and a **Mage** and fights through four increasingly difficult enemies. The key mechanic is a hidden sequence of moves: choosing the correct action keeps the battle going, while one wrong move results in an instant critical-hit death.

## 🎮 Game Features

- Choose between **Warrior** and **Mage**
- Four levels of combat:
  - Goblin
  - Orc
  - Minotaur
  - Dragon
- Three player actions:
  - Basic Attack
  - Final Attack
  - Heal
- Hidden attack patterns that must be memorized
- Different patterns for Warrior and Mage
- Wrong move results in an **instant death**
- Health recovery between levels
- Console-based battle/status display
- Input validation for invalid numeric input

## 🧙 Character Classes

### Warrior

| Attribute | Value |
|---|---:|
| HP | 700 |
| Basic Damage | 40 |
| Final Damage | 120 |
| Heal | 100 |
| Basic Attack | Sword Slash |
| Final Attack | Berserker's Wrath |

### Mage

| Attribute | Value |
|---|---:|
| HP | 400 |
| Basic Damage | 55 |
| Final Damage | 220 |
| Heal | 100 |
| Basic Attack | Arcane Bolt |
| Final Attack | Meteor Storm |

## ⚔️ Battle System

The game uses three possible moves:

| Move | Description |
|---|---|
| **Basic Attack** | Always available and unlocks Final Attack + Heal |
| **Final Attack** | Deals high damage and locks Final Attack + Heal |
| **Heal** | Restores HP and becomes locked after use |

After a **Final Attack**, the player must use a **Basic Attack** next.

The enemy's required move pattern is hidden from the player. The player must remember and follow the correct sequence.

> **ONE WRONG MOVE = INSTANT DEATH**

## 👹 Enemies

### Warrior Route

| Level | Enemy | HP | Attack Damage |
|---|---|---:|---:|
| 1 | Goblin | 320 | 25 |
| 2 | Orc | 320 | 30 |
| 3 | Minotaur | 480 | 35 |
| 4 | Dragon | 640 | 40 |

### Mage Route

| Level | Enemy | HP | Attack Damage |
|---|---|---:|---:|
| 1 | Goblin | 275 | 20 |
| 2 | Orc | 550 | 25 |
| 3 | Minotaur | 605 | 30 |
| 4 | Dragon | 880 | 30 |

## 🧠 Hidden Move Patterns

The game internally stores the required sequence for each level and character class.

- `B` = Basic Attack
- `H` = Heal
- `F` = Final Attack

The player is **not shown the pattern** during the battle.

The patterns are designed so that following the correct sequence allows the player to defeat each enemy exactly.

## 🏗️ OOP Concepts Used

This project demonstrates several important C++ Object-Oriented Programming concepts.

### 1. Classes and Objects

The game is organized into classes such as:

- `Character`
- `Player`
- `Warrior`
- `Mage`
- `Enemy`
- `Arena`

### 2. Inheritance

`Player` inherits from `Character`.

`Warrior` and `Mage` inherit from `Player`.

`Enemy` also inherits from `Character`.

This creates a clear class hierarchy for the game characters.

### 3. Encapsulation

Important character data such as health, damage values, attack names, and ability states are stored inside classes with appropriate access control.

### 4. Abstraction

The `Player` class provides common functionality for different player types, while `Warrior` and `Mage` provide their specific roles and statistics.

### 5. Polymorphism

The `getRole()` function is declared as a pure virtual function in `Player` and implemented differently by `Warrior` and `Mage`.

```cpp
virtual string getRole() = 0;
```

### 6. Virtual Destructor

The base `Character` class contains a virtual destructor:

```cpp
virtual ~Character() {}
```

This supports safe destruction through base-class references/pointers.

### 7. Smart Pointers

The project uses `unique_ptr` to manage dynamically created player and enemy objects.

```cpp
unique_ptr<Player>
unique_ptr<Enemy>
```

### 8. STL Containers

A `vector` is used to store the enemies:

```cpp
vector<unique_ptr<Enemy>> enemies;
```

## 📂 Project Structure

```text
The-Dark-Arena/
│
├── oopfinalgame.cpp
└── README.md
```

## 💻 Requirements

To compile and run the project, you need:

- A C++ compiler
- C++11 or newer
- A terminal/console

The program uses standard C++ libraries including:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
```

## 🔨 Compilation

Using **g++**:

```bash
g++ oopfinalgame.cpp -o dark_arena
```

Then run:

### Windows

```bash
dark_arena.exe
```

### Linux / macOS

```bash
./dark_arena
```

## ▶️ How to Play

1. Start the program.
2. Read the game rules.
3. Choose:
   - `1` for Warrior
   - `2` for Mage
4. Enter your character name.
5. Enter each battle.
6. Observe the available actions and remember the correct sequence.
7. Select the correct move.
8. Defeat all four enemies.
9. Recover some HP between levels.
10. Defeat the Dragon to achieve **VICTORY**.

## ❤️ Health System

The player's health is reduced whenever an enemy successfully attacks.

The player can use the Heal ability when it is unlocked.

After each completed level, the player automatically recovers:

```text
Maximum HP / 5
```

This recovery happens between levels, except after the final level.

## ☠️ Game Over Conditions

The game ends when:

- The player chooses the wrong move.
- The player's HP reaches zero during an enemy attack.

A wrong move triggers the game's **Critical Hit** system and immediately kills the player.

## 🏆 Victory

To win the game, the player must successfully clear all four levels:

```text
Level 1 → Goblin
Level 2 → Orc
Level 3 → Minotaur
Level 4 → Dragon
```

After defeating the Dragon, the game displays a victory message and confirms that the player conquered the Dark Arena.

## 📚 Purpose of the Project

This project was developed as an OOP-based C++ game to demonstrate practical implementation of:

- Classes and objects
- Inheritance
- Polymorphism
- Encapsulation
- Abstraction
- Virtual functions
- Smart pointers
- STL vectors
- Conditional logic
- Loops
- Functions
- Console input/output

## 👨‍💻 Author

**C++ OOP Project — The Dark Arena**

---

⭐ If you enjoyed the project, consider giving the repository a star!
