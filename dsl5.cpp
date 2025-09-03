/* 
Browser maintains the history which refers to a list of recently visited websites or
web pages in a data structure.
Functions:
1. Visit a specific web page
2. Navigate forward and backward
3. Add new pages
4. Delete web pages from existing links
*/

#include <iostream>
#include <string>
using namespace std;

class browser {
private:
    int page_id;
    string page_desc;
    string time_stamp;
    browser* next;
    browser* prev;

public:
    browser() {
        next = nullptr;
        prev = nullptr;
    }
    browser(int id, string desc, string stamp) {
        page_id = id;
        page_desc = desc;
        time_stamp = stamp;
        next = nullptr;
        prev = nullptr;
    }
    friend class history;
};

class history {
private:
    browser* head;
    browser* newnode;
    browser* temp;

public:
    history() {
        head = nullptr;
        newnode = nullptr;
        temp = nullptr;
    }

    void add_pages_beginning(int id, string desc, string stamp) {
        newnode = new browser(id, desc, stamp);
        newnode->prev = nullptr;
        newnode->next = head;
        if (head != nullptr) {
            head->prev = newnode;
        }
        head = newnode;
    }

    void add_pages_end(int id, string desc, string stamp) {
        newnode = new browser(id, desc, stamp);
        newnode->next = nullptr;
        if (head == nullptr) { // fixed: was assignment instead of comparison
            newnode->prev = nullptr;
            head = newnode;
        } else {
            temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
    }

    void add_pages_pos(int id, string desc, string stamp, int pos) {
        if (head == nullptr) {
            head = new browser(id, desc, stamp);
            return;
        } else {
            browser* x = new browser(id, desc, stamp);
            temp = head;
            int i = 1;
            while (i < pos - 1 && temp->next != nullptr) {
                temp = temp->next;
                i++;
            }
            x->next = temp->next;
            x->prev = temp;
            if (temp->next != nullptr) {
                (temp->next)->prev = x;
            }
            temp->next = x;
        }
    }

    void navigate_pages() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        temp = head;
        while (temp != nullptr) {
            cout << "Page id: " << temp->page_id << endl;
            cout << "Page desc: " << temp->page_desc << endl;
            cout << "Time stamp: " << temp->time_stamp << endl;
            temp = temp->next;
        }
    }

    void navigate_pages_backward() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        while (temp != nullptr) {
            cout << "Page id: " << temp->page_id << endl;
            cout << "Page desc: " << temp->page_desc << endl;
            cout << "Time stamp: " << temp->time_stamp << endl;
            temp = temp->prev;
        }
    }

    void visit_page(int id) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        temp = head;
        int position = 1;
        int flag = 0;
        while (temp != nullptr) {
            if (temp->page_id == id) { // fixed: was assignment instead of comparison
                cout << "Node found at position " << position << endl;
                flag = 1;
            }
            temp = temp->next;
            position++;
        }
        if (flag == 0) {
            cout << "Node not found" << endl;
        }
    }

    void delete_page_first() {
        browser* temp1;
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        temp1 = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp1;
    }

    void delete_page_last() {
        browser* temp2;
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        temp2 = head;
        while (temp2->next != nullptr) {
            temp2 = temp2->next;
        }
        if (temp2->prev != nullptr) {
            temp2->prev->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp2;
    }

    void delete_page_byid(int id) {
        browser* temp3;
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        temp3 = head;
        while (temp3 != nullptr && temp3->page_id != id) {
            temp3 = temp3->next;
        }
        if (temp3 == nullptr) {
            cout << "Node not found" << endl;
            return;
        }
        if (temp3->prev != nullptr) {
            temp3->prev->next = temp3->next;
        } else {
            head = temp3->next;
        }
        if (temp3->next != nullptr) {
            temp3->next->prev = temp3->prev;
        }
        delete temp3;
    }
};

int main() {
    int choice, id, pos;
    string desc, stamp;
    history hist;

    do {
        cout << "\nMenu\n";
        cout << "0. Exit\n";
        cout << "1. Insert at start\n";
        cout << "2. Insert at end\n";
        cout << "3. Insert at position\n";
        cout << "4. Navigate pages (forward)\n";
        cout << "5. Navigate pages backward\n";
        cout << "6. Search page by ID\n";
        cout << "7. Delete first page\n";
        cout << "8. Delete last page\n";
        cout << "9. Delete specific page (by page id)\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter page id: ";
            cin >> id;
            cout << "Enter page description: ";
            cin >> desc;
            cout << "Enter time stamp: ";
            cin >> stamp;
            hist.add_pages_beginning(id, desc, stamp);
            break;
        case 2:
            cout << "Enter page id: ";
            cin >> id;
            cout << "Enter page description: ";
            cin >> desc;
            cout << "Enter time stamp: ";
            cin >> stamp;
            hist.add_pages_end(id, desc, stamp);
            break;
        case 3:
            cout << "Enter position: ";
            cin >> pos;
            cout << "Enter page id: ";
            cin >> id;
            cout << "Enter page description: ";
            cin >> desc;
            cout << "Enter time stamp: ";
            cin >> stamp;
            hist.add_pages_pos(id, desc, stamp, pos);
            break;
        case 4:
            hist.navigate_pages();
            break;
        case 5:
            hist.navigate_pages_backward();
            break;
        case 6:
            cout << "Enter page id to search: ";
            cin >> id;
            hist.visit_page(id);
            break;
        case 7:
            hist.delete_page_first();
            break;
        case 8:
            hist.delete_page_last();
            break;
        case 9:
            cout << "Enter page id to delete: ";
            cin >> id;
            hist.delete_page_byid(id);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
