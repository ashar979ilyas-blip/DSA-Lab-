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

template <class Type>
class CustomList : public MyList<Type>
{
public:
    CustomList(int size = 10) : MyList<Type>(size)
    {
    }

    CustomList(const CustomList<Type>& other) : MyList<Type>(other)
    {
    }

    ~CustomList()
    {
    }

    bool isPrime(Type num)
    {
        if (num < 2)
        {
            return false;
        }

        for (int i = 2; i < num; i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    Type sum_ofPrime()
    {
        Type sum = 0;

        for (int i = 0; i < this->currentSize; i++)
        {
            if (isPrime(this->arr[i]))
            {
                sum = sum + this->arr[i];
            }
        }

        return sum;
    }


    Type secondMaxEven()
    {
        Type max1 = Type();
        Type max2 = Type();

        bool found1 = false;
        bool found2 = false;

        for (int i = 0; i < this->currentSize; i++)
        {
            if (this->arr[i] % 2 == 0)
            {
                if (!found1 || this->arr[i] > max1)
                {
                    if (found1)
                    {
                        max2 = max1;
                        found2 = true;
                    }

                    max1 = this->arr[i];
                    found1 = true;
                }
                else if (this->arr[i] != max1 &&
                    (!found2 || this->arr[i] > max2))
                {
                    max2 = this->arr[i];
                    found2 = true;
                }
            }
        }

        if (!found2)
        {
            cout << "Second maximum even number not found." << endl;
            return Type();
        }

        return max2;
    }

    

    Type secondMinOdd()
    {
        Type min1 = Type();
        Type min2 = Type();

        bool found1 = false;
        bool found2 = false;

        for (int i = 0; i < this->currentSize; i++)
        {
            if (this->arr[i] % 2 != 0)
            {
                if (!found1 || this->arr[i] < min1)
                {
                    if (found1)
                    {
                        min2 = min1;
                        found2 = true;
                    }

                    min1 = this->arr[i];
                    found1 = true;
                }
                else if (this->arr[i] != min1 &&
                    (!found2 || this->arr[i] < min2))
                {
                    min2 = this->arr[i];
                    found2 = true;
                }
            }
        }

        if (!found2)
        {
            cout << "Second minimum odd number not found." << endl;
            return Type();
        }

        return min2;
    }


    void printDuplicates()
    {
        bool found = false;

        for (int i = 0; i < this->currentSize; i++)
        {
            bool alreadyPrinted = false;

            for (int j = 0; j < i; j++)
            {
                if (this->arr[i] == this->arr[j])
                {
                    alreadyPrinted = true;
                    break;
                }
            }

            if (!alreadyPrinted)
            {
                for (int j = i + 1; j < this->currentSize; j++)
                {
                    if (this->arr[i] == this->arr[j])
                    {
                        cout << this->arr[i] << " ";
                        found = true;
                        break;
                    }
                }
            }
        }

        if (!found)
        {
            cout << "No duplicates found.";
        }

        cout << endl;
    }


    void rotateClockwaise(int r)
    {
        int n = this->currentSize;
        int mid = n / 2;

        if (n == 0)
        {
            cout << "List is empty!" << endl;
            return;
        }

        int firstSize = mid;
        int secondSize = n - mid;

        if (firstSize > 0)
        {
            r = r % firstSize;

            for (int k = 0; k < r; k++)
            {
                Type temp = this->arr[mid - 1];

                for (int i = mid - 1; i > 0; i--)
                {
                    this->arr[i] = this->arr[i - 1];
                }

                this->arr[0] = temp;
            }
        }

        if (secondSize > 0)
        {
            int rotations = r % secondSize;

            for (int k = 0; k < rotations; k++)
            {
                Type temp = this->arr[n - 1];

                for (int i = n - 1; i > mid; i--)
                {
                    this->arr[i] = this->arr[i - 1];
                }

                this->arr[mid] = temp;
            }
        }

        cout << "Clockwise rotation completed." << endl;
    }

    

    void rotateanitclockwaise(int rt)
    {
        int n = this->currentSize;
        int mid = n / 2;

        if (n == 0)
        {
            cout << "List is empty!" << endl;
            return;
        }

        int firstSize = mid;
        int secondSize = n - mid;

        if (firstSize > 0)
        {
            int rotations = rt % firstSize;

            for (int k = 0; k < rotations; k++)
            {
                Type temp = this->arr[0];

                for (int i = 0; i < mid - 1; i++)
                {
                    this->arr[i] = this->arr[i + 1];
                }

                this->arr[mid - 1] = temp;
            }
        }

        if (secondSize > 0)
        {
            int rotations = rt % secondSize;

            for (int k = 0; k < rotations; k++)
            {
                Type temp = this->arr[mid];

                for (int i = mid; i < n - 1; i++)
                {
                    this->arr[i] = this->arr[i + 1];
                }

                this->arr[n - 1] = temp;
            }
        }

        cout << "Anti-clockwise rotation completed." << endl;
    }
};



int main()
{
    CustomList<int> obj(20);

    int choice, value, index, r;

    do
    {
        cout << "\n===== TASK 3: CUSTOM LIST =====" << endl;

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
        cout << "12. Sum of Prime Numbers" << endl;
        cout << "13. Second Maximum Even" << endl;
        cout << "14. Second Minimum Odd" << endl;
        cout << "15. Print Duplicates" << endl;
        cout << "16. Clockwise Rotation" << endl;
        cout << "17. Anti-clockwise Rotation" << endl;
        cout << "18. Exit" << endl;

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
                cout << "Inserted successfully." << endl;
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
        else if (choice == 12)
        {
            cout << "Sum of prime numbers: " << obj.sum_ofPrime() << endl;
        }
        else if (choice == 13)
        {
            cout << "Second maximum even: " << obj.secondMaxEven() << endl;
        }
        else if (choice == 14)
        {
            cout << "Second minimum odd: " << obj.secondMinOdd() << endl;
        }
        else if (choice == 15)
        {
            cout << "Duplicate elements: ";
            obj.printDuplicates();
        }
        else if (choice == 16)
        {
            cout << "Enter rotations: ";
            cin >> r;

            obj.rotateClockwaise(r);
            obj.display();
        }
        else if (choice == 17)
        {
            cout << "Enter rotations: ";
            cin >> r;

            obj.rotateanitclockwaise(r);
            obj.display();
        }

    } while (choice != 18);

    return 0;
}