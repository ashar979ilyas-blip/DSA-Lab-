
#include <iostream>
using namespace std;

void copyText(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int compareText(const char a[], const char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }

    return a[i] - b[i];
}

class Publication {
public:
    virtual void display() = 0;
    virtual ~Publication() {}
};

class Book : public Publication {
private:
    char title[50];
    char author[50];
    int pages;

public:
    Book() {
        title[0] = '\0';
        author[0] = '\0';
        pages = 0;
    }

    Book(const char t[], const char a[], int p) {
        copyText(title, t);
        copyText(author, a);
        pages = p;
    }

    void display() {
        cout << "Book: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }

    int getPages() const {
        return pages;
    }

    bool matches(const char key[]) const {
        return compareText(title, key) == 0;
    }

    bool operator<(const Book& b) const {
        return pages < b.pages;
    }

    bool operator==(const Book& b) const {
        return pages == b.pages;
    }
};

class Newspaper : public Publication {
private:
    char name[50];
    char date[20];
    char edition[50];

public:
    Newspaper() {
        name[0] = '\0';
        date[0] = '\0';
        edition[0] = '\0';
    }

    Newspaper(const char n[], const char d[], const char e[]) {
        copyText(name, n);
        copyText(date, d);
        copyText(edition, e);
    }

    void display() {
        cout << "Newspaper: " << name << endl;
        cout << "Date: " << date << endl;
        cout << "Edition: " << edition << endl;
    }

    bool matches(const char key[]) const {
        return compareText(name, key) == 0;
    }

    bool operator<(const Newspaper& n) const {
        return compareText(edition, n.edition) < 0;
    }

    bool operator==(const Newspaper& n) const {
        return compareText(edition, n.edition) == 0;
    }
};

template <class T>
void selectionSort(T arr[], int n,
    bool (*before)(const T&, const T&)) {

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (before(arr[j], arr[minIndex])) {
                minIndex = j;
            }
        }

        T temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

bool bookOrder(const Book& a, const Book& b) {
    return a.getPages() < b.getPages();
}

bool newspaperOrder(const Newspaper& a, const Newspaper& b) {
    return a < b;
}

template <class T>
int linearSearch(T arr[], int n, const char key[],
    bool (T::* match)(const char[]) const) {

    for (int i = 0; i < n; i++) {
        if ((arr[i].*match)(key)) {
            return i;
        }
    }

    return -1;
}

template <class T>
int binarySearch(T arr[], int n, T key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;

        else if (arr[mid] < key)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}

class Library {
private:
    Book books[10];
    Newspaper newspapers[10];
    int bookCount;
    int newspaperCount;

public:
    Library() {
        bookCount = 0;
        newspaperCount = 0;
    }

    void addBook(Book b) {
        if (bookCount < 10) {
            books[bookCount] = b;
            bookCount++;
        }
    }

    void addNewspaper(Newspaper n) {
        if (newspaperCount < 10) {
            newspapers[newspaperCount] = n;
            newspaperCount++;
        }
    }

    void displayCollection() {
        cout << "\nBooks:\n";

        for (int i = 0; i < bookCount; i++) {
            books[i].display();
            cout << endl;
        }

        cout << "Newspapers:\n";

        for (int i = 0; i < newspaperCount; i++) {
            newspapers[i].display();
            cout << endl;
        }
    }

    void sortBooksByPages() {
        selectionSort(books, bookCount, bookOrder);
    }

    void sortNewspapersByEdition() {
        selectionSort(newspapers, newspaperCount,
            newspaperOrder);
    }

    Book* searchBookByTitle(const char title[]) {
        int index = linearSearch(
            books, bookCount, title, &Book::matches
        );

        if (index != -1)
            return &books[index];

        return nullptr;
    }

    Newspaper* searchNewspaperByName(const char name[]) {
        int index = linearSearch(
            newspapers, newspaperCount, name,
            &Newspaper::matches
        );

        if (index != -1)
            return &newspapers[index];

        return nullptr;
    }
};

int main() {
    Book book1("The Catcher in the Rye",
        "J.D. Salinger", 277);

    Book book2("To Kill a Mockingbird",
        "Harper Lee", 324);

    Newspaper newspaper1("Washington Post",
        "2024-10-13",
        "Morning Edition");

    Newspaper newspaper2("The Times",
        "2024-10-12",
        "Weekend Edition");

    Library library;

    library.addBook(book1);
    library.addBook(book2);
    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    cout << "Before Sorting:\n";
    library.displayCollection();

    library.sortBooksByPages();
    library.sortNewspapersByEdition();

    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    Book* foundBook =
        library.searchBookByTitle("The Catcher in the Rye");

    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    }
    else {
        cout << "\nBook not found.\n";
    }

    Newspaper* foundNewspaper =
        library.searchNewspaperByName("The Times");

    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    }
    else {
        cout << "\nNewspaper not found.\n";
    }

    return 0;
}
