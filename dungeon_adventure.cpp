#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Function prototypes
void gameStart();
void dungeonRoom();
void secretPassage();
void monsterEncounter();
void treasureRoom();
void wizardRoom();
void trapRoom();
void checkInventory();

// Inventory and health
bool hasKey = false;
bool hasSword = false;
bool hasPotion = false;
int health = 100;

int main() {
    cout << "Welcome to \"Escape the Dungeon\"\n";
    cout << "You find yourself trapped in a dark dungeon.\n";
    cout << "Your mission is to find a way out.\n\n";
    gameStart();
    return 0;
}

// Game Start Function
void gameStart() {
    int choice;
    cout << "You see three paths: one leading left, another right, and a staircase going down.\n";
    cout << "1. Go Left\n2. Go Right\n3. Go Downstairs\nChoose an option: ";
    cin >> choice;

    // Input validation
    if (cin.fail() || (choice < 1 || choice > 3)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Try again.\n";
        gameStart();
    }
    else if (choice == 1) {
        dungeonRoom();
    }
    else if (choice == 2) {
        secretPassage();
    }
    else if (choice == 3) {
        trapRoom();
    }
}

// Dungeon Room Function
void dungeonRoom() {
    int action;
    cout << "You enter a dark room and see a glint of metal. It's a sword!\n";
    cout << "1. Pick up the sword\n2. Ignore the sword and move forward\nChoose an action: ";
    cin >> action;

    // Input validation
    if (cin.fail() || (action != 1 && action != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Try again.\n";
        dungeonRoom();
    }
    else if (action == 1) {
        hasSword = true;
        cout << "You picked up the sword.\n";
        monsterEncounter();
    }
    else {
        monsterEncounter();
    }
}

// Secret Passage Function
void secretPassage() {
    cout << "You find a hidden key on the floor.\n";
    hasKey = true;
    wizardRoom();
}

// Trap Room Function
void trapRoom() {
    cout << "You step on a trap! Arrows fly from the walls.\n";
    health -= 30;
    cout << "You take damage. Health: " << health << "\n";
    
    if (health <= 0) {
        cout << "You have died. Game Over.\n";
    } else {
        cout << "You escape the trap room and find a potion.\n";
        hasPotion = true;
        cout << "You picked up a health potion.\n";
        monsterEncounter();
    }
}

// Monster Encounter Function
void monsterEncounter() {
    int decision;
    cout << "A monster appears!\n";
    cout << "1. Fight\n2. Run\nChoose your action: ";
    cin >> decision;

    switch (decision) {
        case 1:
            if (hasSword) {
                cout << "You defeat the monster with your sword!\n";
                treasureRoom();
            } else {
                health -= 50;
                cout << "You fight bare-handed and get hurt. Health: " << health << "\n";
                if (health <= 0) {
                    cout << "You have died. Game Over.\n";
                } else {
                    treasureRoom();
                }
            }
            break;
        case 2:
            cout << "You escape back to the start.\n";
            gameStart();
            break;
        default:
            cout << "Invalid choice. The monster attacks!\n";
            health -= 50;
            if (health <= 0) {
                cout << "You have died. Game Over.\n";
            } else {
                treasureRoom();
            }
            break;
    }
}

// Wizard Room Function
void wizardRoom() {
    cout << "A mysterious wizard blocks your path.\n";
    cout << "\"Answer my riddle and I shall let you pass.\"\n";
    cout << "\"I speak without a mouth and hear without ears. I have nobody, but I come alive with the wind. What am I?\"\n";
    cout << "Enter your answer: ";
    string answer;
    cin.ignore(); 
    getline(cin, answer);

    // Convert answer to lowercase
    for (auto &c : answer) c = tolower(c);

    if (answer == "echo") {
        cout << "\"Correct! You may pass.\"\n";
        treasureRoom();
    } else {
        cout << "\"Wrong! Face the consequences.\"\n";
        health -= 40;
        cout << "You are cursed. Health: " << health << "\n";
        if (health <= 0) {
            cout << "You have died. Game Over.\n";
        } else {
            treasureRoom();
        }
    }
}

// Treasure Room Function
void treasureRoom() {
    cout << "You find a locked door leading outside.\n";
    if (hasKey) {
        cout << "You use the key and escape! You Win!\n";
    } else {
        cout << "The door is locked. You are trapped. Game Over.\n";
    }
}

// Check Inventory Function
void checkInventory() {
    cout << "\n=== Inventory ===\n";
    cout << "Health: " << health << "\n";
    cout << "Sword: " << (hasSword ? "Yes" : "No") << "\n";
    cout << "Key: " << (hasKey ? "Yes" : "No") << "\n";
    cout << "Potion: " << (hasPotion ? "Yes" : "No") << "\n";
    cout << "=================\n";

    // Use potion if available
    if (hasPotion) {
        char usePotion;
        cout << "Do you want to use the health potion? (y/n): ";
        cin >> usePotion;
        if (usePotion == 'y' || usePotion == 'Y') {
            health += 50;
            hasPotion = false;
            cout << "You used the potion. Health: " << health << "\n";
        }
    }
}