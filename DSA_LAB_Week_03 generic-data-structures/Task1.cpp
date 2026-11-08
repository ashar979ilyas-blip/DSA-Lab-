#include <iostream>
using namespace std;

template <class Type>
class List
{
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    List(int size = 10)
    {
        maxSize = size;
        currentSize = 0;
        arr = new Type[maxSize];
    }

    List(const List<Type>& other)
    {
        maxSize = other.maxSize;
        currentSize = other.currentSize;

        arr = new Type[maxSize];

        for (int i = 0; i < currentSize; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    virtual void addElementAtFirstIndex(Type value) = 0;

    virtual void addElementAtLastIndex(Type value) = 0;

    virtual Type removeElementFromEnd() = 0;

    virtual void removeElementFromStart() = 0;

    virtual ~List()
    {
        delete[] arr;
    }
};

template <class Type>
class BasicList : public List<Type>
{
public:
    BasicList(int size = 10) : List<Type>(size)
    {
    }

    void addElementAtFirstIndex(Type value)
    {
        if (this->currentSize == this->maxSize)
        {
            cout << "List is full!" << endl;
            return;
        }

        for (int i = this->currentSize; i > 0; i--)
        {
            this->arr[i] = this->arr[i - 1];
        }

        this->arr[0] = value;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type value)
    {
        if (this->currentSize == this->maxSize)
        {
            cout << "List is full!" << endl;
            return;
        }

        this->arr[this->currentSize] = value;
        this->currentSize++;
    }

    Type removeElementFromEnd()
    {
        if (this->currentSize == 0)
        {
            cout << "List is empty!" << endl;
            return Type();
        }

        Type value = this->arr[this->currentSize - 1];
        this->currentSize--;

        return value;
    }

    void removeElementFromStart()
    {
        if (this->currentSize == 0)
        {
            cout << "List is empty!" << endl;
            return;
        }

        for (int i = 0; i < this->currentSize - 1; i++)
        {
            this->arr[i] = this->arr[i + 1];
        }

        this->currentSize--;
    }

    void display()
    {
        for (int i = 0; i < this->currentSize; i++)
        {
            cout << this->arr[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    BasicList<int> obj(10);

    int choice;
    int value;

    do
    {
        cout << "\n===== TASK 1 =====" << endl;
        cout << "1. Add at First Index" << endl;
        cout << "2. Add at Last Index" << endl;
        cout << "3. Remove from End" << endl;
        cout << "4. Remove from Start" << endl;
        cout << "5. Display List" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter value: ";
            cin >> value;

            obj.addElementAtFirstIndex(value);
        }
        else if (choice == 2)
        {
            cout << "Enter value: ";
            cin >> value;

            obj.addElementAtLastIndex(value);
        }
        else if (choice == 3)
        {
            cout << "Removed: " << obj.removeElementFromEnd() << endl;
        }
        else if (choice == 4)
        {
            obj.removeElementFromStart();
        }
        else if (choice == 5)
        {
            obj.display();
        }

    } while (choice != 6);

    return 0;
}