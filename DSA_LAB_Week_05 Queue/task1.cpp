
#include <iostream>
using namespace std;

template <typename T>
class AbstractQueue
{
public:
    virtual void enQueue(T value) = 0;
    virtual T deQueue() = 0;
    virtual T front() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractQueue() {}
};

template <typename T>
class myQueue : public AbstractQueue<T>
{
private:
    T* arr;
    int maxSize;
    int frontIndex;
    int rear;
    int count;

public:
    myQueue(int size)
    {
        maxSize = size;
        arr = new T[maxSize];
        frontIndex = 0;
        rear = -1;
        count = 0;
    }

    void enQueue(T value)
    {
        if (isFull())
        {
            cout << "Queue is Full!" << endl;
            return;
        }

        rear = (rear + 1) % maxSize;
        arr[rear] = value;
        count++;

        cout << "Element inserted successfully." << endl;
    }

    T deQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty!" << endl;
            return T();
        }

        T value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        count--;

        return value;
    }

    T front() const
    {
        if (isEmpty())
        {
            cout << "Queue is Empty!" << endl;
            return T();
        }

        return arr[frontIndex];
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    bool isFull() const
    {
        return count == maxSize;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is Empty!" << endl;
            return;
        }

        cout << "Queue: ";

        for (int i = 0; i < count; i++)
        {
            cout << arr[(frontIndex + i) % maxSize] << " ";
        }

        cout << endl;
    }

    ~myQueue()
    {
        delete[] arr;
    }
};

int main()
{
    int size;
    cout << "Enter Queue Size: ";
    cin >> size;

    if (size <= 0)
    {
        cout << "Invalid size!" << endl;
        return 0;
    }

    myQueue<int> q(size);

    int choice, value;

    do
    {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Front";
        cout << "\n4. Check Empty";
        cout << "\n5. Check Full";
        cout << "\n6. Display";
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
            if (!q.isEmpty())
                cout << "Removed: " << q.deQueue() << endl;
            else
                cout << "Queue is Empty!" << endl;
            break;

        case 3:
            if (!q.isEmpty())
                cout << "Front Element: " << q.front() << endl;
            else
                cout << "Queue is Empty!" << endl;
            break;

        case 4:
            cout << (q.isEmpty() ? "Queue is Empty" : "Queue is Not Empty") << endl;
            break;

        case 5:
            cout << (q.isFull() ? "Queue is Full" : "Queue is Not Full") << endl;
            break;

        case 6:
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
