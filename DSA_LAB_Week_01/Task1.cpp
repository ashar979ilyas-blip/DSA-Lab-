
#include <iostream>
using namespace std;

template <class T>
void printArray(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool intLess(int a, int b) {
    return a < b;
}

bool textLess(const char* a, const char* b) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] < b[i];
        i++;
    }

    return a[i] < b[i];
}

template <class T>
void selectionSort(T arr[], int n, bool (*less)(T, T)) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (less(arr[j], arr[minIndex])) {
                minIndex = j;
            }
        }

        T temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int intArray[5] = { 64, 25, 12, 22, 11 };

    cout << "Original integer array: ";
    printArray(intArray, 5);

    selectionSort(intArray, 5, intLess);

    cout << "Sorted integer array: ";
    printArray(intArray, 5);

    const char* stringArray[4] = {
        "apple", "orange", "banana", "grape"
    };

    cout << "\nOriginal string array: ";
    printArray(stringArray, 4);

    selectionSort(stringArray, 4, textLess);

    cout << "Sorted string array: ";
    printArray(stringArray, 4);

    return 0;
}
