#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Position {
    int x, y;
};

struct Action {
    string name;
    int noiseLevel;
    Position target;
};

class StealthMissionPlanner {
private:
    vector<Action> playerStack;
    vector<Action> guardStack;
    const int maxActions = 5;
    Position playerPos = {0, 0};
    Position guardPos = {5, 5};
    int noiseThreshold = 5;
    bool guardAlerted = false;

    // Generate random guard patrol action
    Action randomPatrolAction() {
        string actions[] = {"Patrol North", "Patrol South", "Patrol East", "Patrol West"};
        Position newPos = guardPos;
        int index = rand() % 3;
        if (actions[index] == "Patrol North") newPos.y++;
        else if (actions[index] == "Patrol South") newPos.y--;
        else if (actions[index] == "Patrol East") newPos.x++;
        else newPos.x--;
        return {actions[index], 1, newPos};
    }

    int distanceToGuard() {
        return abs(playerPos.x - guardPos.x) + abs(playerPos.y - guardPos.y);
    }

    void guardInvestigate() {
        Action investigate = {"Investigate Noise", 0, playerPos};
        guardStack.push_back(investigate);
        guardPos = playerPos; 
        cout << "Guard moves to (" << guardPos.x << ", " << guardPos.y << ") to investigate!\n";
    }

public:
    StealthMissionPlanner() {
        srand(time(0));
        guardStack.push_back({"Stand Guard", 0, guardPos});
    }

    void planAction(string name, int noiseLevel, int x, int y) {
        if (playerStack.size() < maxActions) {
            playerStack.push_back({name, noiseLevel, {x, y}});
            cout << "Planned: " << name << " to (" << x << ", " << y << ") (Noise: " << noiseLevel << ")\n";
        } else {
            cout << "Plan full! Execute some actions first.\n";
        }
    }

    void executeNextAction() {
        if (playerStack.empty()) {
            cout << "No actions to execute!\n";
            return;
        }

        Action next = playerStack.back();
        playerStack.pop_back();
        playerPos = next.target;
        cout << "Player: " << next.name << " to (" << playerPos.x << ", " << playerPos.y << ") (Noise: " << next.noiseLevel << ")\n";

        // Noise detection
        if (next.noiseLevel >= noiseThreshold && distanceToGuard() <= 5 && !guardAlerted) {
            guardAlerted = true;
            cout << "Guard hears noise! Alerted!\n";
            guardInvestigate();
        } else if (!guardAlerted) {
            guardStack.push_back(randomPatrolAction());
            guardPos = guardStack.back().target;
            cout << "Guard: " << guardStack.back().name << " to (" << guardPos.x << ", " << guardPos.y << ")\n";
        }
    }

    void guardPatrolStep() {
        if (guardAlerted) {
            if (!guardStack.empty()) {
                Action current = guardStack.back();
                guardStack.pop_back();
                guardPos = current.target;
                cout << "Guard: " << current.name << " at (" << guardPos.x << ", " << guardPos.y << ")\n";
                if (distanceToGuard() == 0) {
                    cout << "Guard caught you! Mission failed!\n";
                } else if (guardStack.empty()) {
                    cout << "Guard lost track-resuming patrol.\n";
                    guardAlerted = false;
                    guardStack.push_back({"Stand Guard", 0, {5, 5}});
                    guardPos = {5, 5};
                }
            }
        } else {
            guardStack.push_back(randomPatrolAction());
            guardPos = guardStack.back().target;
            cout << "Guard: " << guardStack.back().name << " to (" << guardPos.x << ", " << guardPos.y << ")\n";
        }
    }

    void viewStatus() {
        cout << "Player Position: (" << playerPos.x << ", " << playerPos.y << ")\n";
        cout << "Guard Position: (" << guardPos.x << ", " << guardPos.y << ")\n";
        cout << "Player Plan (next first):\n";
        if (playerStack.empty()) cout << "  [Empty]\n";
        else {
            for (int i = playerStack.size() - 1; i >= 0; --i) {
                cout << "  " << playerStack[i].name << " to (" << playerStack[i].target.x << ", " << playerStack[i].target.y << ") (Noise: " << playerStack[i].noiseLevel << ")\n";
            }
        }
        cout << "Guard Patrol (current first):\n";
        if (guardStack.empty()) cout << "  [Empty]\n";
        else {
            for (int i = guardStack.size() - 1; i >= 0; --i) {
                cout << "  " << guardStack[i].name << " at (" << guardStack[i].target.x << ", " << guardStack[i].target.y << ")\n";
            }
        }
        cout << "Guard Alerted: " << (guardAlerted ? "Yes" : "No") << "\n";
        cout << "Distance to Guard: " << distanceToGuard() << "\n";
        cout << "----------\n";
    }
};

int main() {
    StealthMissionPlanner game;
    int choice, x, y;


    cout << "Stealth Mission Planner with Dynamic Guard\n";
    do {
        cout << "\n1. Plan Move Quietly (Noise: 2)\n2. Plan Throw Rock (Noise: 6)\n3. Plan Hide (Noise: 1)\n";
        cout << "4. Execute Next Action\n5. Guard Patrol Step\n6. View Status\n7. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Target X Y (e.g., 1 2): ";
                cin >> x >> y; cin.ignore();
                game.planAction("Move Quietly", 2, x, y);
                break;
            case 2:
                cout << "Target X Y (e.g., 3 4): ";
                cin >> x >> y; cin.ignore();
                game.planAction("Throw Rock", 6, x, y);
                break;
            case 3:
                cout << "Target X Y (e.g., 0 1): ";
                cin >> x >> y; cin.ignore();
                game.planAction("Hide", 1, x, y);
                break;
            case 4: game.executeNextAction(); break;
            case 5: game.guardPatrolStep(); break;
            case 6: game.viewStatus(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}