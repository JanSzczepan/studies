#include <iostream>
#include <fstream>

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

void printElement(Book *&book) {
    cout << book->title << " by " << book->authorName << " " << book->authorSurname << endl;
}

void printList(Book *&head) {
    for (Book *book = head; book != nullptr; book = book->next)
        printElement(book);
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

void moveAndCreateListItem(Book *&head, Book &newBookData, ExclusionChars exclusionChars, const short moveInterval) {
    auto [charToAvoidInTitle, charToAvoidInAuthorsName] = exclusionChars;

    Book *current = head;
    Book *prev = nullptr;
    int index = 1;


    while (current != nullptr && current->next != nullptr) {
        if (index % moveInterval == 0 &&
            current->next->pagesCount % 2 == 0 &&
            current->next->authorName.find(charToAvoidInAuthorsName) == string::npos) {

            cout << "Book to be moved: " << current->next->title << endl;
            cout << "Enter element index: ";
            int userIndex;
            cin >> userIndex;

            if (current->next != nullptr && current->next->next == nullptr && userIndex >= index) {
                // Książka jest ostatnia, nie robimy nic
                prev = current;
                current = current->next;
                index++;
                continue;
            }

            // Specjalny przypadek dla 1 lub 2
            if (userIndex <= 2) {
                Book *toMove = current->next;
                current->next = toMove->next;
                toMove->next = head;
                head = toMove;
            } else {
                // Wyszukujemy miejsce do przeniesienia
                Book *movePrev = head;
                for (int i = 1; i < userIndex - 1 && movePrev->next != nullptr; i++) {
                    movePrev = movePrev->next;
                }

                // Jeśli doszliśmy do końca listy, przenosimy na koniec
                if (movePrev->next == nullptr) {
                    Book *toMove = current->next;
                    current->next = toMove->next;
                    movePrev->next = toMove;
                    toMove->next = nullptr;
                } else {
                    // Przenoszenie książki
                    Book *toMove = current->next;
                    current->next = toMove->next;
                    toMove->next = movePrev->next;
                    movePrev->next = toMove;
                }
            }

            // Aktualizacja wskaźników
            if (current == head) {
                current = head;
            } else {
                current = current->next;
            }
            printList(head);
        } else {
            prev = current;
            current = current->next;
            index++;
        }
    }
    cout << "---------------" << endl;

    current = head;
    Book *previous = nullptr;

    while (current != nullptr) {
        // Sprawdzenie, czy aktualna książka spełnia warunek do dodania nowej książki
        if (current->authorName.find(charToAvoidInAuthorsName) == std::string::npos && current->next != nullptr) {
            // Tworzenie nowego węzła z danymi z newBookData
            Book *newBook = new Book(newBookData);
            newBook->next = current->next;
            current->next = newBook;
            current = newBook->next; // Przeskoczenie nowo dodanej książki
        } else {
            current = current->next;
        }
    }

    printList(head);
}

int main() {
    string fileName;
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

    printList(head);

    Book b = Book{10, "TestTitle", "Test", "Test"};
    moveAndCreateListItem(head, b, {'q', 'a'}, 1);

    while (head != nullptr) {
        Book *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
