
#include <iostream>
#include <string>
using namespace std;

class Queue
{
private:
    struct Node
    {
        string documentName;
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

    void enqueue(string document_name)
    {
        Node* newNode = new Node;

        newNode->documentName = document_name;
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

        cout << "Print Job Added Successfully." << endl;
    }

    void dequeue()
    {
        if (frontNode == NULL)
        {
            cout << "No Print Jobs Available!" << endl;
            return;
        }

        Node* temp = frontNode;

        cout << "Printing Document: "
            << temp->documentName << endl;

        frontNode = frontNode->next;

        if (frontNode == NULL)
            rear = NULL;

        delete temp;
    }

    void front()
    {
        if (frontNode == NULL)
        {
            cout << "Queue is Empty!" << endl;
            return;
        }

        cout << "Next Document: "
            << frontNode->documentName << endl;
    }

    void display()
    {
        if (frontNode == NULL)
        {
            cout << "No Print Jobs Available!" << endl;
            return;
        }

        Node* temp = frontNode;

        cout << "\nPending Print Jobs:\n";

        while (temp != NULL)
        {
            cout << temp->documentName << endl;
            temp = temp->next;
        }
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
    int choice;
    string name;

    do
    {
        cout << "\n1. Add Print Job";
        cout << "\n2. Print Document";
        cout << "\n3. Check Next Document";
        cout << "\n4. Display Print Jobs";
        cout << "\n0. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter Document Name: ";
            getline(cin, name);
            q.enqueue(name);
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
