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
class MyList : public List<Type>
{
public:
    MyList(int size = 10) : List<Type>(size)
    {
    }

    MyList(const MyList<Type>& other) : List<Type>(other)
    {
    }

    ~MyList()
    {
    }

    bool empty()
    {
        return this->currentSize == 0;
    }

    bool full()
    {
        return this->currentSize == this->maxSize;
    }

    int size()
    {
        return this->currentSize;
    }

    void addElementAtFirstIndex(Type value)
    {
        if (full())
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
        if (full())
        {
            cout << "List is full!" << endl;
            return;
        }

        this->arr[this->currentSize] = value;
        this->currentSize++;
    }

    Type removeElementFromEnd()
    {
        if (empty())
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
        if (empty())
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

    bool insertAt(int index, Type value)
    {
        if (full() || index < 0 || index > this->currentSize)
        {
            return false;
        }

        for (int i = this->currentSize; i > index; i--)
        {
            this->arr[i] = this->arr[i - 1];
        }

        this->arr[index] = value;
        this->currentSize++;

        return true;
    }

    Type last()
    {
        if (empty())
        {
            cout << "List is empty!" << endl;
            return Type();
        }

        return this->arr[this->currentSize - 1];
    }

    bool search(Type value)
    {
        for (int i = 0; i < this->currentSize; i++)
        {
            if (this->arr[i] == value)
            {
                return true;
            }
        }

        return false;
    }

    void display()
    {
        if (empty())
        {
            cout << "List is empty!" << endl;
            return;
        }

        for (int i = 0; i < this->currentSize; i++)
        {
            cout << this->arr[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    MyList<int> obj(10);

    int choice, value, index;

    do
    {
        cout << "\n===== TASK 2: MY LIST =====" << endl;
        cout << "1. Add at First" << endl;
        cout << "2. Add at Last" << endl;
        cout << "3. Remove from End" << endl;
        cout << "4. Remove from Start" << endl;
        cout << "5. Insert At Index" << endl;
        cout << "6. Display List" << endl;
        cout << "7. Search Element" << endl;
        cout << "8. Display Last Element" << endl;
        cout << "9. Check Empty" << endl;
        cout << "10. Check Full" << endl;
        cout << "11. Display Size" << endl;
        cout << "12. Exit" << endl;

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
            cout << "Enter index: ";
            cin >> index;

            cout << "Enter value: ";
            cin >> value;

            if (obj.insertAt(index, value))
            {
                cout << "Value inserted successfully." << endl;
            }
            else
            {
                cout << "Invalid index or list is full." << endl;
            }
        }
        else if (choice == 6)
        {
            obj.display();
        }
        else if (choice == 7)
        {
            cout << "Enter value to search: ";
            cin >> value;

            if (obj.search(value))
            {
                cout << "Element found." << endl;
            }
            else
            {
                cout << "Element not found." << endl;
            }
        }
        else if (choice == 8)
        {
            if (!obj.empty())
            {
                cout << "Last element: " << obj.last() << endl;
            }
            else
            {
                cout << "List is empty!" << endl;
            }
        }
        else if (choice == 9)
        {
            cout << (obj.empty() ? "List is empty." : "List is not empty.") << endl;
        }
        else if (choice == 10)
        {
            cout << (obj.full() ? "List is full." : "List is not full.") << endl;
        }
        else if (choice == 11)
        {
            cout << "Current size: " << obj.size() << endl;
        }

    } while (choice != 12);

    return 0;
}