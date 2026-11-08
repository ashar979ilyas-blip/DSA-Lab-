
#include <iostream>
using namespace std;

class Queue
{
private:
    struct Node
    {
        int ticketID;
        Node* next;
    };

    Node* frontNode;
    Node* rear;

public:
    Queue()
    {
        frontNode = NULL;
        rear = NULL;
    }

    void enqueue(int ticket_id)
    {
        if (ticket_id < 1000 || ticket_id > 9999)
        {
            cout << "Ticket ID must be 4 digits!" << endl;
            return;
        }

        Node* temp = frontNode;

        while (temp != NULL)
        {
            if (temp->ticketID == ticket_id)
            {
                cout << "Ticket ID already exists!" << endl;
                return;
            }

            temp = temp->next;
        }

        Node* newNode = new Node;
        newNode->ticketID = ticket_id;
        newNode->next = NULL;

        if (frontNode == NULL)
        {
            frontNode = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        cout << "Ticket Added Successfully." << endl;
    }

    void dequeue()
    {
        if (frontNode == NULL)
        {
            cout << "No Pending Tickets!" << endl;
            return;
        }

        Node* temp = frontNode;

        cout << "Resolved Ticket: "
            << temp->ticketID << endl;

        frontNode = frontNode->next;

        if (frontNode == NULL)
            rear = NULL;

        delete temp;
    }

    void front()
    {
        if (frontNode == NULL)
        {
            cout << "No Pending Tickets!" << endl;
            return;
        }

        cout << "Next Ticket: "
            << frontNode->ticketID << endl;
    }

    void display()
    {
        if (frontNode == NULL)
        {
            cout << "No Pending Tickets!" << endl;
            return;
        }

        Node* temp = frontNode;

        cout << "Pending Tickets: ";

        while (temp != NULL)
        {
            cout << temp->ticketID << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    ~Queue()
    {
        while (frontNode != NULL)
        {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }
};

int main()
{
    Queue q;
    int choice, id;

    do
    {
        cout << "\n1. Add New Ticket";
        cout << "\n2. Resolve Ticket";
        cout << "\n3. Next Ticket";
        cout << "\n4. Display Tickets";
        cout << "\n0. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter 4-Digit Ticket ID: ";
            cin >> id;
            q.enqueue(id);
            break;

        case 2:
            q.dequeue();
            break;

        case 3:
            q.front();
            break;

        case 4:
            q.display();
            break;

        case 0:
            cout << "Program Ended." << endl;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}
