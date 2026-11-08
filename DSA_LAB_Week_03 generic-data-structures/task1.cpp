#include <iostream>
using namespace std;

template <typename Type>
class List
{
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    List(int maxSize = 10, int currentSize = 0)
    {
        if (maxSize <= 0)
            maxSize = 10;
        if (currentSize < 0 || currentSize > maxSize)
            currentSize = 0;
        this->maxSize = maxSize;
        this->currentSize = currentSize;
        arr = new Type[this->maxSize];
    }

    List(const List& other)
    {
        maxSize = other.maxSize;
        currentSize = other.currentSize;
        arr = new Type[maxSize];
        for (int i = 0; i < currentSize; i++)
            arr[i] = other.arr[i];
    }

    virtual ~List()
    {
        delete[] arr;
        arr = nullptr;
    }

    virtual void addElementAtFirstIndex(Type) = 0;
    virtual void addElementAtLastIndex(Type) = 0;
    virtual Type removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;
};

template <typename Type>
class MyList : public List<Type>
{
public:
    MyList(int maxSize = 10, int currentSize = 0) : List<Type>(maxSize, currentSize) {}

    MyList(const MyList& other) : List<Type>(other) {}

    virtual ~MyList() {}

    void addElementAtFirstIndex(Type value)
    {
        if (full())
        {
            cout << "List is full. Cannot add element.\n";
            return;
        }
        for (int i = this->currentSize; i > 0; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[0] = value;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type value)
    {
        if (full())
        {
            cout << "List is full. Cannot add element.\n";
            return;
        }
        this->arr[this->currentSize++] = value;
    }

    Type removeElementFromEnd()
    {
        if (empty())
        {
            cout << "List is empty. Nothing to remove.\n";
            return Type();
        }
        return this->arr[--this->currentSize];
    }

    void removeElementFromStart()
    {
        if (empty())
        {
            cout << "List is empty. Nothing to remove.\n";
            return;
        }
        for (int i = 0; i < this->currentSize - 1; i++)
            this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }

    bool empty() const { return this->currentSize == 0; }

    bool full() const { return this->currentSize == this->maxSize; }

    int size() const { return this->currentSize; }

    bool insertAt(int index, Type value)
    {
        if (index < 0 || index >= this->currentSize || full())
            return false;
        for (int i = this->currentSize; i > index; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    Type last() const
    {
        if (empty())
        {
            cout << "List is empty.\n";
            return Type();
        }
        return this->arr[this->currentSize - 1];
    }

    bool search(Type value) const
    {
        for (int i = 0; i < this->currentSize; i++)
            if (this->arr[i] == value)
                return true;
        return false;
    }

    void display() const
    {
        if (empty())
        {
            cout << "List is empty.\n";
            return;
        }
        cout << "[ ";
        for (int i = 0; i < this->currentSize; i++)
            cout << this->arr[i] << " ";
        cout << "]\n";
    }
};

template <typename Type>
class CustomList : public MyList<Type>
{
private:
    static bool isPrime(long long n)
    {
        if (n < 2)
            return false;
        for (long long i = 2; i * i <= n; i++)
            if (n % i == 0)
                return false;
        return true;
    }

    void rotateRightRange(int start, int len, int r)
    {
        if (len <= 1)
            return;
        r %= len;
        for (int k = 0; k < r; k++)
        {
            Type temp = this->arr[start + len - 1];
            for (int i = start + len - 1; i > start; i--)
                this->arr[i] = this->arr[i - 1];
            this->arr[start] = temp;
        }
    }

    void rotateLeftRange(int start, int len, int r)
    {
        if (len <= 1)
            return;
        r %= len;
        for (int k = 0; k < r; k++)
        {
            Type temp = this->arr[start];
            for (int i = start; i < start + len - 1; i++)
                this->arr[i] = this->arr[i + 1];
            this->arr[start + len - 1] = temp;
        }
    }

public:
    CustomList(int maxSize = 10, int currentSize = 0) : MyList<Type>(maxSize, currentSize) {}

    CustomList(const CustomList& other) : MyList<Type>(other) {}

    virtual ~CustomList() {}

    Type sum_ofPrime() const
    {
        Type sum = Type();
        for (int i = 0; i < this->currentSize; i++)
            if (isPrime((long long)this->arr[i]))
                sum += this->arr[i];
        return sum;
    }

    Type secondMaxEven() const
    {
        bool hasMax = false, hasSecond = false;
        Type max = Type(), second = Type();
        for (int i = 0; i < this->currentSize; i++)
        {
            Type v = this->arr[i];
            if ((long long)v % 2 != 0)
                continue;
            if (!hasMax || v > max)
            {
                if (hasMax) { second = max; hasSecond = true; }
                max = v;
                hasMax = true;
            }
            else if (v < max && (!hasSecond || v > second))
            {
                second = v;
                hasSecond = true;
            }
        }
        if (!hasSecond)
        {
            cout << "No second maximum even number exists.\n";
            return (Type)-1;
        }
        return second;
    }

    Type secondMinOdd() const
    {
        bool hasMin = false, hasSecond = false;
        Type min = Type(), second = Type();
        for (int i = 0; i < this->currentSize; i++)
        {
            Type v = this->arr[i];
            if ((long long)v % 2 == 0)
                continue;
            if (!hasMin || v < min)
            {
                if (hasMin) { second = min; hasSecond = true; }
                min = v;
                hasMin = true;
            }
            else if (v > min && (!hasSecond || v < second))
            {
                second = v;
                hasSecond = true;
            }
        }
        if (!hasSecond)
        {
            cout << "No second minimum odd number exists.\n";
            return (Type)-1;
        }
        return second;
    }

    void printDuplicates() const
    {
        bool found = false;
        cout << "Duplicates: ";
        for (int i = 0; i < this->currentSize; i++)
        {
            bool seenBefore = false;
            for (int j = 0; j < i; j++)
                if (this->arr[j] == this->arr[i]) { seenBefore = true; break; }
            if (seenBefore)
                continue;
            int count = 1;
            for (int j = i + 1; j < this->currentSize; j++)
                if (this->arr[j] == this->arr[i])
                    count++;
            if (count > 1)
            {
                cout << this->arr[i] << " ";
                found = true;
            }
        }
        if (!found)
            cout << "none";
        cout << "\n";
    }

    void rotateClockwaise(int r)
    {
        int half = this->currentSize / 2;
        rotateRightRange(0, half, r);
        rotateRightRange(half, this->currentSize - half, r);
    }

    void rotateanitclockwaise(int rt)
    {
        int half = this->currentSize / 2;
        rotateLeftRange(0, half, rt);
        rotateLeftRange(half, this->currentSize - half, rt);
    }
};

template <typename Type>
class DemoList : public List<Type>
{
public:
    DemoList(int m = 5) : List<Type>(m) {}
    void addElementAtFirstIndex(Type v)
    {
        if (this->currentSize == this->maxSize) return;
        for (int i = this->currentSize; i > 0; i--) this->arr[i] = this->arr[i - 1];
        this->arr[0] = v; this->currentSize++;
    }
    void addElementAtLastIndex(Type v)
    {
        if (this->currentSize == this->maxSize) return;
        this->arr[this->currentSize++] = v;
    }
    Type removeElementFromEnd() { return this->currentSize ? this->arr[--this->currentSize] : Type(); }
    void removeElementFromStart()
    {
        if (!this->currentSize) return;
        for (int i = 0; i < this->currentSize - 1; i++) this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }
    void print() const
    {
        for (int i = 0; i < this->currentSize; i++) cout << this->arr[i] << " ";
        cout << "\n";
    }
};

void runTask1()
{
    DemoList<int> d(5);
    List<int>* p = &d;
    p->addElementAtLastIndex(10);
    p->addElementAtLastIndex(20);
    p->addElementAtFirstIndex(5);
    cout << "List: "; d.print();
    cout << "Removed from end: " << p->removeElementFromEnd() << "\n";
    p->removeElementFromStart();
    cout << "After removing from start: "; d.print();
    DemoList<int> copy(d);
    copy.addElementAtLastIndex(99);
    cout << "Original: "; d.print();
    cout << "Copy:     "; copy.print();
}

void runTask2()
{
    int cap;
    cout << "Enter maximum size of the list: ";
    cin >> cap;
    MyList<int> list(cap);
    int choice, value, index;
    do
    {
        cout << "\n===== MyList Menu =====\n"
            << "1.  Add element at first index\n"
            << "2.  Add element at last index\n"
            << "3.  Remove element from end\n"
            << "4.  Remove element from start\n"
            << "5.  Check if list is empty\n"
            << "6.  Check if list is full\n"
            << "7.  Get current size\n"
            << "8.  Insert at index\n"
            << "9.  Get last element\n"
            << "10. Search a value\n"
            << "11. Display list\n"
            << "12. Test copy constructor\n"
            << "0.  Back\n"
            << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: cout << "Value: "; cin >> value; list.addElementAtFirstIndex(value); break;
        case 2: cout << "Value: "; cin >> value; list.addElementAtLastIndex(value); break;
        case 3:
            if (!list.empty()) cout << "Removed: " << list.removeElementFromEnd() << "\n";
            else list.removeElementFromEnd();
            break;
        case 4: list.removeElementFromStart(); break;
        case 5: cout << (list.empty() ? "List is empty\n" : "List is not empty\n"); break;
        case 6: cout << (list.full() ? "List is full\n" : "List is not full\n"); break;
        case 7: cout << "Size: " << list.size() << "\n"; break;
        case 8:
            cout << "Index: "; cin >> index;
            cout << "Value: "; cin >> value;
            cout << (list.insertAt(index, value) ? "Inserted successfully\n"
                : "Insertion failed (invalid index or list full)\n");
            break;
        case 9:
            if (!list.empty()) cout << "Last element: " << list.last() << "\n";
            else list.last();
            break;
        case 10: cout << "Value to search: "; cin >> value; cout << (list.search(value) ? "Found\n" : "Not found\n"); break;
        case 11: list.display(); break;
        case 12:
        {
            MyList<int> copy(list);
            copy.addElementAtLastIndex(-1);
            cout << "Original: "; list.display();
            cout << "Copy:     "; copy.display();
            break;
        }
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void runTask3()
{
    int cap;
    cout << "Enter maximum size of the list: ";
    cin >> cap;
    CustomList<int> list(cap);
    int choice, value, index, r;
    do
    {
        cout << "\n===== CustomList Menu =====\n"
            << "1.  Add element at first index\n"
            << "2.  Add element at last index\n"
            << "3.  Remove element from end\n"
            << "4.  Remove element from start\n"
            << "5.  Insert at index\n"
            << "6.  Search a value\n"
            << "7.  Get last element\n"
            << "8.  Size / empty / full\n"
            << "9.  Sum of prime numbers\n"
            << "10. Second maximum even number\n"
            << "11. Second minimum odd number\n"
            << "12. Print duplicates\n"
            << "13. Rotate halves clockwise\n"
            << "14. Rotate halves anti-clockwise\n"
            << "15. Display list\n"
            << "0.  Back\n"
            << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1: cout << "Value: "; cin >> value; list.addElementAtFirstIndex(value); break;
        case 2: cout << "Value: "; cin >> value; list.addElementAtLastIndex(value); break;
        case 3:
            if (!list.empty()) cout << "Removed: " << list.removeElementFromEnd() << "\n";
            else list.removeElementFromEnd();
            break;
        case 4: list.removeElementFromStart(); break;
        case 5:
            cout << "Index: "; cin >> index;
            cout << "Value: "; cin >> value;
            cout << (list.insertAt(index, value) ? "Inserted successfully\n"
                : "Insertion failed (invalid index or list full)\n");
            break;
        case 6: cout << "Value to search: "; cin >> value; cout << (list.search(value) ? "Found\n" : "Not found\n"); break;
        case 7:
            if (!list.empty()) cout << "Last element: " << list.last() << "\n";
            else list.last();
            break;
        case 8:
            cout << "Size: " << list.size() << ", Empty: " << (list.empty() ? "yes" : "no")
                << ", Full: " << (list.full() ? "yes" : "no") << "\n";
            break;
        case 9: cout << "Sum of primes: " << list.sum_ofPrime() << "\n"; break;
        case 10: { int v = list.secondMaxEven(); if (v != -1) cout << "Second max even: " << v << "\n"; break; }
        case 11: { int v = list.secondMinOdd(); if (v != -1) cout << "Second min odd: " << v << "\n"; break; }
        case 12: list.printDuplicates(); break;
        case 13: cout << "Number of rotations: "; cin >> r; list.rotateClockwaise(r); list.display(); break;
        case 14: cout << "Number of rotations: "; cin >> r; list.rotateanitclockwaise(r); list.display(); break;
        case 15: list.display(); break;
        case 0: break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main()
{
    int task;
    do
    {
        cout << "\n===== Generic Data Structures =====\n"
            << "1. Task 1 (abstract List demo)\n"
            << "2. Task 2 (MyList menu)\n"
            << "3. Task 3 (CustomList menu)\n"
            << "0. Exit\n"
            << "Choice: ";
        cin >> task;
        switch (task)
        {
        case 1: runTask1(); break;
        case 2: runTask2(); break;
        case 3: runTask3(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (task != 0);
    return 0;
}