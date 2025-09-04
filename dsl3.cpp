#include <iostream>
#include <string.h>
using namespace std;

const int table_size = 10;

class Client 
{
public:
    string name;
    string telephone;

    Client() 
    {
        name = "";
        telephone = "0";
    }

};

class HashTable
{
    private :
        Client* table;
    
    public :
        HashTable()
        {
            table = new Client[table_size];
        }

        int hashfuntion(string & key)
        {
            int sum = 0;
            for (int i = 0; i < key.length(); i++)
            {
                sum += key[i];
            }
            return sum % table_size;
        }

        void insert(string & name, string & phone)
        {
            int index = hashfuntion(name);
            int originalindex = index;
            int i = 0;

            while(table[index].telephone != "0" && table_size)
            {
                index = (originalindex + (++i)) % table_size;
            }

            if(i < table_size)
            {
                table[index].name = name;
                table[index].telephone = phone;
                cout << "Inserted at index : " << index << endl;
            }
            else
            {
                cout << "Hash Table is Full." << endl;
            }
        }

        void display()
        {
            cout << "\nTelephone Book :\n";

            for(int i = 0;i < table_size; i++)
            {
                cout << "Index : " << i << " : ";
                if(table[i].telephone != "0")
                {
                    cout << table[i].name << " - " << table[i].telephone << endl;
                }
                else
                {
                    cout << "Empty" << endl;
                }
            }
        }

        void search(string & name)
        {
            int index = hashfuntion(name);
            int originalindex = index;
            int comparisons = 1;

            while(table[index].name != name && comparisons <= table_size)
            {
                index = (originalindex + comparisons) % table_size;
                comparisons++;
            }
            if(comparisons <= table_size && table[index].name == name)
            {
                cout << "\nFound at index " << index << " : " << table[index].telephone << " (Comparisons : " << comparisons << ")\n";
            }
            else
            {
                cout << "\nClient nat found." << "(Comparisons : )" << comparisons << ")\n";
            }
        }

        ~HashTable()
        {
            delete[] table;
        }
};

int main() 
{
    int n, choice;
    string name,phone;

    HashTable ht;
    
    do
    {
        cout << "\nTelephone Book Menu : \n";

        cout << "1 -> Insert Record\n";
        cout << "2 -> Display Table\n";
        cout << "3 -> Search  Client\n";
        cout << "4 -> Exit\n";

        cout << "Enter your choice : ";
        cin >> choice;
        cin.ignore();

        switch(choice)
        {
            case 1 :
                cout << "Enter number of clients to insert : ";
                cin >> n;
                cin.ignore();

                for(int i = 0; i < n; i++)
                {
                    cout << "\nClient : " << i+1 << " :\n";
                    cout << "Enter name : ";
                    getline(cin, name);
                    cout << "Enter telephone number : ";
                    getline(cin, phone);

                    ht.insert(name, phone);
                }

                break;
            
            case 2 :
                ht.display();
                break;
            
            case 3 :
                cout << "Enter client name to search : ";
                getline(cin, name);
                ht.search(name);

                break;
            
            case 4 :
                cout << "Exiting Program..." << endl;
                
                break;
            
            default :
                cout << "Invalid Choice!" << endl;
        }
    } while(choice != 4);

    return 0;
}