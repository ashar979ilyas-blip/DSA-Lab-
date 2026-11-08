
#include <iostream>
using namespace std;

class Employee {
public:
    virtual double calculateSalary() = 0;
};

class FullTimeEmployee : public Employee {
private:
    double salary;

public:
    FullTimeEmployee(double s) {
        salary = s;
    }

    double calculateSalary() {
        return salary;
    }
};

class PartTimeEmployee : public Employee {
private:
    int hours;
    double rate;

public:
    PartTimeEmployee(int h, double r) {
        hours = h;
        rate = r;
    }

    double calculateSalary() {
        return hours * rate;
    }
};

int main() {
    FullTimeEmployee emp1(50000);
    PartTimeEmployee emp2(80, 500);

    cout << "Full Time Salary: "
        << emp1.calculateSalary() << endl;

    cout << "Part Time Salary: "
        << emp2.calculateSalary() << endl;

    return 0;
}
