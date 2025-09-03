#include<iostream>
using namespace std;

class Seat
{
    public :
        bool booked;
        Seat* prev;
        Seat* next;

        Seat()
        {
            booked = false;
            prev = NULL;
            next = NULL;
        }
};

class Row
{
    public :
        Seat* head;
        int totalseats;
        
        Row()
        {
            head = NULL;
            totalseats = 0;
        }
        Row(int n)
        {
            head = NULL;
            totalseats = n;

            Seat *p = NULL;
            for(int i = 0; i < n; i++)
            {
                Seat* q = new Seat();

                if(head == NULL)
                {
                    head = q;
                    p = head;
                }
                else
                {
                    p -> next = q;
                    q -> prev = p;
                    p = q;
                }
                head -> prev = p;
                p -> next = head;
            }
        }
};

class Theater
{
    public :
        Row** row;
        int totalrows;

        Theater()
        {
            row = NULL;
            totalrows= 0;
        }

        Theater(int rowscount, int totalseats)
        {
            totalrows = rowscount;
            row = new Row*[rowscount];

            for(int i = 0; i < rowscount; i++)
            {
                row[i] = new Row(totalseats);
            }
        }

        void displayAvailableSeats();
        void bookSeat(int, int);
        void cancelBooking(int, int);
};

int main()
{
    int rows, seats;
    
    cout << "Enter number of rows : ";
    cin >> rows;
    cout << "Enter number of seats per row : ";
    cin >> seats;

    Theater theater (rows, seats);

    int choice;
    
    cout << "\n1. Display Available Seats\n";
    cout << "2. Book a Seat\n";
    cout << "3. Cancel Booking\n";
    cout << "4. Exit\n";
    
    do 
    {    
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                theater.displayAvailableSeats();
                break;

            case 2: 
            {
                int rowNum, seatNum;
                cout << "Enter row number to book: ";
                cin >> rowNum;
                cout << "Enter seat number to book: ";
                cin >> seatNum;
                theater.bookSeat(rowNum, seatNum);
                
                break;
            }

            case 3: 
            {
                int rowNum, seatNum;
                cout << "Enter row number to cancel: ";
                cin >> rowNum;
                cout << "Enter seat number to cancel: ";
                cin >> seatNum;
                theater.cancelBooking(rowNum, seatNum);
                
                break;
            }

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
 
void Theater::displayAvailableSeats()
{
    for(int i = 0; i < totalrows; i++)
    {
        cout << "Row " << i+1 << " : ";
        Seat* p = row[i]->head;

        for(int j = 0; j < row[i]->totalseats; j++)
        {
            if(p->booked == false)
            {
                cout << "S" << j + 1 << " ";
            }
            else
            {
                cout << "   ";  // show 'b' for booked seats
            }
            p = p->next;
        }
        cout << endl;
    }
}


void Theater:: bookSeat(int rownum, int seatnum)
{
    if(rownum < 1 || rownum > totalrows)
    {
        cout << "Invalid Row";
        return;
    }

    Row* Rows = row[rownum-1];
    if(seatnum < 1 || seatnum > Rows -> totalseats)
    {
        cout << "Invalid seats";
        return;
    }

    Seat* p = Rows -> head;
    for(int i = 0; i < seatnum-1; i++)
    {
        p = p -> next;
    }
    if(p -> booked == true)
    {
        cout << "Seat already booked!" << endl;
    }
    else
    {
        p -> booked = true;
        cout << "Seat " << seatnum << " in Row " << rownum << " is successfully booked." << endl;
    }
}

void Theater :: cancelBooking(int rownum, int seatnum)
{
    if(rownum < 1 || rownum > totalrows)
    {
        cout << "Invalid Row";
        return;
    }

    Row* Rows = row[rownum-1];
    if(seatnum < 1 || seatnum > Rows -> totalseats)
    {
        cout << "Invalid seats";
        return;
    }

    Seat* p = Rows -> head;
    for(int i = 0; i < seatnum-1; i++)
    {
        p = p -> next;
    }
    if(p -> booked == false)
    {
        cout << "Seat is not booked yet!" << endl;
    }
    else
    {
        p -> booked = false;
        cout << "Booking for Seat " << seatnum << " in Row " << rownum << " has been cancelled." << endl;
    }
}
