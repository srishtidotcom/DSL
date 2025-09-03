#include <iostream>
#include <string>
using namespace std;

// Node structure
struct Node {
    int music_id;
    string title;
    float time_duration;
    Node* prev;
    Node* next;

    Node(int id, string t, float d) {
        music_id = id;
        title = t;
        time_duration = d;
        prev = next = nullptr;
    }
};

class Playlist {
private:
    Node* head;
    int size;

public:
    Playlist() {
        head = nullptr;
        size = 0;
    }

    // Insert at any position
    void insertAt(int pos, int id, string title, float duration) {
        if (pos < 1 || pos > size + 1) {
            cout << "Invalid position!\n";
            return;
        }

        Node* newNode = new Node(id, title, duration);

        if (head == nullptr) { // empty list
            head = newNode;
            head->next = head;
            head->prev = head;
        } 
        else if (pos == 1) { // insert at head
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        } 
        else {
            Node* temp = head;
            for (int i = 1; i < pos - 1; i++) temp = temp->next;

            Node* nextNode = temp->next;
            newNode->next = nextNode;
            newNode->prev = temp;
            temp->next = newNode;
            nextNode->prev = newNode;
        }
        size++;
        cout << "Inserted successfully!\n";
    }

    // Delete at position
    void deleteAt(int pos) {
        if (head == nullptr || pos < 1 || pos > size) {
            cout << "Invalid position!\n";
            return;
        }

        Node* temp = head;

        if (size == 1) { // only one node
            delete head;
            head = nullptr;
        } 
        else if (pos == 1) { // delete head
            Node* tail = head->prev;
            temp = head;
            head = head->next;
            tail->next = head;
            head->prev = tail;
            delete temp;
        } 
        else {
            for (int i = 1; i < pos; i++) temp = temp->next;

            Node* prevNode = temp->prev;
            Node* nextNode = temp->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            delete temp;
        }
        size--;
        cout << "Deleted successfully!\n";
    }

    // Sort playlist by chosen field
    void sortPlaylist(int choice) {
        if (!head || head->next == head) return; // empty or single node

        for (Node* i = head; i->next != head; i = i->next) {
            for (Node* j = i->next; j != head; j = j->next) {
                bool swapNeeded = false;

                if (choice == 1 && i->music_id > j->music_id) swapNeeded = true;
                else if (choice == 2 && i->title > j->title) swapNeeded = true;
                else if (choice == 3 && i->time_duration > j->time_duration) swapNeeded = true;

                if (swapNeeded) {
                    swap(i->music_id, j->music_id);
                    swap(i->title, j->title);
                    swap(i->time_duration, j->time_duration);
                }
            }
        }
        cout << "Sorted successfully!\n";
    }

    // Display playlist
    void display() {
        if (!head) {
            cout << "Playlist is empty!\n";
            return;
        }
        Node* temp = head;
        int index = 1;
        do {
            cout << index++ << ". [ID: " << temp->music_id
                 << ", Title: " << temp->title
                 << ", Duration: " << temp->time_duration << " min]\n";
            temp = temp->next;
        } while (temp != head);
    }

    // Play continuously in loop
    void playLoop(int n) {
        if (!head) {
            cout << "Playlist is empty!\n";
            return;
        }
        cout << "Playing playlist in loop (" << n << " songs)...\n";
        Node* temp = head;
        for (int i = 0; i < n; i++) {
            cout << "Playing: " << temp->title
                 << " [" << temp->time_duration << " min]\n";
            temp = temp->next; // circular, so it automatically loops
        }
    }
};

// Menu-driven program
int main() {
    Playlist pl;
    int choice;

    do {
        cout << "\n--- Playlist Menu ---\n";
        cout << "1. Insert Media File\n";
        cout << "2. Delete Media File\n";
        cout << "3. Display Playlist\n";
        cout << "4. Sort Playlist\n";
        cout << "5. Play in Loop\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, pos;
            string title;
            float duration;
            cout << "Enter music_id: "; cin >> id;
            cout << "Enter title: "; cin.ignore(); getline(cin, title);
            cout << "Enter duration (in min): "; cin >> duration;
            cout << "Enter position: "; cin >> pos;
            pl.insertAt(pos, id, title, duration);
        }
        else if (choice == 2) {
            int pos;
            cout << "Enter position to delete: "; cin >> pos;
            pl.deleteAt(pos);
        }
        else if (choice == 3) {
            pl.display();
        }
        else if (choice == 4) {
            int field;
            cout << "Sort by: 1.ID  2.Title  3.Duration: ";
            cin >> field;
            pl.sortPlaylist(field);
        }
        else if (choice == 5) {
            int n;
            cout << "Enter number of songs to play in loop: ";
            cin >> n;
            pl.playLoop(n);
        }
        else if (choice == 6) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
