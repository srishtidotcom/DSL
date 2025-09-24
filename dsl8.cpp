#include <iostream>
using namespace std;

// Node structure
struct Node {
    int orderID;
    Node* prev;
    Node* next;

    Node(int id) {
        orderID = id;
        prev = next = nullptr;
    }
};

// Deque class for Pizza Parlour
class PizzaDeque {
private:
    Node* front;
    Node* rear;

public:
    PizzaDeque() {
        front = rear = nullptr;
    }

    // Receive order at front
    void receiveFront(int id) {
        Node* temp = new Node(id);
        if (front == nullptr) { // empty queue
            front = rear = temp;
        } else {
            temp->next = front;
            front->prev = temp;
            front = temp;
        }
        cout << "Order " << id << " received at front.\n";
    }

    // Receive order at rear
    void receiveRear(int id) {
        Node* temp = new Node(id);
        if (rear == nullptr) { // empty queue
            front = rear = temp;
        } else {
            rear->next = temp;
            temp->prev = rear;
            rear = temp;
        }
        cout << "Order " << id << " received at rear.\n";
    }

    // Process order from front
    void processFront() {
        if (front == nullptr) {
            cout << "No orders to process!\n";
            return;
        }
        cout << "Processing order " << front->orderID << " from front.\n";
        Node* temp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
    }

    // Process order from rear
    void processRear() {
        if (rear == nullptr) {
            cout << "No orders to process!\n";
            return;
        }
        cout << "Processing order " << rear->orderID << " from rear.\n";
        Node* temp = rear;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
    }

    // Display all orders
    void displayOrders() {
        if (front == nullptr) {
            cout << "No orders in the queue.\n";
            return;
        }
        cout << "Current Orders: ";
        Node* temp = front;
        while (temp) {
            cout << temp->orderID << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

// Driver code
int main() {
    PizzaDeque parlour;
    int choice, id;

    do {
        cout << "\n--- Pizza Parlour Menu ---\n";
        cout << "1. Receive Order at Front\n";
        cout << "2. Receive Order at Rear\n";
        cout << "3. Process Order from Front\n";
        cout << "4. Process Order from Rear\n";
        cout << "5. Display Orders\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Order ID: ";
                cin >> id;
                parlour.receiveFront(id);
                break;
            case 2:
                cout << "Enter Order ID: ";
                cin >> id;
                parlour.receiveRear(id);
                break;
            case 3:
                parlour.processFront();
                break;
            case 4:
                parlour.processRear();
                break;
            case 5:
                parlour.displayOrders();
                break;
            case 0:
                cout << "Closing Pizza Parlour...\n";
                break;
            default:
                cout << "Invalid choice. Try again!\n";
        }
    } while (choice != 0);

    return 0;
}
