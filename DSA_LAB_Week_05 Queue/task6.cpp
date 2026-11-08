
#include <iostream>
#include <string>
using namespace std;

class Queue
{
private:
    struct Package
    {
        int id;
        string address;
        int startTime;
        int endTime;
        Package* next;
    };

    Package* frontNode;
    Package* rear;

    int convertTime(int time)
    {
        int hours = time / 100;
        int minutes = time % 100;

        if (hours < 0 || hours > 23 ||
            minutes < 0 || minutes > 59)
            return -1;

        return hours * 60 + minutes;
    }

public:
    Queue()
    {
        frontNode = NULL;
        rear = NULL;
    }

    void enqueue(int id, string address,
        int start, int end)
    {
        int s = convertTime(start);
        int e = convertTime(end);

        if (s == -1 || e == -1 || s > e)
        {
            cout << "Invalid Delivery Time!" << endl;
            return;
        }

        Package* temp = frontNode;

        while (temp != NULL)
        {
            if (temp->id == id)
            {
                cout << "Package ID Already Exists!" << endl;
                return;
            }

            temp = temp->next;
        }

        Package* newNode = new Package;

        newNode->id = id;
        newNode->address = address;
        newNode->startTime = start;
        newNode->endTime = end;
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

        cout << "Package Added Successfully." << endl;
    }

    void dequeue()
    {
        if (frontNode == NULL)
        {
            cout << "No Packages Available!" << endl;
            return;
        }

        Package* temp = frontNode;

        cout << "Package Delivered. ID: "
            << temp->id << endl;

        frontNode = frontNode->next;

        if (frontNode == NULL)
            rear = NULL;

        delete temp;
    }

    void front()
    {
        if (frontNode == NULL)
        {
            cout << "No Packages Available!" << endl;
            return;
        }

        cout << "\nNext Package Details:\n";
        cout << "ID: " << frontNode->id << endl;
        cout << "Address: " << frontNode->address << endl;
        cout << "Start Time: " << frontNode->startTime << endl;
        cout << "End Time: " << frontNode->endTime << endl;
    }

    void display()
    {
        if (frontNode == NULL)
        {
            cout << "No Pending Packages!" << endl;
            return;
        }

        Package* temp = frontNode;

        cout << "\nPending Packages:\n";

        while (temp != NULL)
        {
            cout << "\nPackage ID: " << temp->id;
            cout << "\nAddress: " << temp->address;
            cout << "\nStart Time: " << temp->startTime;
            cout << "\nEnd Time: " << temp->endTime;
            cout << endl;

            temp = temp->next;
        }
    }

    bool timeToDeliver(int currentTime)
    {
        if (frontNode == NULL)
        {
            cout << "No Packages Available!" << endl;
            return false;
        }

        int current = convertTime(currentTime);

        if (current == -1)
        {
            cout << "Invalid Current Time!" << endl;
            return false;
        }

        int start = convertTime(frontNode->startTime);
        int end = convertTime(frontNode->endTime);

        if (current > end)
        {
            cout << "Package " << frontNode->id
                << " has Expired!" << endl;

            Package* temp = frontNode;
            frontNode = frontNode->next;

            if (frontNode == NULL)
                rear = NULL;

            delete temp;

            return false;
        }

        if (current < start)
        {
            cout << "Delivery Time Has Not Started Yet!" << endl;
            return false;
        }

        cout << "Package Can Be Delivered On Time." << endl;

        return true;
    }

    void processPackage(int currentTime)
    {
        if (timeToDeliver(currentTime))
        {
            dequeue();
        }
    }

    ~Queue()
    {
        while (frontNode != NULL)
        {
            Package* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }
};

int main()
{
    Queue q;

    int choice, id, start, end, currentTime;
    string address;

    do
    {
        cout << "\n1. Add Package";
        cout << "\n2. Process Package";
        cout << "\n3. Check Front Package";
        cout << "\n4. Display Packages";
        cout << "\n5. Check Delivery Time";
        cout << "\n0. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter Package ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Recipient Address: ";
            getline(cin, address);

            cout << "Enter Start Time (HHMM): ";
            cin >> start;

            cout << "Enter End Time (HHMM): ";
            cin >> end;

            q.enqueue(id, address, start, end);
            break;

        case 2:
            cout << "Enter Current Time (HHMM): ";
            cin >> currentTime;

            q.processPackage(currentTime);
            break;

        case 3:
            q.front();
            break;

        case 4:
            q.display();
            break;

        case 5:
            cout << "Enter Current Time (HHMM): ";
            cin >> currentTime;

            q.timeToDeliver(currentTime);
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
