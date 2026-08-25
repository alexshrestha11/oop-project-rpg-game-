#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>

using namespace std;


// ================================================================
// CHARACTER
// ================================================================
class Character
{
protected:
    string name;
    int health;
    int maxHealth;

public:

    Character(string n, int hp)
    {
        name = n;
        health = hp;
        maxHealth = hp;
    }

    virtual ~Character() {}

    string getName()
    {
        return name;
    }

    int getHealth()
    {
        return health;
    }

    int getMaxHealth()
    {
        return maxHealth;
    }

    bool isAlive()
    {
        return health > 0;
    }

    void takeDamage(int damage)
    {
        health -= damage;

        if (health < 0)
            health = 0;
    }

    void heal(int amount)
    {
        health += amount;

        if (health > maxHealth)
            health = maxHealth;
    }
};


// ================================================================
// PLAYER BASE CLASS
// ================================================================
class Player : public Character
{
protected:

    int basicDamage;
    int finalDamage;
    int healAmount;

    bool finalUnlocked;
    bool healUnlocked;

    string basicAttackName;
    string finalAttackName;

public:

    Player(
        string n,
        int hp,
        int basic,
        int finalAtk,
        int heal,
        string basicName,
        string finalName
    )
        : Character(n, hp)
    {
        basicDamage = basic;
        finalDamage = finalAtk;
        healAmount = heal;

        finalUnlocked = false;
        healUnlocked = false;

        basicAttackName = basicName;
        finalAttackName = finalName;
    }

    virtual string getRole() = 0;


    // ============================================================
    // RESET ABILITIES
    // ============================================================
    void resetAbilities()
    {
        finalUnlocked = false;
        healUnlocked = false;
    }


    // ============================================================
    // BASIC ATTACK
    //
    // Basic unlocks Final + Heal
    // ============================================================
    int basicAttack()
    {
        finalUnlocked = true;
        healUnlocked = true;

        cout << "\n";
        cout << name
             << " uses "
             << basicAttackName
             << "!"
             << endl;

        cout << "Damage: "
             << basicDamage
             << endl;

        cout << "FINAL ATTACK UNLOCKED!"
             << endl;

        cout << "HEAL UNLOCKED!"
             << endl;

        return basicDamage;
    }


    // ============================================================
    // FINAL ATTACK
    //
    // Final locks BOTH Final and Heal.
    // ============================================================
    int finalAttack()
    {
        if (!finalUnlocked)
        {
            cout << "\nFINAL ATTACK IS LOCKED!"
                 << endl;

            return -1;
        }

        finalUnlocked = false;
        healUnlocked = false;

        cout << "\n";
        cout << name
             << " uses "
             << finalAttackName
             << "!"
             << endl;

        cout << "FINAL DAMAGE: "
             << finalDamage
             << endl;

        cout << "FINAL ATTACK LOCKED!"
             << endl;

        cout << "HEAL LOCKED!"
             << endl;

        return finalDamage;
    }


    // ============================================================
    // HEAL
    //
    // Heal locks itself.
    // Final remains available.
    // ============================================================
    bool useHeal()
    {
        if (!healUnlocked)
        {
            cout << "\nHEAL IS LOCKED!"
                 << endl;

            return false;
        }

        healUnlocked = false;

        int oldHealth = health;

        heal(healAmount);

        int recovered = health - oldHealth;

        cout << "\n";
        cout << name
             << " uses HEAL!"
             << endl;

        cout << "Recovered: "
             << recovered
             << " HP"
             << endl;

        cout << "HEAL IS NOW LOCKED."
             << endl;

        return true;
    }


