#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Transition {
    string condition; 
    string targetState;
    Transition* next;
};

struct State {
    string name;
    Transition* transitions;
    State* prev;
    State* next;
};

struct HistoryNode {
    string stateName;
    HistoryNode* next;
};

class BehavioralStateMachine {
private:
    State* head;
    State* tail;
    State* current;
    HistoryNode* history;

    State* findState(const string& name) {
        State* temp = head;
        while (temp && temp->name != name) temp = temp->next;
        return temp;
    }

public:
    BehavioralStateMachine() : head(nullptr), tail(nullptr), current(nullptr), history(nullptr) {}
    ~BehavioralStateMachine() {
        while (head) {
            State* temp = head;
            head = head->next;
            while (temp->transitions) {
                Transition* t = temp->transitions;
                temp->transitions = t->next;
                delete t;
            }
            delete temp;
        }
        while (history) {
            HistoryNode* temp = history;
            history = history->next;
            delete temp;
        }
    }

    void addState(const string& name) {
        if (findState(name)) {
            cout << "State '" << name << "' already exists.\n";
            return;
        }
        State* newState = new State{name, nullptr, nullptr, nullptr};
        if (!head) {
            head = tail = current = newState;
        } else {
            newState->prev = tail;
            tail->next = newState;
            tail = newState;
        }
        cout << "Added state: '" << name << "'\n";
    }

    void addTransition(const string& fromState, const string& condition, const string& toState) {
        State* from = findState(fromState);
        State* to = findState(toState);
        if (!from || !to) {
            cout << "One or both states not found.\n";
            return;
        }
        Transition* newTransition = new Transition{condition, toState, nullptr};
        if (!from->transitions) {
            from->transitions = newTransition;
        } else {
            Transition* t = from->transitions;
            while (t->next) t = t->next;
            t->next = newTransition;
        }
        cout << "Added transition from '" << fromState << "' to '" << toState << "' on '" << condition << "'\n";
    }

    void setCurrentState(const string& name) {
        State* target = findState(name);
        if (!target) {
            cout << "State '" << name << "' not found.\n";
            return;
        }
        current = target;
        // Add to history
        HistoryNode* newHistory = new HistoryNode{name, history};
        history = newHistory;
        cout << "Current state set to: '" << name << "'\n";
    }

    void simulate(const string& condition) {
        if (!current) {
            cout << "No current state set.\n";
            return;
        }
        Transition* t = current->transitions;
        while (t && t->condition != condition) t = t->next;
        if (t) {
            State* nextState = findState(t->targetState);
            if (nextState) {
                current = nextState;
                HistoryNode* newHistory = new HistoryNode{t->targetState, history};
                history = newHistory;
                cout << "Transitioned to '" << t->targetState << "' due to '" << condition << "'\n";
            }
        } else {
            cout << "No transition for condition '" << condition << "'\n";
        }
    }

    void viewStates() {
        if (!head) {
            cout << "No states defined.\n";
            return;
        }
        cout << "\nStates and Transitions:\n";
        State* temp = head;
        while (temp) {
            cout << "- " << temp->name << (temp == current ? " [Current]" : "") << ":\n";
            Transition* t = temp->transitions;
            while (t) {
                cout << " -> " << t->targetState << " on '" << t->condition << "'\n";
                t = t->next;
            }
            temp = temp->next;
        }
    }

    void viewHistory() {
        if (!history) {
            cout << "No state history.\n";
            return;
        }
        cout << "\nState History (most recent first):\n";
        HistoryNode* temp = history;
        while (temp) {
            cout << "- " << temp->stateName << "\n";
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream file("states.txt");
        if (!file) {
            cout << "Error saving states.\n";
            return;
        }
        State* temp = head;
        while (temp) {
            file << "State\n" << temp->name << "\n";
            Transition* t = temp->transitions;
            while (t) {
                file << "TRANSITION\n" << t->condition << "\n" << t->targetState << "\n";
                t = t->next;
            }
            temp = temp->next;
        }
        file.close();
        cout << "State machine saved to states.txt!\n";
    }

    void loadFromFile() {
        ifstream file("states.txt");
        if (!file) return;
        string line, stateName, condition, targetState;
        while (getline(file, line)) {
            if (line == "STATE") {
                getline(file, stateName);
                addState(stateName);
            } else if (line == "TRANSITION") {
                getline(file, condition);
                getline(file, targetState);
                addTransition(stateName, condition, targetState);
            }
        }
        file.close();
        if (head && !current) setCurrentState(head->name);
    }
};

int main() {
    BehavioralStateMachine sm;
    sm.loadFromFile();
    int choice;
    do {
        cout << "\n=== Behavioral State Machine ===\n";
        cout << "1. Add State\n2. Add Transition\n3. Set Current State\n4. Simulate\n";
        cout << "5. View States\n6. View History\n7. Save\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter state name: ";
                string name;
                getline(cin, name);
                sm.addState(name);
                break;
            }
            case 2: {
                cout << "Enter from state: ";
                string from;
                getline(cin, from);
                cout << "Enter condition: ";
                string cond;
                getline(cin, cond);
                cout << "Enter target state: ";
                string to;
                getline(cin, to);
                sm.addTransition(from, cond, to);
                break;
            }
            case 3: {
                cout << "Enter state name: ";
                string name;
                getline(cin, name);
                sm.setCurrentState(name);
                break;
            }
            case 4: {
                cout << "Enter condition: ";
                string cond;
                getline(cin, cond);
                sm.simulate(cond);
                break;
            }
            case 5: sm.viewStates(); break;
            case 6: sm.viewHistory(); break;
            case 7: sm.saveToFile(); break;
            case 8: cout << "Exiting state machine.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 8);
    return 0;
}