#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Product {
    string name;
    string category;
    int quantity;
    double price;
};

struct Warehouse {
    string name;
    Product* products;
    int size;
    int capacity;
};

void displayMenu();
int getChoice();
void addWarehouse(Warehouse*& warehouses, int& warehouseCount, int& warehouseCapacity);
void selectWarehouse(Warehouse* warehouses, int warehouseCount);
void addProduct(Warehouse& warehouse);
void updateProduct(Warehouse& warehouse);
void removeProduct(Warehouse& warehouse);
void viewAnalytics(const Warehouse& warehouse);
void resizeWarehouse(Warehouse& warehouse);
void quickSort(Product* arr, int low, int high);
int partition(Product* arr, int low, int high);
int binarySearch(const Product* arr, int size, const string& name);
void saveData(const Warehouse* warehouses, int warehouseCount);
void loadData(Warehouse*& warehouses, int& warehouseCount, int& warehouseCapacity);

int main() {
    int warehouseCount = 0;
    int warehouseCapacity = 2;
    Warehouse* warehouses = new Warehouse[warehouseCapacity];
    loadData(warehouses, warehouseCount, warehouseCapacity);

    int choice;
    do {
        displayMenu();
        choice = getChoice();
        switch (choice) {
            case 1: addWarehouse(warehouses, warehouseCount, warehouseCapacity); break;
            case 2: selectWarehouse(warehouses, warehouseCount); break;
            case 3: saveData(warehouses, warehouseCount); cout << "Data saved!\n";
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 4);

    saveData(warehouses, warehouseCount);
    for (int i = 0; i < warehouseCount; i++) {
        delete[] warehouses[i].products;
    }
    delete[] warehouses;
    return 0;
}

void displayMenu() {
    cout << "\n=== Dynamic Inventory Management System ===\n";
    cout << "1. Add Warehouse\n";
    cout << "2. Select Warehouse\n";
    cout << "3. Save Data\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
}

int getChoice() {
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

void addWarehouse(Warehouse*& warehouses, int& warehouseCount, int& warehouseCapacity) {
    if (warehouseCount >= warehouseCapacity) {
        int newCapacity = warehouseCapacity * 2;
        Warehouse* newWarehouses = new Warehouse[newCapacity];
        for (int i = 0; i < warehouseCount; i++) {
            newWarehouses[i] = warehouses[i];
        }
        delete[] warehouses;
        warehouses = newWarehouses;
        warehouseCapacity = newCapacity;
        cout << "Warehouse array resized to " << warehouseCapacity << ".\n";
    }
    cout << "Enter warehouse name: ";
    string name;
    getline(cin, name);
    warehouses[warehouseCount] = {name, new Product[5], 0, 5};
    warehouseCount++;
    cout << "Warehouse " << name << " added!\n";
}