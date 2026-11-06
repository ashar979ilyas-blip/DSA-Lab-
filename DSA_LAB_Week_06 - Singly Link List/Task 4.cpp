#include <iostream>
using namespace std;

class Node {
public:
    int patientID;
    Node* next;

    Node(int id) {
        patientID = id;
        next = nullptr;
    }
};

class HospitalQueue {
private:
    Node* head;

public:
    // Constructor
    HospitalQueue() {
        head = nullptr;
    }

    // Add patient at the end
    void AddPatient(int id) {
        Node* newNode = new Node(id);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;

            while (temp->next != nullptr) {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        cout << "Patient added successfully!" << endl;
    }

    // Remove patient by ID
    void RemovePatient(int id) {
        if (head == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node* temp = head;

        // Delete first node
        if (head->patientID == id) {
            head = head->next;
            delete temp;

            cout << "Patient cancelled successfully!" << endl;
            return;
        }

        // Search for patient
        while (temp->next != nullptr &&
            temp->next->patientID != id) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Patient not found!" << endl;
            return;
        }

        Node* del = temp->next;
        temp->next = del->next;

        delete del;

        cout << "Patient cancelled successfully!" << endl;
    }

    // Display patient queue
    void DisplayPatients() {
        if (head == nullptr) {
            cout << "No patients in queue!" << endl;
            return;
        }

        Node* temp = head;

        cout << "Patient Queue: ";

        while (temp != nullptr) {
            cout << temp->patientID << " -> ";
            temp = temp->next;
        }

        cout << "NULL" << endl;
    }

    // Count total patients
    void CountPatients() {
        int count = 0;
        Node* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        cout << "Total patients: " << count << endl;
    }

    // Destructor
    ~HospitalQueue() {
        Node* temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    HospitalQueue hospital;

    int choice, id;

    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Remove Patient (Cancel)" << endl;
        cout << "3. Display Patients" << endl;
        cout << "4. Count Patients" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter Patient ID: ";
            cin >> id;
            hospital.AddPatient(id);
            break;

        case 2:
            cout << "Enter Patient ID to cancel: ";
            cin >> id;
            hospital.RemovePatient(id);
            break;

        case 3:
            hospital.DisplayPatients();
            break;

        case 4:
            hospital.CountPatients();
            break;

        case 5:
            cout << "Program terminated." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
