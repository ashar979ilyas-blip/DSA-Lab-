#include <iostream>
using namespace std;

struct Customer
{
    char name[50];
    char transaction[50];
};

class BankQueue
{
private:
    Customer arr[5];
    int front, rear, currentSize, maxSize;

public:
    BankQueue()
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

    void enqueue(Customer c)
    {
        if (isFull())
        {
            cout << "Queue is full!" << endl;
            return;
        }

        rear = (rear + 1) % maxSize;
        arr[rear] = c;
        currentSize++;

        cout << "Customer added successfully." << endl;
    }

    Customer dequeue()
    {
        Customer emptyCustomer = { "", "" };

        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return emptyCustomer;
        }

        Customer served = arr[front];

        front = (front + 1) % maxSize;
        currentSize--;

        if (currentSize == 0)
        {
            front = 0;
            rear = -1;
        }

        return served;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No customers waiting." << endl;
            return;
        }

        for (int i = 0; i < currentSize; i++)
        {
            int index = (front + i) % maxSize;

            cout << "Name: " << arr[index].name << endl;
            cout << "Transaction: " << arr[index].transaction << endl;
        }
    }

    int getTotal()
    {
        return currentSize;
    }
};

int main()
{
    BankQueue q;
    int choice;

    do
    {
        cout << "\n===== BANK QUEUE =====" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Serve Customer" << endl;
        cout << "3. Display Customers" << endl;
        cout << "4. Total Customers" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Customer c;

            cout << "Enter name: ";
            cin >> ws;
            cin.getline(c.name, 50);

            cout << "Enter transaction: ";
            cin.getline(c.transaction, 50);

            q.enqueue(c);
        }
        else if (choice == 2)
        {
            Customer c = q.dequeue();

            if (c.name[0] != '\0')
            {
                cout << "Customer served: " << c.name << endl;
                cout << "Transaction: " << c.transaction << endl;
            }
        }
        else if (choice == 3)
        {
            q.display();
        }
        else if (choice == 4)
        {
            cout << "Total customers: " << q.getTotal() << endl;
        }
        else if (choice == 5)
        {
            cout << "Exiting..." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}