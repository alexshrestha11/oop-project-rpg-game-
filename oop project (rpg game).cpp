#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>

using namespace std;


// ================================================================
// CHARACTER BASE CLASS
// ================================================================
class Character
{
protected:
    string name;
    int health;
    int maxHealth;
    int attackPower;

public:

    Character(const string& n, int hp, int atk)
        : name(n), health(hp), maxHealth(hp), attackPower(atk)
    {
    }

    virtual ~Character() {}

    string getName() const
    {
        return name;
    }

    int getHealth() const
    {
        return health;
    }

    int getMaxHealth() const
    {
        return maxHealth;
    }

    bool isAlive() const
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

    virtual int basicAttack() = 0;
    virtual int finalAttack() = 0;
};


// ================================================================
// PLAYER BASE CLASS
// ================================================================
class Player : public Character
{
protected:

    bool finalUnlocked;
    bool healUnlocked;

    string basicAttackName;
    string finalAttackName;

    int healAmount;

public:

    Player(const string& n,
           int hp,
           int atk,
           const string& basicName,
           const string& finalName,
           int healValue)

        : Character(n, hp, atk),
          finalUnlocked(false),
          healUnlocked(false),
          basicAttackName(basicName),
          finalAttackName(finalName),
          healAmount(healValue)
    {
    }

    virtual string getRoleName() const = 0;


    // ============================================================
    // CHECK FINAL
    // ============================================================
    bool isFinalUnlocked() const
    {
        return finalUnlocked;
    }


    // ============================================================
    // CHECK HEAL
    // ============================================================
    bool isHealUnlocked() const
    {
        return healUnlocked;
    }


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
    // Basic unlocks BOTH Final and Heal.
    // ============================================================
    int basicAttack() override
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
             << attackPower
             << endl;

        cout << "FINAL ATTACK UNLOCKED!"
             << endl;

        cout << "HEAL UNLOCKED!"
             << endl;

        return attackPower;
    }


    // ============================================================
    // FINAL ATTACK
    //
    // Requires Basic Attack.
    //
    // After Final:
    // Final = locked
    // Heal = locked
    // ============================================================
    int finalAttack() override
    {
        if (!finalUnlocked)
        {
            cout << "\nFINAL ATTACK IS LOCKED!"
                 << endl;

            cout << "Use BASIC ATTACK first."
                 << endl;

            return 0;
        }

        finalUnlocked = false;
        healUnlocked = false;

        cout << "\n";
        cout << name
             << " unleashes "
             << finalAttackName
             << "!"
             << endl;

        return attackPower * 2;
    }


    // ============================================================
    // HEAL
    //
    // Requires Basic Attack.
    //
    // After Heal:
    // Heal = locked
    // Final = remains available
    // ============================================================
    bool useHeal()
    {
        if (!healUnlocked)
        {
            cout << "\nHEAL IS LOCKED!"
                 << endl;

            cout << "Use BASIC ATTACK first."
                 << endl;

            return false;
        }

        healUnlocked = false;

        int oldHealth = health;

        heal(healAmount);

        int recovered =
            health - oldHealth;

        cout << "\n";
        cout << name
             << " uses HEAL!"
             << endl;

        cout << "Recovered: "
             << recovered
             << " HP"
             << endl;

        cout << "HP: "
             << health
             << "/"
             << maxHealth
             << endl;

        return true;
    }


    // ============================================================
    // SHOW PLAYER STATUS
    // ============================================================
    void showStatus() const
    {
        cout << "\n";
        cout << "--------------------------------------------"
             << endl;

        cout << name
             << " ["
             << getRoleName()
             << "]"
             << endl;

        cout << "HP: "
             << health
             << "/"
             << maxHealth
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

        cout << "--------------------------------------------"
             << endl;
    }
};


// ================================================================
// WARRIOR
// ================================================================
class Warrior : public Player
{
public:

    Warrior(const string& n)
        : Player(
            n,
            700,
            40,
            "Sword Slash",
            "Berserker's Wrath",
            100
        )
    {
    }

    string getRoleName() const override
    {
        return "Warrior";
    }


