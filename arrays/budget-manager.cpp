#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Expense {
    string category;
    double amount;
    double budgetLimit;
};

struct User {
    string name;
    vector<Expense> expenses;
};

void displayMainMenu();
int getUserChoice();
void addUser(vector<User>& users);
void selectUser(vector<User>& users);
void addExpense(User& user);
void setBudgetLimit(User& user);
void viewSummary(const User& user);
void saveData(const vector<User>& users);
void loadData(vector<User>& users);

int main() {
    vector<User> users;
    loadData(users);

    int choice;
    do {
        displayMainMenu();
        choice = getUserChoice();
        switch (choice) {
            case 1: addUser(users); break;
            case 2: selectUser(users); break;
            case 3: saveData(users); cout << "Data saved!\n"; break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 4);
    
    saveData(users);
    return 0;
}

void displayMainMenu() {
    cout << "\n=== Personal Budget Manager ===\n";
    cout << "1. Add User\n";
    cout << "2. Select User\n";
    cout << "3. Save Data\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
}

int getUserChoice() {
    int choice;
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore();
    return choice;
}

void addUser(vector<User>& users) {
    cout << "Enter new user name: ";
    string name;
    getline(cin, name);
    users.push_back({name, {}});
    cout << "User " << name << " added!\n";
}

void selectUser(vector<User>& users) {
    if (users.empty()) {
        cout << "No users yet. Add a user first.\n";
        return;
    }
    cout << "Select User:\n";
    for (size_t i = 0; i < users.size(); i++) {
        cout << i + 1 << ". " << users[i].name << "\n";
    }
    cout << "Enter user number: ";
    int userIdx = getUserChoice();
    if (userIdx < 1 || userIdx > static_cast<int>(users.size())) {
        cout << "Invalid user.\n";
        return;
    }

    User& user = users[userIdx - 1];
    int subChoice;
    do {
        cout << "\nUser: " << user.name << "\n";
        cout << "1. Add Expense\n";
        cout << "2. Set Budget Limit\n";
        cout << "3. View Summary\n";
        cout << "4. Back\n";
        cout << "Enter choice: ";
        subChoice = getUserChoice();
        switch (subChoice) {
            case 1: addExpense(user); break;
            case 2: setBudgetLimit(user); break;
            case 3: viewSummary(user); break;
            case 4: break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (subChoice != 4);
}

void addExpense(User& user) {
    cout << "Add Expense for " << user.name << "\n";
    cout << "Category: ";
    string category;
    getline(cin, category);
    cout << "Amount: $";
    double amount;
    cin >> amount;
    if (cin.fail() || amount < 0) {
        cout << "Invalid or negative amount.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore();
    user.expenses.push_back({category, amount, 0.0});
    cout << "Expense added!\n";
}

void setBudgetLimit(User& user) {
    if (user.expenses.empty()) {
        cout << "No expenses to set limits for.\n";
        return;
    }
    cout << "Set Budget Limit for " << user.name << "\n";
    for (size_t i = 0; i < user.expenses.size(); i++) {
        cout << i + 1 << ". " << user.expenses[i].category << " ($" << user.expenses[i].amount << ")\n";
    }
    cout << "Select category number: ";
    int idx = getUserChoice();
    if (idx < 1 || idx > static_cast<int>(user.expenses.size())) {
        cout << "Invalid category.\n";
        return;
    }
    cout << "Enter budget limit: $";
    double limit;
    cin >> limit;
    if (cin.fail() || limit < 0) {
        cout << "Invalid limit.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore();
    user.expenses[idx -1].budgetLimit = limit;
    cout << "Budget limit set!\n";
}

void viewSummary(const User& user) {
    cout << "\nSummary for " << user.name << "\n";
    if (user.expenses.empty()) {
        cout << "No expenses.\n";
        return;
    }
    double total = 0;
    for (const auto& exp : user.expenses) {
        cout << exp.category << ": $" << fixed << setprecision(2) << exp.amount;
        if (exp.budgetLimit > 0 && exp.amount > exp.budgetLimit) {
            cout << " [OVER BUDGET: $" << exp.budgetLimit << "limit]";
        }
        cout << "\n";
        total += exp.amount;
    }
    cout << "Total: $" << total << "\n";
}

void saveData(const vector<User>& users) {
    ofstream file("budget_data.txt");
    if (!file) {
        cout << "Error saving data.\n";
        return;
    }
    file << users.size() << "\n";
    for (const auto& user : users) {
        file << user.name << "\n" << user.expenses.size() << "\n";
        for (const auto& exp : user.expenses) {
            file << exp.category << "\n" << exp.amount << "\n" << exp.budgetLimit << "\n";
        }
    }
    file.close();
}

void loadData(vector<User>& users) {
    ifstream file("budget_data.txt");
    if (!file) return;
    int userCount;
    file >> userCount; file.ignore();
    for (int i = 0; i < userCount; i++) {
        string name;
        getline(file, name);
        int expCount;
        file >> expCount; file.ignore();
        User user = {name, {}};
        for (int j = 0; j < expCount; j++) {
            string category;
            double amount, limit;
            getline(file, category);
            file >> amount >> limit; file.ignore();
            user.expenses.push_back({category, amount, limit});
        }
        users.push_back(user);
    }
    file.close();
}