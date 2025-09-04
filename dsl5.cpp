#include <iostream>
#include <string.h>
using namespace std;

class Node
{
    public:
        int page_id;
        char page_desc[20];
        char time_stamp[20];
        Node* next;
        Node* prev;

        Node(int id, char* desc, char* timestamp) 
        {
            page_id = id;
            strcpy(page_desc, desc);
            strcpy(time_stamp, timestamp);
            next = NULL;
            prev = NULL;
        }
};

class Browser
{
    private:
        Node* head;  
        Node* tail; 
        Node* current; 

    public:
        Browser() 
        {
            head = NULL;
            tail = NULL;
            current = NULL;
        }

        void add_page(int id, char* desc, char* timestamp);
        void visit_page(int id);
        void navigate_backward();
        void navigate_forward();
        void delete_page(int id);
        void display_history_forward();
        void display_history_backward();
        
};

int main() 
{
    Browser browser;
    int choice, id;
    char desc[20], timestamp[20];

    do 
    {
        cout << "\n--- Browser History Menu ---\n";
        cout << "1. Add Page\n";
        cout << "2. Visit Page\n";
        cout << "3. Navigate Backward\n";
        cout << "4. Navigate Forward\n";
        cout << "5. Delete Page\n";
        cout << "6. Display History Forward\n";
        cout << "7. Display History Backward\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:  
                cout << "Enter page ID: ";
                cin >> id;
                cout << "Enter page description: ";
                cin.ignore();
                cin.getline(desc, 20);
                cout << "Enter timestamp: ";
                cin.getline(timestamp, 20);
                browser.add_page(id, desc, timestamp);
                break;

            case 2:  
                cout << "Enter page ID to visit: ";
                cin >> id;
                browser.visit_page(id);
                break;

            case 3:  
                browser.navigate_backward();
                break;

            case 4: 
                browser.navigate_forward();
                break;

            case 5: 
                cout << "Enter page ID to delete: ";
                cin >> id;
                browser.delete_page(id);
                break;

            case 6:  
                browser.display_history_forward();
                break;

            case 7:  
                browser.display_history_backward();
                break;

            case 8:  
                cout << "Exiting Browser History...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 8);

    return 0;
}

void Browser :: add_page(int id, char* desc, char* timestamp) 
{
    Node* newNode = new Node(id, desc, timestamp);

    if (head == NULL) 
    {
        head = tail = current = newNode;
    } 
    else 
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    cout << "Page added: " << newNode->page_desc << " at " << newNode->time_stamp << endl;
}

void Browser :: visit_page(int id) 
{
    Node* temp = head;

    while (temp != NULL) 
    {
        if (temp->page_id == id) 
        {
            current = temp;
            cout << "Visiting page: " << current->page_desc << " at " << current->time_stamp << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Page not found!" << endl;
}

void Browser :: navigate_backward() 
{
    if (current == NULL || current->prev == NULL) 
    {
        cout << "No previous page!" << endl;
        return;
    }
    current = current->prev;
    cout << "Navigated back to: " << current->page_desc << " at " << current->time_stamp << endl;
}

void Browser :: navigate_forward() 
{
    if (current == NULL || current->next == NULL)
    {
        cout << "No next page!" << endl;
        return;
    }
    current = current->next;
    cout << "Navigated forward to: " << current->page_desc << " at " << current->time_stamp << endl;
}

void Browser ::  delete_page(int id) 
{
    Node* temp = head;

    while (temp != NULL) 
    {
        if (temp->page_id == id) 
        {
            if (temp->prev) 
            {
                temp->prev->next = temp->next;
            }
            if (temp->next) 
            {
                temp->next->prev = temp->prev;
            }
            if (temp == head) 
            {
                head = temp->next;
            }
            if (temp == tail) 
            {
                tail = temp->prev;
            }
            if (temp == current) 
            {
                current = nullptr; 
            }    
            delete temp;
            cout << "Page deleted: " << id << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Page not found!" << endl;
}

void Browser :: display_history_forward() 
{
    if (head == NULL) 
    {
        cout << "History is empty!" << endl;
        return;
    }
            
    Node* temp = head;
    cout << "Browser History (forward): " << endl;
    while (temp != NULL) 
    {
        cout << temp->page_id << ": " << temp->page_desc << " (" << temp->time_stamp << ")" << endl;
        temp = temp->next;
    }
}

void Browser :: display_history_backward() 
{
    if (tail == NULL) 
    {
        cout << "History is empty!" << endl;
        return;
    }

    Node* temp = tail;
    cout << "Browser History (backward): " << endl;
    while (temp != NULL) 
    {
        cout << temp->page_id << ": " << temp->page_desc << " (" << temp->time_stamp << ")" << endl;
        temp = temp->prev;
    }
}