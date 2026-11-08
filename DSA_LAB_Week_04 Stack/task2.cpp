#include <iostream>
using namespace std;

template <typename T>
class AbstractStack
{
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T>
{
private:
    T* arr;
    T* minArr;
    int maxSize;
    int currentSize;

public:
    myStack(int size)
    {
        maxSize = size;
        currentSize = 0;
        arr = new T[maxSize];
        minArr = new T[maxSize];
    }

    void push(T value)
    {
        if (isFull())
        {
            cout << "Stack is full. Cannot push element.\n";
            return;
        }

        arr[currentSize] = value;

        if (currentSize == 0 || value < minArr[currentSize - 1])
            minArr[currentSize] = value;
        else
            minArr[currentSize] = minArr[currentSize - 1];

        currentSize++;
        cout << "Element pushed successfully.\n";
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty. Cannot pop.\n";
            return T();
        }

        currentSize--;
        return arr[currentSize];
    }

    T top() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty.\n";
            return T();
        }

        return arr[currentSize - 1];
    }

    bool isEmpty() const
    {
        return currentSize == 0;
    }

    bool isFull() const
    {
        return currentSize == maxSize;
    }

    T getMin() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty. Minimum does not exist.\n";
            return T();
        }

        return minArr[currentSize - 1];
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack elements (top to bottom): ";
        for (int i = currentSize - 1; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }

    ~myStack()
    {
        delete[] arr;
        delete[] minArr;
    }
};

int main()
{
    int size, choice, value;

    cout << "Enter maximum stack size: ";
    cin >> size;

    myStack<int> s(size);

    do
    {
        cout << "\n--- STACK MENU ---\n";
        cout << "1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Show top element\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Check if stack is full\n";
        cout << "6. Display stack elements\n";
        cout << "7. Show minimum element\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            s.push(value);
            break;

        case 2:
            if (!s.isEmpty())
                cout << "Removed element: " << s.pop() << endl;
            else
                cout << "Stack is empty.\n";
            break;

        case 3:
            if (!s.isEmpty())
                cout << "Top element: " << s.top() << endl;
            else
                cout << "Stack is empty.\n";
            break;

        case 4:
            if (s.isEmpty())
                cout << "Stack is empty.\n";
            else
                cout << "Stack is not empty.\n";
            break;

        case 5:
            if (s.isFull())
                cout << "Stack is full.\n";
            else
                cout << "Stack is not full.\n";
            break;

        case 6:
            s.display();
            break;

        case 7:
            if (!s.isEmpty())
                cout << "Minimum element: " << s.getMin() << endl;
            else
                cout << "Stack is empty.\n";
            break;

        case 8:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