    int finalAttack() override
    {
        if (!finalUnlocked)
        {
            cout << "\nFINAL ATTACK IS LOCKED!"
                 << endl;

            return 0;
        }

        finalUnlocked = false;
        healUnlocked = false;

        cout << "\n";
        cout << name
             << " unleashes BERSERKER'S WRATH!"
             << endl;

        return 120;
    }
};


// ================================================================
// MAGE
// ================================================================
class Mage : public Player
{
public:

    Mage(const string& n)
        : Player(
            n,
            400,
            55,
            "Arcane Bolt",
            "Meteor Storm",
            100
        )
    {
    }

    string getRoleName() const override
    {
        return "Mage";
    }


    int finalAttack() override
    {
        if (!finalUnlocked)
        {
            cout << "\nFINAL ATTACK IS LOCKED!"
                 << endl;

            return 0;
        }

        finalUnlocked = false;
        healUnlocked = false;

        cout << "\n";
        cout << name
             << " summons METEOR STORM!"
             << endl;

        return 220;
    }
};


// ================================================================
// ENEMY BASE CLASS
// ================================================================
class Enemy : public Character
{
protected:

    string attackName;

public:

    Enemy(const string& n,
          int hp,
          int atk,
          const string& attack)

        : Character(n, hp, atk),
          attackName(attack)
    {
    }


    int basicAttack() override
    {
        cout << "\n";
        cout << name
             << " uses "
             << attackName
             << "!"
             << endl;

        return attackPower;
    }


    int finalAttack() override
    {
        return attackPower * 2;
    }


    void showStatus() const
    {
        cout << "\n";
        cout << name
             << " HP: "
             << health
             << "/"
             << maxHealth
             << endl;
    }
};


// ================================================================
// ENEMIES
// ================================================================
class Goblin : public Enemy
{
public:

    Goblin(int hp)
        : Enemy(
            "Goblin",
            hp,
            25,
            "Claw Swipe"
        )
    {
    }
};


class Orc : public Enemy
{
public:

    Orc(int hp)
        : Enemy(
            "Orc",
            hp,
            35,
            "Club Smash"
        )
    {
    }
};


class Minotaur : public Enemy
{
public:

    Minotaur(int hp)
        : Enemy(
            "Minotaur",
            hp,
            45,
            "Horn Charge"
        )
    {
    }
};


class Dragon : public Enemy
{
public:

    Dragon(int hp)
        : Enemy(
            "Dragon",
            hp,
            60,
            "Flame Breath"
        )
    {
    }
};


// ================================================================
// ARENA
// ================================================================
class Arena
{
private:

    vector<unique_ptr<Enemy> > enemies;


    // ============================================================
    // BASIC DAMAGE
    // ============================================================
    int getBasicDamage(Player& player)
    {
        if (player.getRoleName() == "Warrior")
            return 40;

        if (player.getRoleName() == "Mage")
            return 55;

        return 0;
    }


    // ============================================================
    // FINAL DAMAGE
    // ============================================================
    int getFinalDamage(Player& player)
    {
        if (player.getRoleName() == "Warrior")
            return 120;

        if (player.getRoleName() == "Mage")
            return 220;

        return 0;
    }


    // ============================================================
    // BUILD ENEMIES
    //
    // The HP is calculated so the complete pattern is required.
    // ============================================================
    void buildLevels(Player& player)
    {
        int B = getBasicDamage(player);
        int F = getFinalDamage(player);


        /*
        ============================================================
        WARRIOR PATTERNS

        Goblin:
        B -> F -> B -> H -> F

        Orc:
        B -> H -> B -> F -> B -> F

        Minotaur:
        B -> F -> H -> B -> F -> B -> H -> F

        Dragon:
        B -> F -> B -> H -> F -> B -> F -> H -> B -> F


        MAGE PATTERNS

        Goblin:
        B -> H -> F

        Orc:
        B -> F -> H -> B -> H -> F

        Minotaur:
        B -> H -> F -> B -> H -> B -> F -> H -> F

        Dragon:
        B -> H -> B -> F -> H -> B
        -> H -> F -> B -> H -> F
        ============================================================
        */


        // --------------------------------------------------------
        // HP values
        // --------------------------------------------------------

        if (player.getRoleName() == "Warrior")
        {
            // Goblin:
            // B + F + B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Goblin(2 * B + 2 * F)
                )
            );


