#include <iostream>
#include <string>
using namespace std;

struct Node {
    int music_id;
    string title;
    float time_duration;
    Node* next;
};

class Playlist {
    Node* head;

public:
    Playlist();

    void insert(int id, string title, float duration, int pos);
    void remove(int id);
    void display();
    void sort(int choice);
    void playLoop();
};

// Constructor
Playlist::Playlist() {
    head = nullptr;
}

// Insert at any position
void Playlist::insert(int id, string title, float duration, int pos) {
    Node* newNode = new Node{id, title, duration, nullptr};

    if (!head) {  // Empty list
        head = newNode;
        head->next = head;
        return;
    }

    if (pos == 1) {  // Insert at beginning
        Node* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < pos - 1 && temp->next != head; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete by music_id
void Playlist::remove(int id) {
    if (!head) {
        cout << "Playlist is empty!\n";
        return;
    }

    Node* curr = head;
    Node* prev = nullptr;

    // Case: deleting head
    if (head->music_id == id) {
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next != head)
            temp = temp->next;
        temp->next = head->next;
        Node* del = head;
        head = head->next;
        delete del;
        return;
    }

    prev = head;
    curr = head->next;
    while (curr != head) {
        if (curr->music_id == id) {
            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Music ID not found!\n";
}

// Display playlist
void Playlist::display() {
    if (!head) {
        cout << "Playlist is empty!\n";
        return;
    }
    Node* temp = head;
    cout << "\n--- Playlist ---\n";
    do {
        cout << "ID: " << temp->music_id
             << " | Title: " << temp->title
             << " | Duration: " << temp->time_duration << " mins\n";
        temp = temp->next;
    } while (temp != head);
    cout << "----------------\n";
}

// Bubble Sort by field
void Playlist::sort(int choice) {
    if (!head || head->next == head) return;

    bool swapped;
    do {
        swapped = false;
        Node* curr = head;
        do {
            Node* nextNode = curr->next;
            if (nextNode == head) break;

            bool condition = false;
            if (choice == 1 && curr->music_id > nextNode->music_id)
                condition = true;
            else if (choice == 2 && curr->title > nextNode->title)
                condition = true;
            else if (choice == 3 && curr->time_duration > nextNode->time_duration)
                condition = true;

            if (condition) {
                swap(curr->music_id, nextNode->music_id);
                swap(curr->title, nextNode->title);
                swap(curr->time_duration, nextNode->time_duration);
                swapped = true;
            }

            curr = curr->next;
        } while (curr->next != head);
    } while (swapped);

    cout << "Playlist sorted!\n";
}

// Play continuously
void Playlist::playLoop() {
    if (!head) {
        cout << "Playlist is empty!\n";
        return;
    }
    Node* temp = head;
    cout << "Playing in loop (Press Ctrl+C to stop):\n";
    while (true) {
        cout << "Now Playing -> ID: " << temp->music_id
             << " | Title: " << temp->title
             << " | Duration: " << temp->time_duration << " mins\n";
        temp = temp->next;
    }
}

// ---------------- Main -----------------
int main() {
    Playlist playlist;
    int choice;

    do {
        cout << "\n====== Playlist Menu ======\n";
        cout << "1. Insert Media File\n";
        cout << "2. Delete Media File\n";
        cout << "3. Display Playlist\n";
        cout << "4. Sort Playlist\n";
        cout << "5. Play in Loop\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, pos;
                string title;
                float duration;
                cout << "Enter Music ID: ";
                cin >> id;
                cin.ignore();  // remove newline
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Duration (in minutes): ";
                cin >> duration;
                cout << "Enter Position to Insert: ";
                cin >> pos;
                playlist.insert(id, title, duration, pos);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Music ID to Delete: ";
                cin >> id;
                playlist.remove(id);
                break;
            }
            case 3:
                playlist.display();
                break;
            case 4: {
                int sortChoice;
                cout << "Sort by: 1.ID  2.Title  3.Duration : ";
                cin >> sortChoice;
                playlist.sort(sortChoice);
                break;
            }
            case 5:
                playlist.playLoop();  // infinite loop until stopped manually
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
