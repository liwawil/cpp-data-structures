#include <iostream>
#include <vector>
#include <string>
using namespace std;

class GameMenuNavigator {
private:
    vector<string> menuStack;

public:
    GameMenuNavigator() {
        menuStack.push_back("Main Menu");
    }

    void enterSubmenu(string submenu) {
        menuStack.push_back(submenu);
        cout << "Entered: " << submenu << "\n";
    }

    void goBack() {
        if (menuStack.size() > 1) {
            string current = menuStack.back();
            menuStack.pop_back();
            cout << "Returned to: " << menuStack.back() << " (Exited: " << current << ")\n";
        } else {
            cout << "Already at Main Menu, cannot go back further!\n";
        }
    }

    void viewCurrentMenu() {
        cout << "Current Menu Stack (top to bottom):\n";
        for (int i = menuStack.size() -1; i >= 0; --i) {
            cout << " " << menuStack[i] << "\n";
        }
        cout << "---------\n";
    }
};

int main() {
    GameMenuNavigator navigator;
    int choice;
    string submenu;

    cout << "Welcome to the Game Menu Navigator!\n";
    do {
        cout << "\n1. Enter Submenu\n2. Go Back\n3. View Menu Stack\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter submenu name (e.g., Options, Audio): ";
                getline(cin, submenu);
                navigator.enterSubmenu(submenu);
                break;
            case 2:
                navigator.goBack();
                break;
            case 3:
                navigator.viewCurrentMenu();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}

