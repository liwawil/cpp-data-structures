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

void selectWarehouse(Warehouse* warehouses, int warehouseCount) {
    if (warehouseCount == 0) {
        cout << "No warehouses yet. Add one first.\n";
        return;
    }
    cout << "Select Warehouse:\n";
    for (int i = 0; i < warehouseCount; i++) {
        cout << i + 1 << ". " << warehouses[i].name << "\n";
    }
    cout << "Enter warehouse number: ";
    int idx = getChoice();
    if (idx < 1 || idx > warehouseCount) {
        cout << "Invalid warehouse.\n";
        return;
    }

    Warehouse& warehouse = warehouses[idx - 1];
    int subChoice;
    do {
        cout << "\nWarehouse: " << warehouse.name << "\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Remove Product\n";
        cout << "4. View Analytics\n";
        cout << "5. Back\n";
        cout << "Enter choice: ";
        subChoice = getChoice();
        switch (subChoice) {
            case 1: addProduct(warehouse); break;
            case 2: updateProduct(warehouse); break;
            case 3: removeProduct(warehouse); break;
            case 4: viewAnalytics(warehouse); break;
            case 5: break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (subChoice != 5);
}

void addProduct(Warehouse& warehouse) {
    if (warehouse.size >= warehouse.capacity) resizeWarehouse(warehouse);
    cout << "Enter product name: ";
    string name;
    getline(cin, name);
    cout << "Enter category: ";
    string category;
    getline(cin, category);
    cout << "Enter quantity: ";
    int quantity;
    cin >> quantity;
    cout << "Enter price: $";
    double price;
    cin >> price;
    if (cin.fail() || quantity < 0 || price < 0) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore();
    warehouse.products[warehouse.size++] = {name, category, quantity, price};
    cout << "Product addded!\n";
}

void updateProduct(Warehouse& warehouse) {
    if (warehouse.size == 0) {
        cout << "No products to update.\n";
        return;
    }
    cout << "Enter product name to update: ";
    string name;
    getline(cin, name);
    quickSort(warehouse.products, 0, warehouse.size - 1);
    int idx = binarySearch(warehouse.products, warehouse.size, name);
    if (idx == -1) {
        cout << "Product not found.\n";
        return;
    }
    cout << "Current: " << warehouse.products[idx].quantity << " units, $" << warehouse.products[idx].price << "\n";
    cout << "New quantity: ";
    cin >> warehouse.products[idx].quantity;
    cout << "New price: $";
    cin >> warehouse.products[idx].price;
    if (cin.fail() || warehouse.products[idx].quantity < 0 || warehouse.products[idx].price < 0) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore();
    cout << "Product updated!\n";
} 

void removeProduct(Warehouse& warehouse) {
    if (warehouse.size == 0) {
        cout << "No products to remove.\n";
        return;
    }
    cout << "Enter product name to remove: ";
    string name;
    getline(cin, name);
    int idx = binarySearch(warehouse.products, warehouse.size, name);
    if (idx == -1) {
        cout << "Product not found.\n";
        return;
    }
    for (int i = idx; i < warehouse.size - 1; i++) {
        warehouse.products[i] = warehouse.products[i + 1];
    }
    warehouse.size--;
    cout << "Product removed!\n";
}

void viewAnalytics(const Warehouse& warehouse) {
    if (warehouse.size == 0) {
        cout << "No products in " << warehouse.name << ".\n";
        return;
    }
    double totalValue = 0;
    cout << "\nInventory for " << warehouse.name << ":\n";
    for (int i = 0; i < warehouse.size; i++) {
        cout << i + 1 << ". " << warehouse.products[i].name << " (" << warehouse.products[i].category
            << "): " << warehouse.products[i].quantity << " units, $" << warehouse.products[i].price << "\n";
        totalValue += warehouse.products[i].quantity * warehouse.products[i].price;
    }
    cout << "Total Inventory Value: $" << fixed << setprecision(2) << totalValue << "\n";
    cout << "Low Stock Items (<10 units):\n";
    for (int i = 0; i < warehouse.size; i++) {
        if (warehouse.products[i].quantity < 10) {
            cout << " - " << warehouse.products[i].name << ": " << warehouse.products[i].quantity << " units\n";
        }
    }
}

void resizeWarehouse(Warehouse& warehouse) {
    int newCapacity = warehouse.capacity * 2;
    Product* newProducts = new Product[newCapacity];
    for (int i = 0; i < warehouse.size; i++) {
        newProducts[i] = warehouse.products[i];
    }
    delete[] warehouse.products;
    warehouse.products = newProducts;
    warehouse.capacity = newCapacity;
    cout << "Product array resized to " << newCapacity << ".\n";
}

// Quicksort implementation for products by name
int partition(Product* arr, int low, int high) {
    string pivot = arr[high].name;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].name <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Product* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int binarySearch(const Product* arr, int size, const string& name) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].name == name) return mid;
        if (arr[mid].name < name) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void saveData(const Warehouse* warehouses, int warehouseCount) {
    ofstream file("inventory_data.txt");
    if (!file) {
        cout << "Error saving data.\n";
        return;
    }
    file << warehouseCount << "\n";
    for (int i = 0; i < warehouseCount; i++) {
        file << warehouses[i].name << "\n" << warehouses[i].size << "\n";
        for (int j = 0; j < warehouses[i].size; j++) {
            file << warehouses[i].products[j].name << "\n" << warehouses[i].products[j].category << "\n"
                << warehouses[i].products[j].quantity << "\n" << warehouses[i].products[j].price << "\n";
        }
    }
    file.close();
}

void loadData(Warehouse*& warehouses, int& warehouseCount, int& warehouseCapacity) {
    ifstream file("inventory_data.txt");
    if (!file) return;
    file >> warehouseCount; file.ignore();
    if (warehouseCount > warehouseCapacity) {
        delete[] warehouses;
        warehouseCapacity = warehouseCount * 2;
        warehouses = new Warehouse[warehouseCapacity];
    }
    for (int i = 0; i < warehouseCount; i++) {
        string name;
        int size;
        getline(file, name);
        file >> size; file.ignore();
        warehouses[i] = {name, new Product[5], 0, 5};
        if (size > 5) {
            delete[] warehouses[i].products;
            warehouses[i].products = new Product[size * 2];
            warehouses[i].capacity = size * 2;
        }
        for (int j = 0; j < size; j++) {
            getline(file, warehouses[i].products[j].name);
            getline(file, warehouses[i].products[j].category);
            file >> warehouses[i].products[j].quantity >> warehouses[i].products[j].price;
            file.ignore();
            warehouses[i].size++;
        }
    }
    file.close();
}
