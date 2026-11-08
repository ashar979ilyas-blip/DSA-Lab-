
#include <iostream>
using namespace std;

class Course {
public:
    virtual void duration() = 0;
};

class OnlineCourse : public Course {
private:
    int weeks;
    int hoursPerWeek;

public:
    OnlineCourse(int w, int h) {
        weeks = w;
        hoursPerWeek = h;
    }

    void duration() {
        cout << "Online Course Duration: "
            << weeks << " weeks" << endl;

        cout << "Total Hours: "
            << weeks * hoursPerWeek << endl;
    }
};

class OfflineCourse : public Course {
private:
    int months;
    int hoursPerDay;

public:
    OfflineCourse(int m, int h) {
        months = m;
        hoursPerDay = h;
    }

    void duration() {
        cout << "Offline Course Duration: "
            << months << " months" << endl;

        cout << "Total Hours (assuming 30 days per month): "
            << months * 30 * hoursPerDay << endl;
    }
};

int main() {
    OnlineCourse online(8, 3);
    OfflineCourse offline(2, 4);

    online.duration();
    cout << endl;
    offline.duration();

    return 0;
}
