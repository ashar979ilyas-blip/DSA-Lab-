
#include <iostream>
using namespace std;

class myCarStack
{
private:
    int cars[8];
    int topIndex;

public:
    myCarStack()
    {
        topIndex = -1;
    }

    bool isEmpty()
    {
        return topIndex == -1;
    }

    bool isFull()
    {
        return topIndex == 7;
    }

    void push(int carNumber)
    {
        if (isFull())
        {
            cout << "Parking lot is full.\n";
        }
        else
        {
            topIndex++;
            cars[topIndex] = carNumber;
            cout << "Car parked successfully.\n";
        }
    }

    int pop()
    {
        if (isEmpty())
            return -1;

        int carNumber = cars[topIndex];
        topIndex--;
        return carNumber;
    }

    int top()
    {
        if (isEmpty())
            return -1;

        return cars[topIndex];
    }

    int count()
    {
        return topIndex + 1;
    }

    bool search(int carNumber)
    {
        for (int i = 0; i <= topIndex; i++)
        {
            if (cars[i] == carNumber)
                return true;
        }

        return false;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No cars are parked.\n";
            return;
        }

        cout << "Parked cars (top to bottom): ";

        for (int i = topIndex; i >= 0; i--)
        {
            cout << cars[i] << " ";
        }

        cout << endl;
    }

    bool removeCar(int carNumber)
    {
        if (!search(carNumber))
            return false;

        myCarStack temp;

        while (top() != carNumber)
        {
            temp.push(pop());
        }

        pop();

        while (!temp.isEmpty())
        {
            push(temp.pop());
        }

        return true;
    }
};

int main()
{
    myCarStack parking;
    int choice, carNumber;

    do
    {
        cout << "\n--- PARKING LOT MENU ---\n";
        cout << "1. Park a new car\n";
        cout << "2. Remove a car by car number\n";
        cout << "3. View parked cars\n";
        cout << "4. Show total cars parked\n";
        cout << "5. Show car currently at the top\n";
        cout << "6. Search for a car\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter car number: ";
            cin >> carNumber;

            if (parking.search(carNumber))
                cout << "This car is already parked.\n";
            else
                parking.push(carNumber);

            break;

        case 2:
            cout << "Enter car number to remove: ";
            cin >> carNumber;

            if (parking.removeCar(carNumber))
                cout << "Car removed successfully.\n";
            else
                cout << "Car not found.\n";

            break;

        case 3:
            parking.display();
            break;

        case 4:
            cout << "Total cars parked: "
                << parking.count() << endl;
            break;

        case 5:
            if (parking.isEmpty())
                cout << "Parking lot is empty.\n";
            else
                cout << "Top car: " << parking.top() << endl;

            break;

        case 6:
            cout << "Enter car number to search: ";
            cin >> carNumber;

            if (parking.search(carNumber))
                cout << "Car is present.\n";
            else
                cout << "Car is not present.\n";

            break;

        case 7:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