    // ============================================================
    // STATUS
    // ============================================================
    void showStatus()
    {
        cout << "\n";
        cout << "----------------------------------------"
             << endl;

        cout << name
             << " ["
             << getRole()
             << "]"
             << endl;

        cout << "HP: "
             << health
             << " / "
             << maxHealth
             << endl;

        cout << "Basic Attack: READY"
             << endl;

        cout << "Final Attack: ";

        if (finalUnlocked)
            cout << "READY";
        else
            cout << "LOCKED";

        cout << endl;

        cout << "Heal: ";

        if (healUnlocked)
            cout << "READY";
        else
            cout << "LOCKED";

        cout << endl;

        cout << "----------------------------------------"
             << endl;
    }


    bool isFinalUnlocked()
    {
        return finalUnlocked;
    }

    bool isHealUnlocked()
    {
        return healUnlocked;
    }
};


// ================================================================
// WARRIOR
// ================================================================
class Warrior : public Player
{
public:

    Warrior(string n)
        : Player(
            n,
            700,              // HP
            40,               // Basic
            120,              // Final
            100,              // Heal
            "Sword Slash",
            "Berserker's Wrath"
        )
    {
    }

    string getRole()
    {
        return "Warrior";
    }
};


// ================================================================
// MAGE
// ================================================================
class Mage : public Player
{
public:

    Mage(string n)
        : Player(
            n,
            400,              // HP
            55,               // Basic
            220,              // Final
            100,              // Heal
            "Arcane Bolt",
            "Meteor Storm"
        )
    {
    }

    string getRole()
    {
        return "Mage";
    }
};


// ================================================================
// ENEMY
// ================================================================
class Enemy : public Character
{
private:
    int attackDamage;
    string attackName;

public:

    Enemy(
        string n,
        int hp,
        int damage,
        string attack
    )
        : Character(n, hp)
    {
        attackDamage = damage;
        attackName = attack;
    }


    int attack(Player& player)
    {
        cout << "\n";
        cout << name
             << " uses "
             << attackName
             << "!"
             << endl;

        player.takeDamage(attackDamage);

        cout << player.getName()
             << " takes "
             << attackDamage
             << " damage."
             << endl;

        return attackDamage;
    }


    void showStatus()
    {
        cout << "\n";
        cout << name
             << " HP: "
             << health
             << " / "
             << maxHealth
             << endl;
    }
};


// ================================================================
// ARENA
// ================================================================
class Arena
{
private:

    vector<unique_ptr<Enemy>> enemies;


    // ============================================================
    // GET PATTERN
    //
    // B = Basic
    // H = Heal
    // F = Final
    //
    // These patterns are hidden from the player.
    // ============================================================
    vector<char> getPattern(
        Player& player,
        int level
    )
    {
        vector<char> pattern;


        // ========================================================
        // WARRIOR
        // ========================================================
        if (player.getRole() == "Warrior")
        {
            if (level == 1)
            {
                // Goblin
                pattern = {
                    'B',
                    'F',
                    'B',
                    'H',
                    'F'
                };
            }

            else if (level == 2)
            {
                // Orc
                pattern = {
                    'B',
                    'H',
                    'F',
                    'B',
                    'F'
                };
            }

            else if (level == 3)
            {
                // Minotaur
                pattern = {
                    'B',
                    'F',
                    'B',
                    'H',
                    'F',
                    'B',
                    'H',
                    'F'
                };
            }

            else
            {
                // Dragon
                pattern = {
                    'B',
                    'H',
                    'F',
                    'B',
                    'F',
                    'B',
                    'H',
                    'F',
                    'B',
                    'F'
                };
            }
        }


        // ========================================================
        // MAGE
        // ========================================================
        else
        {
            if (level == 1)
            {
                // Goblin
                pattern = {
                    'B',
                    'H',
                    'F'
                };
            }

            else if (level == 2)
            {
                // Orc
                pattern = {
                    'B',
                    'F',
                    'B',
                    'H',
                    'F'
                };
            }

            else if (level == 3)
            {
                // Minotaur
                pattern = {
                    'B',
                    'H',
                    'B',
                    'F',
                    'B',
                    'H',
                    'F'
                };
            }

            else
            {
                // Dragon
                pattern = {
                    'B',
                    'H',
                    'F',
                    'B',
                    'H',
                    'B',
                    'F',
                    'B',
                    'H',
                    'F'
                };
            }
        }

        return pattern;
    }


