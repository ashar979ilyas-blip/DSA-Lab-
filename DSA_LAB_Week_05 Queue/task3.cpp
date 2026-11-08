
#include <iostream>
using namespace std;

class Queue
{
private:
    int arr[100];
    int frontIndex, rear, count;

public:
    Queue()
    {
        frontIndex = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(int value)
    {
        if (count == 100)
            return;

        rear = (rear + 1) % 100;
        arr[rear] = value;
        count++;
    }

    int dequeue()
    {
        if (isEmpty())
            return -1;

        int value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % 100;
        count--;

        return value;
    }

    int front()
    {
        if (isEmpty())
            return -1;

        return arr[frontIndex];
    }

    bool isEmpty()
    {
        return count == 0;
    }

    int size()
    {
        return count;
    }

    void display()
    {
        for (int i = 0; i < count; i++)
        {
            cout << arr[(frontIndex + i) % 100] << " ";
        }

        cout << endl;
    }
};

void reverseFirstK(Queue& q, int k)
{
    int stack[100];
    int top = -1;

    if (k > q.size())
        k = q.size();

    if (k <= 1)
        return;

    for (int i = 0; i < k; i++)
    {
        stack[++top] = q.dequeue();
    }

    while (top != -1)
    {
        q.enqueue(stack[top--]);
    }

    int remaining = q.size() - k;

    for (int i = 0; i < remaining; i++)
    {
        q.enqueue(q.dequeue());
    }
}

int main()
{
    Queue q;
    int n, value, k;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n < 0 || n > 100)
    {
        cout << "Invalid size!" << endl;
        return 0;
    }

    cout << "Enter Queue Elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> value;
        q.enqueue(value);
    }

    cout << "Original Queue: ";
    q.display();

    cout << "Enter K: ";
    cin >> k;

    if (k < 0)
    {
        cout << "Invalid K!" << endl;
        return 0;
    }

    reverseFirstK(q, k);

    cout << "Output Queue: ";
    q.display();

    return 0;
}
