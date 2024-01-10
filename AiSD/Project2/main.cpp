#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Book {
    int pagesCount = 0;
    string title;
    string authorName;
    string authorSurname;
    Book *next{};
};

struct ExclusionChars {
    char charToAvoidInTitle;
    char charToAvoidInAuthorsName;
};

const int LIST_START_INDEX = 1;
const int MOVE_BOOK_INTERVAL = 2;
const char CHAR_TO_AVOID_IN_TITLE = 'q';
const char CHAR_TO_AVOID_IN_AUTHORS_NAME = 'J';

void getDivider() {
    cout << "----------------" << endl;
}

void printElement(Book *&book) {
    cout << book->title << " by " << book->authorName << " " << book->authorSurname << endl;
}

void printList(Book *&head, const string &prompt) {
    if (head == nullptr) return;

    cout << prompt << endl;
    getDivider();
    for (Book *book = head; book != nullptr; book = book->next)
        printElement(book);
    getDivider();
}

void addBookToList(Book *&head, Book &book) {
    auto [pagesCount, title, authorsName, authorsSurname, next] = book;
    Book *newBook = new Book{pagesCount, title, authorsName, authorsSurname, next};

    if (head == nullptr) {
        head = newBook;
    } else {
        Book *current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newBook;
    }
}

template<typename T>
void removeElement(T *&head, T *elementToRemove) {
    if (head == nullptr || elementToRemove == nullptr) return;

    if (elementToRemove == head) {
        head = head->next;
        return;
    }

    T *temp = head;
    while (temp != nullptr && temp->next != elementToRemove) {
        temp = temp->next;
    }

    if (temp != nullptr) {
        temp->next = elementToRemove->next;
    }
}

template<typename T>
void insertElement(T *&head, T *elementToInsert, int position) {
    if (elementToInsert == nullptr) return;

    if (position <= LIST_START_INDEX || head == nullptr) {
        elementToInsert->next = head;
        head = elementToInsert;
        return;
    }

    T *temp = head;
    for (int i = LIST_START_INDEX; i < position - 1 && temp->next != nullptr; i++) {
        temp = temp->next;
    }
    elementToInsert->next = temp->next;
    temp->next = elementToInsert;
}

template<typename T>
void moveElement(T *&head, T *elementToMove, int newPosition) {
    if (elementToMove == nullptr) return;

    removeElement<T>(head, elementToMove);
    insertElement<T>(head, elementToMove, newPosition - 1);
}

void moveAndCreateListItem(Book *&head, Book &newBook, ExclusionChars exclusionChars, const short moveInterval) {
    auto isBookToMove = [moveInterval, exclusionChars](Book *book, int &movedBooksCount) -> bool {
        bool isEvenNumberOfPages = book->pagesCount % 2 == 0;
        bool isTitleWithoutExcludedChar = book->title.find(exclusionChars.charToAvoidInTitle) == string::npos;
        bool isDividendByInterval = movedBooksCount % moveInterval == 0;

        if (isEvenNumberOfPages && isTitleWithoutExcludedChar)
            movedBooksCount++;

        return (isDividendByInterval && isEvenNumberOfPages && isTitleWithoutExcludedChar);
    };

    Book *current = head;
    int movedBooksCount = 0;
    while (current != nullptr) {
        Book *next = current->next;

        if (isBookToMove(current, movedBooksCount)) {
            cout << "Book to be moved: " << current->title << endl;
            cout << "Enter element index: ";
            int userIndex;
            cin >> userIndex;
            moveElement(head, current, userIndex);
            printList(head, "Book moved:");
        }

        current = next;
    }

    auto isNewBookToAdd = [exclusionChars](Book *current) -> bool {
        return current->authorName.find(exclusionChars.charToAvoidInAuthorsName) == string::npos;
    };

    current = head;
    int index = LIST_START_INDEX;
    while (current != nullptr) {
        Book *next = current->next;
        if (isNewBookToAdd(current)) {
            auto [pagesCount, title, authorsName, authorsSurname, n] = newBook;
            Book *newBookPtr = new Book{pagesCount, title, authorsName, authorsSurname, n};
            insertElement<Book>(head, newBookPtr, index);
            index++;
        }
        current = next;
        index++;
    }
    printList(head, "New book(s) added:");
}

int main() {
    string fileName = "data.csv";
    cout << "Enter file name: ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file) {
        cerr << "Cannot open file!" << endl;
        return 1;
    }

    Book *head = nullptr;
    Book book;
    string pagesCount;
    while (getline(file, book.title, ',') &&
           getline(file, pagesCount, ',') &&
           getline(file, book.authorName, ',') &&
           getline(file, book.authorSurname)) {
        book.pagesCount = stoi(pagesCount);
        addBookToList(head, book);
    }

    file.close();

    Book newBook;
    cout << "Enter data about new book:" << endl;
    cout << "Title: ";
    cin >> newBook.title;
    cout << "Number of pages: ";
    cin >> newBook.pagesCount;
    cout << "Author's name: ";
    cin >> newBook.authorName;
    cout << "Author's surname: ";
    cin >> newBook.authorSurname;

    printList(head, "Initial list of books:");

    moveAndCreateListItem(head, newBook, {CHAR_TO_AVOID_IN_TITLE, CHAR_TO_AVOID_IN_AUTHORS_NAME}, MOVE_BOOK_INTERVAL);

    while (head != nullptr) {
        Book *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
