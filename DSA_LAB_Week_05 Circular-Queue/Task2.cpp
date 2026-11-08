#include <iostream>
using namespace std;

struct Booking
{
    int customerID;
    char customerName[50];
    int numberOfTickets;
};

class CinemaQueue
{
private:
    Booking arr[5];
    int front, rear, currentSize, maxSize;

public:
    CinemaQueue()
    {
        front = 0;
        rear = -1;
        currentSize = 0;
        maxSize = 5;
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }

    bool isFull()
    {
        return currentSize == maxSize;
    }

    void enqueue(Booking b)
    {
        if (isFull())
        {
            cout << "Queue is full!" << endl;
            return;
        }

        rear = (rear + 1) % maxSize;
        arr[rear] = b;
        currentSize++;

        cout << "Booking added successfully." << endl;
    }

    Booking dequeue()
    {
        Booking emptyBooking = { 0, "", 0 };

        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return emptyBooking;
        }

        Booking cancelled = arr[front];

        front = (front + 1) % maxSize;
        currentSize--;

        if (currentSize == 0)
        {
            front = 0;
            rear = -1;
        }

        return cancelled;
    }

    void peek()
    {
        if (isEmpty())
        {
            cout << "No bookings available." << endl;
            return;
        }

        cout << "Customer ID: " << arr[front].customerID << endl;
        cout << "Customer Name: " << arr[front].customerName << endl;
        cout << "Tickets: " << arr[front].numberOfTickets << endl;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No bookings available." << endl;
            return;
        }

        for (int i = 0; i < currentSize; i++)
        {
            int index = (front + i) % maxSize;

            cout << "\nBooking " << i + 1 << endl;
            cout << "Customer ID: " << arr[index].customerID << endl;
            cout << "Customer Name: " << arr[index].customerName << endl;
            cout << "Tickets: " << arr[index].numberOfTickets << endl;
        }
    }

    int getTotal()
    {
        return currentSize;
    }
};

int main()
{
    CinemaQueue q;
    int choice;

    do
    {
        cout << "\n===== CINEMA BOOKING QUEUE =====" << endl;
        cout << "1. Book Tickets" << endl;
        cout << "2. Cancel First Booking" << endl;
        cout << "3. Display Next Booking" << endl;
        cout << "4. Display All Bookings" << endl;
        cout << "5. Total Bookings" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Booking b;

            cout << "Enter Customer ID: ";
            cin >> b.customerID;

            cout << "Enter Customer Name: ";
            cin >> ws;
            cin.getline(b.customerName, 50);

            cout << "Enter Number of Tickets: ";
            cin >> b.numberOfTickets;

            q.enqueue(b);
        }
        else if (choice == 2)
        {
            Booking b = q.dequeue();

            if (b.customerID != 0)
            {
                cout << "Booking cancelled for: " << b.customerName << endl;
            }
        }
        else if (choice == 3)
        {
            q.peek();
        }
        else if (choice == 4)
        {
            q.display();
        }
        else if (choice == 5)
        {
            cout << "Total bookings: " << q.getTotal() << endl;
        }
        else if (choice == 6)
        {
            cout << "Exiting..." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 6);

    return 0;
}