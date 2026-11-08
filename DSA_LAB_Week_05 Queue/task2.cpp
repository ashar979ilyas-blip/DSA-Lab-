
#include <iostream>
using namespace std;

class Stack
{
private:
    int arr[100];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    void push(int value)
    {
        if (top == 99)
        {
            cout << "Stack is Full!" << endl;
            return;
        }

        arr[++top] = value;
    }

    int pop()
    {
        if (top == -1)
            return -1;

        return arr[top--];
    }

    bool isEmpty()
    {
        return top == -1;
    }

    int getTop()
    {
        if (isEmpty())
            return -1;

        return arr[top];
    }

    int getSize()
    {
        return top + 1;
    }

    int getElement(int index)
    {
        return arr[index];
    }
};

class Queue
{
private:
    Stack s1, s2;

    void transfer()
    {
        while (!s1.isEmpty())
        {
            s2.push(s1.pop());
        }
    }

public:
    void enQueue(int value)
    {
        s1.push(value);
        cout << "Element Inserted." << endl;
    }

    int deQueue()
    {
        if (s2.isEmpty())
            transfer();

        if (s2.isEmpty())
        {
            cout << "Queue is Empty!" << endl;
            return -1;
        }

        return s2.pop();
    }

    int front()
    {
        if (s2.isEmpty())
            transfer();

        if (s2.isEmpty())
        {
            cout << "Queue is Empty!" << endl;
            return -1;
        }

        return s2.getTop();
    }

    void display()
    {
        if (s1.isEmpty() && s2.isEmpty())
        {
            cout << "Queue is Empty!" << endl;
            return;
        }

        cout << "Queue: ";

        for (int i = s2.getSize() - 1; i >= 0; i--)
        {
            cout << s2.getElement(i) << " ";
        }

        for (int i = 0; i < s1.getSize(); i++)
        {
            cout << s1.getElement(i) << " ";
        }

        cout << endl;
    }
};

int main()
{
    Queue q;
    int choice, value;

    do
    {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Front";
        cout << "\n4. Display";
        cout << "\n0. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Value: ";
            cin >> value;
            q.enQueue(value);
            break;

        case 2:
            value = q.deQueue();
            if (value != -1)
                cout << "Removed: " << value << endl;
            break;

        case 3:
            value = q.front();
            if (value != -1)
                cout << "Front Element: " << value << endl;
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
