
#include <iostream>
using namespace std;

bool textEqual(const char* a, const char* b) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return false;
        i++;
    }

    return a[i] == b[i];
}

template <class T>
int linearSearch(T arr[], int n, T key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }

    return -1;
}

int linearSearch(const char* arr[], int n, const char* key) {
    for (int i = 0; i < n; i++) {
        if (textEqual(arr[i], key)) {
            return i;
        }
    }

    return -1;
}

template <class T>
void printSearchResult(int index, T key) {
    if (index != -1) {
        cout << key << " found at index " << index << endl;
    }
    else {
        cout << key << " not found." << endl;
    }
}

int main() {
    int intArray[5] = { 64, 25, 12, 22, 11 };
    int intKey = 12;

    int intIndex = linearSearch(intArray, 5, intKey);
    printSearchResult(intIndex, intKey);

    float floatArray[4] = { 3.14, 2.71, 1.62, 0.57 };
    float floatKey = 1.62;

    int floatIndex = linearSearch(floatArray, 4, floatKey);
    printSearchResult(floatIndex, floatKey);

    const char* stringArray[4] = {
        "apple", "orange", "banana", "grape"
    };

    const char* stringKey = "banana";

    int stringIndex = linearSearch(stringArray, 4, stringKey);
    printSearchResult(stringIndex, stringKey);

    return 0;
}