    // ============================================================
    // CREATE ENEMIES
    //
    // Enemy HP is calculated from the pattern.
    // Therefore the FINAL attack defeats the enemy exactly.
    // ============================================================
    void createEnemies(Player& player)
    {
        vector<char> pattern;


        // ========================================================
        // WARRIOR
        // ========================================================
        if (player.getRole() == "Warrior")
        {
            // -----------------------------
            // GOBLIN
            // B F B H F
            //
            // 2 Basic + 2 Final
            // = 80 + 240
            // = 320
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Goblin",
                        320,
                        25,
                        "Claw Swipe"
                    )
                )
            );


            // -----------------------------
            // ORC
            // B H F B F
            //
            // 2 Basic + 2 Final
            // = 320
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Orc",
                        320,
                        30,
                        "Club Smash"
                    )
                )
            );


            // -----------------------------
            // MINOTAUR
            // B F B H F B H F
            //
            // 3 Basic + 3 Final
            // = 120 + 360
            // = 480
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Minotaur",
                        480,
                        35,
                        "Horn Charge"
                    )
                )
            );


            // -----------------------------
            // DRAGON
            // B H F B F B H F B F
            //
            // 4 Basic + 4 Final
            // = 160 + 480
            // = 640
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Dragon",
                        640,
                        40,
                        "Flame Breath"
                    )
                )
            );
        }


        // ========================================================
        // MAGE
        // ========================================================
        else
        {
            // -----------------------------
            // GOBLIN
            // B H F
            //
            // 1 Basic + 1 Final
            // = 55 + 220
            // = 275
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Goblin",
                        275,
                        20,
                        "Claw Swipe"
                    )
                )
            );


            // -----------------------------
            // ORC
            // B F B H F
            //
            // 2 Basic + 2 Final
            // = 110 + 440
            // = 550
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Orc",
                        550,
                        25,
                        "Club Smash"
                    )
                )
            );


            // -----------------------------
            // MINOTAUR
            // B H B F B H F
            //
            // 3 Basic + 2 Final
            // = 165 + 440
            // = 605
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Minotaur",
                        605,
                        30,
                        "Horn Charge"
                    )
                )
            );


            // -----------------------------
            // DRAGON
            // B H F B H B F B H F
            //
            // 4 Basic + 3 Final
            // = 220 + 660
            // = 880
            // -----------------------------

            enemies.push_back(
                unique_ptr<Enemy>(
                    new Enemy(
                        "Dragon",
                        880,
                        30,
                        "Flame Breath"
                    )
                )
            );
        }
    }


    // ============================================================
    // INPUT
    // ============================================================
    int getChoice()
    {
        int choice;

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            return -1;
        }

        return choice;
    }


    // ============================================================
    // WRONG MOVE
    //
    // WRONG MOVE = INSTANT DEATH
    // ============================================================
    void criticalHit(
        Player& player,
        Enemy& enemy
    )
    {
        cout << "\n";
        cout << "=================================================="
             << endl;

        cout << "                  WRONG MOVE!"
             << endl;

        cout << "=================================================="
             << endl;

        cout << enemy.getName()
             << " detected your mistake!"
             << endl;

        cout << "\n";
        cout << "The enemy launches a CRITICAL HIT!"
             << endl;

        cout << "\n";
        cout << "                CRITICAL HIT!!!"
             << endl;

        cout << "\n";
        cout << player.getName()
             << " has been killed instantly!"
             << endl;

        player.takeDamage(
            player.getHealth()
        );

        cout << "\n";
        cout << "GAME OVER!"
             << endl;
    }


    // ============================================================
    // BATTLE
    // ============================================================
    void battle(
        Player& player,
        Enemy& enemy,
        int level
    )
    {
        player.resetAbilities();


        vector<char> pattern =
            getPattern(
                player,
                level
            );


        int step = 0;
        int turn = 1;


        cout << "\n";
        cout << "=================================================="
             << endl;

        cout << "                    LEVEL "
             << level
             << endl;

        cout << "                 ENEMY: "
             << enemy.getName()
             << endl;

        cout << "=================================================="
             << endl;


        cout << "\n";
        cout << "No clues are available."
             << endl;

        cout << "Study the enemy and remember the pattern."
             << endl;

        cout << "ONE WRONG MOVE = INSTANT DEATH."
             << endl;


        // ========================================================
        // BATTLE LOOP
        // ========================================================

        while (
            player.isAlive() &&
            enemy.isAlive() &&
            step < (int)pattern.size()
        )
        {
            cout << "\n";
            cout << "================ TURN "
                 << turn
                 << " ================"
                 << endl;


            player.showStatus();

            enemy.showStatus();


            // ====================================================
            // MENU
            // ====================================================

            cout << "\n";
            cout << "Choose your action:"
                 << endl;

            cout << "1. Basic Attack"
                 << endl;

            cout << "2. Final Attack ";

            if (player.isFinalUnlocked())
                cout << "[READY]";
            else
                cout << "[LOCKED]";

            cout << endl;

            cout << "3. Heal ";

            if (player.isHealUnlocked())
                cout << "[READY]";
            else
                cout << "[LOCKED]";

            cout << endl;


            cout << "\n> ";


            int choice =
                getChoice();


            char selectedMove;


            if (choice == 1)
            {
                selectedMove = 'B';
            }

            else if (choice == 2)
            {
                selectedMove = 'F';
            }

            else if (choice == 3)
            {
                selectedMove = 'H';
            }

            else
            {
                cout << "\nInvalid choice!"
                     << endl;

                continue;
            }


            // ====================================================
            // CHECK PATTERN
            //
            // Player NEVER sees pattern[step].
            // ====================================================

            if (selectedMove != pattern[step])
            {
                criticalHit(
                    player,
                    enemy
                );

                return;
            }


            // ====================================================
            // BASIC
            // ====================================================

            if (selectedMove == 'B')
            {
                int damage =
                    player.basicAttack();

                enemy.takeDamage(damage);

                cout << "\nCORRECT MOVE!"
                     << endl;
            }


            // ====================================================
            // FINAL
            // ====================================================

            else if (selectedMove == 'F')
            {
                int damage =
                    player.finalAttack();

                if (damage > 0)
                {
                    enemy.takeDamage(damage);

                    cout << "\nCORRECT MOVE!"
                         << endl;
                }
            }


            // ====================================================
            // HEAL
            // ====================================================

            else if (selectedMove == 'H')
            {
                bool success =
                    player.useHeal();

                if (!success)
                {
                    return;
                }

                cout << "\nCORRECT MOVE!"
                     << endl;
            }


            // ====================================================
            // CHECK ENEMY
            // ====================================================

            if (!enemy.isAlive())
            {
                cout << "\n";
                cout << "=================================================="
                     << endl;

                cout << "               ENEMY DEFEATED!"
                     << endl;

                cout << "=================================================="
                     << endl;

                return;
            }


            // ====================================================
            // ENEMY ATTACK
            //
            // Only occurs after a correct move.
            // ====================================================

            enemy.attack(player);


            if (!player.isAlive())
            {
                cout << "\n";
                cout << "=================================================="
                     << endl;

                cout << "                    GAME OVER"
                     << endl;

                cout << "=================================================="
                     << endl;

                return;
            }


            // ====================================================
            // ADVANCE PATTERN
            // ====================================================

            step++;

            turn++;
        }


        // ========================================================
        // LEVEL COMPLETE
        // ========================================================

        if (!enemy.isAlive())
        {
            cout << "\n";
            cout << "LEVEL "
                 << level
                 << " CLEARED!"
                 << endl;
        }
    }


    // ============================================================
    // CHARACTER SELECTION
    // ============================================================
    unique_ptr<Player> choosePlayer()
    {
        cout << "\n";
        cout << "=================================================="
             << endl;

        cout << "               CHOOSE YOUR ROLE"
             << endl;

        cout << "=================================================="
             << endl;


        cout << "\n";
        cout << "1. WARRIOR"
             << endl;

        cout << "   HP: 700"
             << endl;

        cout << "   Basic: 40"
             << endl;

        cout << "   Final: 120"
             << endl;

        cout << "   Heal: 100"
             << endl;


        cout << "\n";
        cout << "2. MAGE"
             << endl;

        cout << "   HP: 400"
             << endl;

        cout << "   Basic: 55"
             << endl;

        cout << "   Final: 220"
             << endl;

        cout << "   Heal: 100"
             << endl;


        cout << "\nChoose: ";


        int choice =
            getChoice();


        cout << "\nEnter your name: ";

        string playerName;

        cin >> playerName;


        if (choice == 1)
        {
            return unique_ptr<Player>(
                new Warrior(playerName)
            );
        }

        else if (choice == 2)
        {
            return unique_ptr<Player>(
                new Mage(playerName)
            );
        }

        else
        {
            cout << "Invalid choice."
                 << endl;

            cout << "Warrior selected."
                 << endl;

            return unique_ptr<Player>(
                new Warrior(playerName)
            );
        }
    }


