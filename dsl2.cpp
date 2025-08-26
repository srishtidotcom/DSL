// An E-commerce website has a range of products having Product id, name. manufacturer, price and quality rating out of 5. Write a C++/Java Program to display products as..
//1. In Increasing order of Product id (Use Bubble Sort) 2. In Increasing order of Product price (Use Selection Sort) 3. In Decreasing order of Product Quality Rating (Insertion Sort)

#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    int id;
    string name;
    string manufacturer;
    float price;
    int rating; // out of 5
};

void displayProducts(Product arr[], int n) {
    if (n == 0) {
        cout << "\nNo products available.\n";
        return;
    }
    cout << "\nProduct ID\tName\tManufacturer\tPrice\tRating\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i].id << "\t\t"
             << arr[i].name << "\t"
             << arr[i].manufacturer << "\t"
             << arr[i].price << "\t"
             << arr[i].rating << endl;
    }
}

// Bubble Sort (by ID ascending)
void bubbleSortByID(Product arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    cout << "\nProducts sorted by Product ID (Bubble Sort).\n";
}

// Selection Sort (by Price ascending)
void selectionSortByPrice(Product arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].price < arr[minIndex].price) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
    cout << "\nProducts sorted by Price (Selection Sort).\n";
}

// Insertion Sort (by Rating descending)
void insertionSortByRating(Product arr[], int n) {
    for (int i = 1; i < n; i++) {
        Product key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].rating < key.rating) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    cout << "\nProducts sorted by Rating (Insertion Sort).\n";
}

int main() {
    Product products[100]; // max 100 products
    int n = 0; // number of products
    int choice;

    do {
        cout << "\n--- E-Commerce Product Menu ---\n";
        cout << "1. Add Product Details\n";
        cout << "2. Display Product Details\n";
        cout << "3. Sort by Product ID (Bubble Sort)\n";
        cout << "4. Sort by Product Price (Selection Sort)\n";
        cout << "5. Sort by Product Rating (Insertion Sort)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\nEnter number of products to add: ";
            int count; cin >> count;
            for (int i = 0; i < count; i++) {
                cout << "\nEnter details of product " << (n + 1) << ":\n";
                cout << "Product ID: "; cin >> products[n].id;
                cout << "Name: "; cin >> products[n].name;
                cout << "Manufacturer: "; cin >> products[n].manufacturer;
                cout << "Price: "; cin >> products[n].price;
                cout << "Quality Rating (1-5): "; cin >> products[n].rating;
                n++;
            }
            break;
        }
        case 2:
            displayProducts(products, n);
            break;
        case 3:
            bubbleSortByID(products, n);
            displayProducts(products, n);
            break;
        case 4:
            selectionSortByPrice(products, n);
            displayProducts(products, n);
            break;
        case 5:
            insertionSortByRating(products, n);
            displayProducts(products, n);
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
