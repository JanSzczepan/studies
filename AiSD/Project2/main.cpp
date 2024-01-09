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

    for (Book *current = head; current != nullptr; current = current->next)
        cout << current->title << " by " << current->authorName << " " << current->authorSurname << endl;

    while (head != nullptr) {
        Book *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
