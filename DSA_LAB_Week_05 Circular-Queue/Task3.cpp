#include <iostream>
using namespace std;

struct PrintJob
{
    int jobID;
    char userName[50];
    int pages;
};

class PrinterQueue
{
private:
    PrintJob arr[5];
    int front, rear, currentSize, maxSize;

public:
    PrinterQueue()
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

    void enqueue(PrintJob p)
    {
        if (isFull())
        {
            cout << "Printer queue is full!" << endl;
            return;
        }

        rear = (rear + 1) % maxSize;
        arr[rear] = p;
        currentSize++;

        cout << "Print job added successfully." << endl;
    }

    PrintJob dequeue()
    {
        PrintJob emptyJob = { 0, "", 0 };

        if (isEmpty())
        {
            cout << "No print jobs available!" << endl;
            return emptyJob;
        }

        PrintJob completed = arr[front];

        front = (front + 1) % maxSize;
        currentSize--;

        if (currentSize == 0)
        {
            front = 0;
            rear = -1;
        }

        return completed;
    }

    void peek()
    {
        if (isEmpty())
        {
            cout << "No pending print jobs." << endl;
            return;
        }

        cout << "Job ID: " << arr[front].jobID << endl;
        cout << "User Name: " << arr[front].userName << endl;
        cout << "Pages: " << arr[front].pages << endl;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No pending print jobs." << endl;
            return;
        }

        for (int i = 0; i < currentSize; i++)
        {
            int index = (front + i) % maxSize;

            cout << "\nPrint Job " << i + 1 << endl;
            cout << "Job ID: " << arr[index].jobID << endl;
            cout << "User Name: " << arr[index].userName << endl;
            cout << "Pages: " << arr[index].pages << endl;
        }
    }

    int getTotal()
    {
        return currentSize;
    }
};

int main()
{
    PrinterQueue q;
    int choice;

    do
    {
        cout << "\n===== PRINTER QUEUE =====" << endl;
        cout << "1. Submit Print Job" << endl;
        cout << "2. Process Print Job" << endl;
        cout << "3. Display Next Print Job" << endl;
        cout << "4. Display All Print Jobs" << endl;
        cout << "5. Total Pending Jobs" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            PrintJob p;

            cout << "Enter Job ID: ";
            cin >> p.jobID;

            cout << "Enter User Name: ";
            cin >> ws;
            cin.getline(p.userName, 50);

            cout << "Enter Number of Pages: ";
            cin >> p.pages;

            q.enqueue(p);
        }
        else if (choice == 2)
        {
            PrintJob p = q.dequeue();

            if (p.jobID != 0)
            {
                cout << "Print job completed!" << endl;
                cout << "Job ID: " << p.jobID << endl;
                cout << "User: " << p.userName << endl;
                cout << "Pages printed: " << p.pages << endl;
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
            cout << "Total pending jobs: " << q.getTotal() << endl;
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