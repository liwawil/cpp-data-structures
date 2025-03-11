#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Task {
    string description;
    bool isHighPriority;
    Task* next;
};

class TaskManager {
private:
    Task* head;
public:
    TaskManager() : head(nullptr) {}
    ~TaskManager() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addTask(const string& desc, bool isHighPriority = false) {
        Task* newTask = new Task{desc, isHighPriority, nullptr};
        if (isHighPriority || !head) {
            newTask->next = head;
            head = newTask;
            cout << "Added high-priority task: " << desc << "\n";
        } else {
            Task* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newTask;
            cout << "Added task: " << desc << "\n";
        }
    }

    void completeTask() {
        if (!head) {
            cout << "No tasks to complete.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Completed task: " << temp->description << "\n";
        delete temp;
    }

    void viewTasks() {
        if (!head) {
            cout << "No tasks in the list.\n";
            return;
        }
        cout << "\nTask List:\n";
        Task* temp = head;
        int i = 1;
        while (temp) {
            cout << i++ << ". " << temp->description << (temp->isHighPriority ? " [High Priority]" : "") << "\n";
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream file("tasks.txt");
        if (!file) {
            cout << "Error saving tasks.\n";
            return;
        }
        Task* temp = head;
        while (temp) {
            file << temp->description << "\n" << temp->isHighPriority << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Tasks saved successfully!\n";
    }

    void loadFromFile() {
        ifstream file("tasks.txt");
        if (!file) return;
        string desc;
        bool isHighPriority;
        while (getline(file, desc) && file >> isHighPriority) {
            file.ignore();
            addTask(desc, isHighPriority);
        }
        file.close();
    }
};

int main() {
    TaskManager manager;
    manager.loadFromFile();
    int choice;
    do {
        cout << "\n=== Task Management System ===\n";
        cout << "1. Add Task\n";
        cout << "2. Add High-Priority Task\n";
        cout << "3. Complete Task\n";
        cout << "4. View Tasks\n";
        cout << "5. Save Tasks\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter task description: ";
                string desc;
                getline(cin, desc);
                manager.addTask(desc);
                break;
            }
            case 2: {
                cout << "Enter high-priority task description: ";
                string desc;
                getline(cin, desc);
                manager.addTask(desc, true);
                break;
            }
            case 3: manager.completeTask(); break;
            case 4: manager.viewTasks(); break;
            case 5: manager.saveToFile(); break;
            case 6: cout << "Exiting Task Manager.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}