            // Orc:
            // B + B + F + B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Orc(3 * B + 2 * F)
                )
            );


            // Minotaur:
            // B + B + F + B + F + B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Minotaur(4 * B + 3 * F)
                )
            );


            // Dragon:
            // B + B + B + F + B + F + B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Dragon(5 * B + 3 * F)
                )
            );
        }


        else
        {
            // ----------------------------------------------------
            // MAGE
            // ----------------------------------------------------

            // Goblin:
            // B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Goblin(B + F)
                )
            );


            // Orc:
            // B + F + B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Orc(2 * B + 2 * F)
                )
            );


            // Minotaur:
            // B + F + B + B + F + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Minotaur(3 * B + 3 * F)
                )
            );


            // Dragon:
            // B + B + F + B + F + B + F
            enemies.push_back(
                unique_ptr<Enemy>(
                    new Dragon(4 * B + 3 * F)
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
    // GET REQUIRED MOVE
    //
    // IMPORTANT:
    // This is NEVER displayed to the player.
    // ============================================================
    char getRequiredMove(
        Player& player,
        int level,
        int step
    )
    {
        vector<char> pattern;


        // ========================================================
        // WARRIOR PATTERNS
        // ========================================================
        if (player.getRoleName() == "Warrior")
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
                    'B',
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
                    'F',
                    'B',
                    'H',
                    'F',
                    'B',
                    'F',
                    'H',
                    'B',
                    'F'
                };
            }
        }


        // ========================================================
        // MAGE PATTERNS
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
                    'H',
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
                    'F',
                    'B',
                    'H',
                    'B',
                    'F',
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
                    'B',
                    'F',
                    'H',
                    'B',
                    'H',
                    'F',
                    'B',
                    'H',
                    'F'
                };
            }
        }


        if (step >= 0 &&
            step < (int)pattern.size())
        {
            return pattern[step];
        }


        return 'B';
    }


    // ============================================================
    // PATTERN LENGTH
    // ============================================================
    int getPatternLength(
        Player& player,
        int level
    )
    {
        if (player.getRoleName() == "Warrior")
        {
            if (level == 1)
                return 5;

            if (level == 2)
                return 6;

            if (level == 3)
                return 8;

            return 10;
        }

        else
        {
            if (level == 1)
                return 3;

            if (level == 2)
                return 6;

            if (level == 3)
                return 9;

            return 11;
        }
    }


    // ============================================================
    // WRONG MOVE
    //
    // WRONG MOVE = INSTANT DEATH
    // ============================================================
    void wrongMove(
        Player& player,
        Enemy& enemy
    )
    {
        cout << "\n";
        cout << "============================================================"
             << endl;

        cout << "                    WRONG MOVE!"
             << endl;

        cout << "============================================================"
             << endl;


        cout << enemy.getName()
             << " detected your mistake!"
             << endl;


        cout << "\n";
        cout << "The enemy prepares a devastating attack..."
             << endl;

        cout << "\n";
        cout << "                    CRITICAL HIT!"
             << endl;


        // Instant kill
        player.takeDamage(
            player.getHealth()
        );


        cout << "\n";
        cout << player.getName()
             << " has been killed instantly!"
             << endl;


        cout << "\n";
        cout << "============================================================"
             << endl;

        cout << "                       GAME OVER"
             << endl;

        cout << "============================================================"
             << endl;


        cout << "\n";
        cout << "You broke the enemy's attack pattern."
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


        int step = 0;

        int patternLength =
            getPatternLength(
                player,
                level
            );

        int turn = 1;


        cout << "\n";
        cout << "============================================================"
             << endl;

        cout << "                         LEVEL "
             << level
             << endl;

        cout << "                     ENEMY: "
             << enemy.getName()
             << endl;

        cout << "============================================================"
             << endl;


        cout << "\n";
        cout << "The enemy has entered the arena."
             << endl;

        cout << "There are NO clues."
             << endl;

        cout << "Study the enemy's pattern carefully."
             << endl;

        cout << "ONE WRONG MOVE = INSTANT DEATH."
             << endl;


        while (
            player.isAlive() &&
            enemy.isAlive() &&
            step < patternLength
        )
        {
            cout << "\n";
            cout << "==================== TURN "
                 << turn
                 << " ===================="
                 << endl;


            player.showStatus();

            enemy.showStatus();


            // ====================================================
            // MENU
            // ====================================================

            cout << "\n";
            cout << "Choose your action:"
                 << endl;


            cout << "1) Basic Attack"
                 << endl;


            cout << "2) Final Attack ";

            if (player.isFinalUnlocked())
                cout << "[READY]";
            else
                cout << "[LOCKED]";

            cout << endl;


            cout << "3) Heal ";

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
                cout << "\n";
                cout << "Invalid choice."
                     << endl;

                continue;
            }


            // ====================================================
            // GET HIDDEN REQUIRED MOVE
            // ====================================================

            char requiredMove =
                getRequiredMove(
                    player,
                    level,
                    step
                );


            // ====================================================
            // WRONG MOVE
            // ====================================================

            if (selectedMove != requiredMove)
            {
                wrongMove(
                    player,
                    enemy
                );

                return;
            }


            // ====================================================
            // BASIC ATTACK
            // ====================================================

            if (selectedMove == 'B')
            {
                int damage =
                    player.basicAttack();


                enemy.takeDamage(damage);


                cout << "\n";
                cout << "CORRECT MOVE!"
                     << endl;


                cout << enemy.getName()
                     << " takes "
                     << damage
                     << " damage."
                     << endl;
            }


            // ====================================================
            // FINAL ATTACK
            // ====================================================

            else if (selectedMove == 'F')
            {
                int damage =
                    player.finalAttack();


                if (damage > 0)
                {
                    enemy.takeDamage(damage);


                    cout << "\n";
                    cout << "CORRECT MOVE!"
                         << endl;


                    cout << "FINAL ATTACK!"
                         << endl;


                    cout << enemy.getName()
                         << " takes "
                         << damage
                         << " damage."
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
                    continue;
                }


                cout << "\n";
                cout << "CORRECT MOVE!"
                     << endl;
            }


            // ====================================================
            // CHECK ENEMY DEATH
            // ====================================================

            if (!enemy.isAlive())
            {
                cout << "\n";
                cout << "============================================================"
                     << endl;

                cout << "                    ENEMY DEFEATED!"
                     << endl;

                cout << "============================================================"
                     << endl;

                return;
            }


            // ====================================================
            // ENEMY NORMAL ATTACK
            //
            // A correct move does NOT kill the player.
            // ====================================================

            int enemyDamage =
                enemy.basicAttack();


            player.takeDamage(
                enemyDamage
            );


            cout << "-> "
                 << player.getName()
                 << " takes "
                 << enemyDamage
                 << " damage."
                 << endl;


            // ====================================================
            // CHECK PLAYER DEATH
            // ====================================================

            if (!player.isAlive())
            {
                cout << "\n";
                cout << "============================================================"
                     << endl;

                cout << "                       GAME OVER"
                     << endl;

                cout << "============================================================"
                     << endl;

                return;
            }


            // ====================================================
            // ADVANCE PATTERN
            //
            // ONLY CORRECT MOVES ADVANCE THE PATTERN.
            // ====================================================

            step++;

            turn++;
        }


        // ========================================================
        // LEVEL COMPLETED
        // ========================================================

        if (!enemy.isAlive())
        {
            cout << "\n";
            cout << "============================================================"
                 << endl;

            cout << "                    LEVEL CLEARED!"
                 << endl;

            cout << "============================================================"
                 << endl;
        }
    }


    // ============================================================
    // CHARACTER SELECTION
    // ============================================================
    unique_ptr<Player> choosePlayer()
    {
        cout << "\n";
        cout << "============================================================"
             << endl;

        cout << "                    CHOOSE YOUR CLASS"
             << endl;

        cout << "============================================================"
             << endl;


        // ========================================================
        // WARRIOR
        // ========================================================

        cout << "\n";
        cout << "1) WARRIOR"
             << endl;

        cout << "   HP: 700"
             << endl;

        cout << "   Basic Attack: 40"
             << endl;

        cout << "   Final Attack: 120"
             << endl;

        cout << "   Heal: 100"
             << endl;


        // ========================================================
        // MAGE
        // ========================================================

        cout << "\n";
        cout << "2) MAGE"
             << endl;

        cout << "   HP: 400"
             << endl;

        cout << "   Basic Attack: 55"
             << endl;

        cout << "   Final Attack: 220"
             << endl;

        cout << "   Heal: 100"
             << endl;


        cout << "\n";
        cout << "Choose your class: ";


        int choice =
            getChoice();


        cout << "\n";
        cout << "Enter your character name: ";


        string playerName;

        cin >> playerName;


        // ========================================================
        // CREATE WARRIOR
        // ========================================================

        if (choice == 1)
        {
            return unique_ptr<Player>(
                new Warrior(playerName)
            );
        }


        // ========================================================
        // CREATE MAGE
        // ========================================================

        else if (choice == 2)
        {
            return unique_ptr<Player>(
                new Mage(playerName)
            );
        }


        // ========================================================
        // INVALID
        // ========================================================

        else
        {
            cout << "\n";
            cout << "Invalid choice."
                 << endl;

            cout << "Warrior selected by default."
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
        cout << "============================================================"
             << endl;

        cout << "                  THE DARK ARENA"
             << endl;

        cout << "============================================================"
             << endl;


        cout << "\n";
        cout << "RULES"
             << endl;

        cout << "------------------------------------------------------------"
             << endl;

        cout << "1. Choose Warrior or Mage."
             << endl;

        cout << "2. Basic Attack is always available."
             << endl;

        cout << "3. Basic Attack unlocks Final Attack."
             << endl;

        cout << "4. Basic Attack unlocks Heal."
             << endl;

        cout << "5. Heal can only be used after Basic Attack."
             << endl;

        cout << "6. Final Attack can only be used after Basic Attack."
             << endl;

        cout << "7. There are NO clues."
             << endl;

        cout << "8. Every enemy has a fixed attack pattern."
             << endl;

        cout << "9. Warrior and Mage have DIFFERENT patterns."
             << endl;

        cout << "10. Wrong move = CRITICAL HIT."
             << endl;

        cout << "11. Critical Hit = INSTANT DEATH."
             << endl;

        cout << "12. You must follow the entire pattern to win."
             << endl;

        cout << "------------------------------------------------------------"
             << endl;


        // ========================================================
        // CHOOSE PLAYER
        // ========================================================

        unique_ptr<Player> player =
            choosePlayer();


        // ========================================================
        // CREATE LEVELS
        // ========================================================

        buildLevels(*player);


        int level = 1;


        // ========================================================
        // BATTLE EACH LEVEL
        // ========================================================

        for (size_t i = 0;
             i < enemies.size();
             i++)
        {
            battle(
                *player,
                *enemies[i],
                level
            );


            // ----------------------------------------------------
            // PLAYER DEAD
            // ----------------------------------------------------

            if (!player->isAlive())
            {
                return;
            }


            // ----------------------------------------------------
            // RECOVERY BETWEEN LEVELS
            // ----------------------------------------------------

            if (level < 4)
            {
                int recovery =
                    player->getMaxHealth() / 5;


                int oldHealth =
                    player->getHealth();


                player->heal(
                    recovery
                );


                int recovered =
                    player->getHealth()
                    - oldHealth;


                cout << "\n";
                cout << "You recover "
                     << recovered
                     << " HP before the next level."
                     << endl;
            }


            level++;
        }


        // ========================================================
        // FINAL VICTORY
        // ========================================================

        cout << "\n";
        cout << "============================================================"
             << endl;

        cout << "                       VICTORY!"
             << endl;

        cout << "============================================================"
             << endl;


        cout << "\n";
        cout << player->getName()
             << " has conquered the DARK ARENA!"
             << endl;


        cout << "\n";
        cout << "All four enemies have been defeated."
             << endl;


        cout << "\n";
        cout << "============================================================"
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