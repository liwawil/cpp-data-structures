#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Event {
    int timeStamp; // Time in seconds when event occurs
    string description; // What happens
    Event* next; // Pointer to next event;
};

class GameEventScheduler {
private:
    Event* head;
    int currentTime; 

public:
    GameEventScheduler() : head(nullptr), currentTime(0) {}
    ~GameEventScheduler() {
        while (head) {
            Event* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addEvent(int time, const string& desc) {
        Event* newEvent = new Event{time, desc, nullptr};
        if (!head || head->timeStamp >= time) { // Insert at head
            newEvent->next = head;
            head = newEvent;
        } else { // Insert in sorted position 
            Event* current = head;
            while (current->next && current->next->timeStamp < time) {
                current = current->next;
            }
            newEvent->next = current->next;
            current->next = newEvent;
        }
        cout << "Added event: '" << desc << "' at " << time << "s\n";
    }

    // Remove an event by description (first match)
    void removeEvent(const string& desc) {
        if (!head) {
            cout << "No events to remove.\n";
            return;
        }
        if (head->description == desc) {
            Event* temp = head;
            head = head->next;
            delete temp;
            cout << "Removed event: '" << desc << "'\n";
            return;
        }
        Event* current = head;
        while (current->next && current->next->description != desc) {
            current = current->next;
        }
        if (current->next) {
            Event* temp = current->next;
            current->next = temp->next;
            delete temp;
            cout << "Removed event: '" << desc << "'\n";
        } else {
            cout << "Event '" << desc << "' not found.\n";
        }
    }

    // List events up to a specified time
    void listEvents(int maxTime) {
        if (!head) {
            cout << "No events scheduled.\n";
            return;
        }
        cout << "\nEvents up to " << maxTime << "s:\n";
        Event* current = head;
        while (current && current->timeStamp <= maxTime) {
            cout << "- " << current->timeStamp << "s: " << current->description << "\n";
            current = current->next;
        }
    }

    void advanceTime(int newTime) {
        if (newTime < currentTime) {
            cout << "Cannot move time backward.\n";
            return;
        }
        cout << "\nAdvancing time to " << newTime << "s:\n";
        Event* current = head;
        while (current && current->timeStamp <= newTime) {
            cout << "Time " << current->timeStamp << "s: " << current->description << " triggered.\n";
            Event* temp = current;
            current = current->next;
            head = current; // Remove triggered event
            delete temp;
        }
        currentTime = newTime;
    }

    void saveToFile() {
        ofstream file("events.txt");
        if (!file) {
            cout << "Error saving events.\n";
            return;
        }
        Event* current = head;
        while (current) {
            file << current->timeStamp << "\n" << current->description << "\n";
            current = current->next;
        }
        file.close();
        cout << "Events saved to events.txt!\n";
    }

    void loadFromFile() {
        ifstream file("events.txt");
        if (!file) return; // Silent fail if no file
        int time;
        string desc;
        while (file >> time) {
            file.ignore();
            getline(file, desc);
            addEvent(time, desc);
        }
        file.close();
    }
};

int main() {
    GameEventScheduler scheduler;
    scheduler.loadFromFile();
    int choice;
    do {
        cout << "\n=== Game Event Scheduler ===\n";
        cout << "1. Add Event\n2. Remove Event\n3. List Events up To Time\n";
        cout << "4. Advance Time\n5. Save Events\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter time stamp (seconds): ";
                int time;
                cin >> time;
                cin.ignore();
                cout << "Enter event description: ";
                string desc;
                getline(cin, desc);
                scheduler.addEvent(time, desc);
                break;
            }
            case 2: {
                cout << "Enter event description to remove: ";
                string desc;
                getline(cin, desc);
                scheduler.removeEvent(desc);
                break;
            }
            case 3: {
                cout << "Enter max time to list events up to (seconds): ";
                int maxTime;
                cin >> maxTime;
                scheduler.listEvents(maxTime);
                break;
            }
            case 4: {
                cout << "Enter new game time (seconds): ";
                int newTime;
                cin >> newTime;
                scheduler.advanceTime(newTime);
                break;
            }
            case 5: scheduler.saveToFile(); break;
            case 6: cout << "Exiting scheduler.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}