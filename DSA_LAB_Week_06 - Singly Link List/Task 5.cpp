#include <iostream>
using namespace std;

class Node {
public:
    int studentID;
    int priority;
    Node* next;

    Node(int id, int p) {
        studentID = id;
        priority = p;
        next = nullptr;
    }
};

class ReservationQueue {
private:
    Node* head;

public:
  
    ReservationQueue() {
        head = nullptr;
    }

    void AddStudent(int id, int p) {
        if (p < 1 || p > 3) {
            cout << "Invalid priority!" << endl;
            return;
        }

        Node* newNode = new Node(id, p);

        if (head == nullptr || p < head->priority) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* temp = head;

            while (temp->next != nullptr &&
                temp->next->priority <= p) {
                temp = temp->next;
            }

            newNode->next = temp->next;
            temp->next = newNode;
        }

        cout << "Student " << id
            << " added successfully." << endl;
    }

    void RemoveStudent(int id) {
        if (head == nullptr) {
            cout << "Reservation list is empty!" << endl;
            return;
        }

        Node* temp = head;

        if (head->studentID == id) {
            head = head->next;
            delete temp;

            cout << "Student " << id
                << " reservation cancelled." << endl;
            return;
        }

        while (temp->next != nullptr &&
            temp->next->studentID != id) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Student not found!" << endl;
            return;
        }

        Node* del = temp->next;
        temp->next = del->next;

        delete del;

        cout << "Student " << id
            << " reservation cancelled." << endl;
    }

    void UpdatePriority(int id, int newPriority) {
        if (newPriority < 1 || newPriority > 3) {
            cout << "Invalid priority!" << endl;
            return;
        }

        Node* temp = head;

        while (temp != nullptr &&
            temp->studentID != id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student not found!" << endl;
            return;
        }

        int oldID = temp->studentID;

        RemoveStudent(id);

        AddStudent(oldID, newPriority);

        cout << "Priority updated successfully." << endl;
    }

    void Display() {
        if (head == nullptr) {
            cout << "No reservations available." << endl;
            return;
        }

        Node* temp = head;

        cout << "Reservation Queue:" << endl;

        while (temp != nullptr) {
            cout << "Student ID: " << temp->studentID
                << " | Priority: ";

            if (temp->priority == 1)
                cout << "Research";
            else if (temp->priority == 2)
                cout << "Assignment";
            else
                cout << "Casual";

            cout << endl;

            temp = temp->next;
        }
    }

    void CountStudents() {
        int count = 0;
        Node* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        cout << "Total students: " << count << endl;
    }

   
    void BookReturned() {
        if (head == nullptr) {
            cout << "No student waiting for this book."
                << endl;
            return;
        }

        Node* temp = head;

        cout << "Book issued to Student ID: "
            << temp->studentID << endl;

        head = head->next;

        delete temp;
    }

  
    ~ReservationQueue() {
        Node* temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Library {
private:
    ReservationQueue book1;
    ReservationQueue book2;

public:
 
    void AddReservation(int book, int id, int p) {
        if (book == 1)
            book1.AddStudent(id, p);
        else if (book == 2)
            book2.AddStudent(id, p);
        else
            cout << "Invalid book number!" << endl;
    }

    void CancelReservation(int book, int id) {
        if (book == 1)
            book1.RemoveStudent(id);
        else if (book == 2)
            book2.RemoveStudent(id);
        else
            cout << "Invalid book number!" << endl;
    }

    void UpdateReservation(int book, int id, int p) {
        if (book == 1)
            book1.UpdatePriority(id, p);
        else if (book == 2)
            book2.UpdatePriority(id, p);
        else
            cout << "Invalid book number!" << endl;
    }

    void DisplayBook(int book) {
        if (book == 1)
            book1.Display();
        else if (book == 2)
            book2.Display();
        else
            cout << "Invalid book number!" << endl;
    }

    void CountBook(int book) {
        if (book == 1)
            book1.CountStudents();
        else if (book == 2)
            book2.CountStudents();
        else
            cout << "Invalid book number!" << endl;
    }

    void ReturnBook(int book) {
        if (book == 1)
            book1.BookReturned();
        else if (book == 2)
            book2.BookReturned();
        else
            cout << "Invalid book number!" << endl;
    }
};

int main() {
    Library lib;

    int choice, book, id, priority;

    do {
        cout << "\n===== UNIVERSITY LIBRARY SYSTEM =====" << endl;

        cout << "1. Add Student Reservation" << endl;
        cout << "2. Cancel Reservation" << endl;
        cout << "3. Update Student Priority" << endl;
        cout << "4. Display Reservation Queue" << endl;
        cout << "5. Count Students" << endl;
        cout << "6. Return Book / Issue to Student" << endl;
        cout << "7. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter Book Number (1 or 2): ";
            cin >> book;

            cout << "Enter Student ID: ";
            cin >> id;

            cout << "Enter Priority (1=Research, "
                << "2=Assignment, 3=Casual): ";
            cin >> priority;

            lib.AddReservation(book, id, priority);
            break;

        case 2:
            cout << "Enter Book Number: ";
            cin >> book;

            cout << "Enter Student ID: ";
            cin >> id;

            lib.CancelReservation(book, id);
            break;

        case 3:
            cout << "Enter Book Number: ";
            cin >> book;

            cout << "Enter Student ID: ";
            cin >> id;

            cout << "Enter New Priority: ";
            cin >> priority;

            lib.UpdateReservation(book, id, priority);
            break;

        case 4:
            cout << "Enter Book Number: ";
            cin >> book;

            lib.DisplayBook(book);
            break;

        case 5:
            cout << "Enter Book Number: ";
            cin >> book;

            lib.CountBook(book);
            break;

        case 6:
            cout << "Enter Returned Book Number: ";
            cin >> book;

            lib.ReturnBook(book);
            break;

        case 7:
            cout << "Exiting Library System..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}
