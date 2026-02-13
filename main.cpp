#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Structs
struct Upgrade {
    string name;
    double baseCost;
    double cost;
    double incomePerSecond;
    int owned;
};

struct Player {
    double money;
    double incomePerSecond;
};

// Functions
void displayMenu();
void displayUpgrades(Upgrade upgrades[], int size);
void buyUpgrade(Player& player, Upgrade& upgrade);
void generateIncome(Player* player);
void saveGame(Player player, Upgrade upgrades[], int size);
void loadGame(Player& player, Upgrade upgrades[], int size);
void newGame(Player& player, Upgrade upgrades[], int size);

int main() {

    Player player;
    player.money = 0;
    player.incomePerSecond = 0;

    const int SIZE = 3;

    Upgrade upgrades[SIZE] = {
        {"Intern", 50, 50, 1, 0},
        {"Developer", 200, 200, 5, 0},
        {"Server Farm", 1000, 1000, 25, 0}
    };

    int choice;
    bool running = true;

    loadGame(player, upgrades, SIZE);

    while (running) {

        generateIncome(&player);

        cout << "\nMoney: $" << player.money;
        cout << "\nIncome Per Tick: $" << player.incomePerSecond + 1 << endl;

        displayMenu();
        cin >> choice;

        if (choice == 1) {
            player.money += 1;
        }
        else if (choice == 2) {
            displayUpgrades(upgrades, SIZE);
            int upgradeChoice;
            cin >> upgradeChoice;

            if (upgradeChoice >= 1 && upgradeChoice <= SIZE) {
                buyUpgrade(player, upgrades[upgradeChoice - 1]);
            }
        }
        else if (choice == 3) {
            saveGame(player, upgrades, SIZE);
            cout << "Game Saved.\n";
        }
        else if (choice == 4) {
            running = false;
        }
        else if (choice == 5) {
            newGame(player, upgrades, SIZE);
        }
        else {
            cout << "Invalid choice.\n";
        }

        if (player.money >= 10000) {
            cout << "\nYou launched your Tech Company! You win!\n";
            running = false;
        }
    }

    return 0;
}

// Menu
void displayMenu() {
    cout << "\n1. Click for $1";
    cout << "\n2. Buy Upgrade";
    cout << "\n3. Save Game";
    cout << "\n4. Exit";
    cout << "\n5. New Game";
    cout << "\nChoice: ";
}

// Upgrade Display
void displayUpgrades(Upgrade upgrades[], int size) {
    cout << "\nAvailable Upgrades:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << upgrades[i].name
            << " | Cost: $" << upgrades[i].cost
            << " | Income: +" << upgrades[i].incomePerSecond
            << " | Owned: " << upgrades[i].owned << endl;
    }
}

// Upgrading
void buyUpgrade(Player& player, Upgrade& upgrade) {

    if (player.money >= upgrade.cost) {

        player.money -= upgrade.cost;
        player.incomePerSecond += upgrade.incomePerSecond;
        upgrade.owned++;

        // Increase Cost
        upgrade.cost *= 1.15;

        cout << "Purchased " << upgrade.name << "!\n";
    }
    else {
        cout << "Not enough money!\n";
    }
}
// Generate Income
void generateIncome(Player* player) {
    player->money += player->incomePerSecond;
}

// Same Game
void saveGame(Player player, Upgrade upgrades[], int size) {

    ofstream file("save.txt");

    file << player.money << endl;
    file << player.incomePerSecond << endl;

    for (int i = 0; i < size; i++) {
        file << upgrades[i].owned << endl;
        file << upgrades[i].cost << endl;
    }

    file.close();
}

// Load Game
void loadGame(Player& player, Upgrade upgrades[], int size) {

    ifstream file("save.txt");

    if (file.is_open()) {

        file >> player.money;
        file >> player.incomePerSecond;

        for (int i = 0; i < size; i++) {
            file >> upgrades[i].owned;
            file >> upgrades[i].cost;
        }

        file.close();
    }
}

// New Game
void newGame(Player& player, Upgrade upgrades[], int size) {

    player.money = 0;
    player.incomePerSecond = 0;

    for (int i = 0; i < size; i++) {
        upgrades[i].owned = 0;
        upgrades[i].cost = upgrades[i].baseCost;
    }

    ofstream file("save.txt");
    file.close();

    cout << "New game started!\n";
}