public:

    // ============================================================
    // START GAME
    // ============================================================
    void start()
    {
        cout << "\n";
        cout << "=================================================="
             << endl;

        cout << "                 THE DARK ARENA"
             << endl;

        cout << "=================================================="
             << endl;


        cout << "\nRULES"
             << endl;

        cout << "-----------------------------------------------"
             << endl;

        cout << "1. Choose Warrior or Mage."
             << endl;

        cout << "2. Basic Attack is always available."
             << endl;

        cout << "3. Basic Attack unlocks Final Attack and Heal."
             << endl;

        cout << "4. Heal becomes locked after being used."
             << endl;

        cout << "5. Final Attack locks both Final and Heal."
             << endl;

        cout << "6. After Final Attack, Basic Attack must come next."
             << endl;

        cout << "7. There are NO clues."
             << endl;

        cout << "8. Warrior and Mage have different patterns."
             << endl;

        cout << "9. Wrong move = CRITICAL HIT."
             << endl;

        cout << "10. Critical Hit = INSTANT DEATH."
             << endl;

        cout << "11. Follow the complete pattern to defeat the enemy."
             << endl;

        cout << "-----------------------------------------------"
             << endl;


        // ========================================================
        // SELECT PLAYER
        // ========================================================

        unique_ptr<Player> player =
            choosePlayer();


        // ========================================================
        // CREATE ENEMIES
        // ========================================================

        createEnemies(*player);


        // ========================================================
        // FOUR LEVELS
        // ========================================================

        for (int level = 1;
             level <= 4;
             level++)
        {
            battle(
                *player,
                *enemies[level - 1],
                level
            );


            if (!player->isAlive())
            {
                return;
            }


            // ====================================================
            // HEAL BETWEEN LEVELS
            // ====================================================

            if (level < 4)
            {
                int oldHealth =
                    player->getHealth();


                player->heal(
                    player->getMaxHealth() / 5
                );


                int recovered =
                    player->getHealth()
                    - oldHealth;


                cout << "\n";
                cout << "You recover "
                     << recovered
                     << " HP before the next battle."
                     << endl;
            }
        }


        // ========================================================
        // VICTORY
        // ========================================================

        cout << "\n";
        cout << "=================================================="
             << endl;

        cout << "                    VICTORY!"
             << endl;

        cout << "=================================================="
             << endl;

        cout << "\n";
        cout << player->getName()
             << " conquered the Dark Arena!"
             << endl;
    }
};


// ================================================================
// MAIN
// ================================================================
int main()
{
    Arena game;

    game.start();

    return 0;
}
