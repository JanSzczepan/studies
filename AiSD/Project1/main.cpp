#include <iostream>
#include <random>

using namespace std;

struct Book {
    int pagesCount = 0;
    string title;
    string authorName;
    string authorSurname;
    Book *next{};
};

const int N = 6;

void getDivider() {
    cout << "-------------------" << endl;
}

void printBooks(Book *ptr) {
    int count = 1;
    while (ptr != nullptr) {
        cout << "Book (" << count << "):" << endl;
        cout << "Title: " << ptr->title << endl;
        cout << "Number of pages: " << ptr->pagesCount << endl;
        cout << "Author's name: " << ptr->authorName << endl;
        cout << "Author's surname: " << ptr->authorSurname << endl;
        ptr = ptr->next;
        count++;
    }
    if (count > 1) getDivider();
}

int main() {
    Book *head = nullptr;
    Book *current;

    for (int i = 0; i < N; i++) {
        current = new Book;
        cout << "Book (" << i + 1 << "/" << N << "):" << endl;
        cout << "Title: ";
        cin >> current->title;
        cout << "Number of pages: ";
        cin >> current->pagesCount;
        cout << "Author's name: ";
        cin >> current->authorName;
        cout << "Author's surname: ";
        cin >> current->authorSurname;
        current->next = head;
        head = current;
    }
    getDivider();

    printBooks(head);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, N);
    int randNumOfBooks = dis(gen);
    cout << "Number of books to delete: " << randNumOfBooks << endl;

    char charInTitle;
    cout << "Enter a character in the title of books that need to be removed: ";
    cin >> charInTitle;
    getDivider();

    auto isBookToDelete = [charInTitle](Book *ptr, const int prevPagesCount) -> bool {
        return (ptr->title.find(charInTitle) != string::npos && ptr->pagesCount > prevPagesCount);
    };
    Book *deleteHead = head;
    Book *prevBook = new Book;
    int prevPagesCount = 0;
    int i = 0;
    while (i < randNumOfBooks && deleteHead != nullptr) {
        current = deleteHead;

        if (isBookToDelete(current, prevPagesCount)) {
            if (head == current) {
                deleteHead = head->next;
                head = head->next;
            } else {
                prevBook->next = deleteHead->next;
                deleteHead = deleteHead->next;
            }

            prevPagesCount = current->pagesCount;
            cout << "Deleting Book: " << current->title << endl;
            delete current;
            i++;
        } else {
            prevBook = current;
            prevPagesCount = current->pagesCount;
            deleteHead = deleteHead->next;
        }
    }
    getDivider();

    printBooks(head);

    while (head != nullptr) {
        current = head;
        head = head->next;
        cout << "Final deleting Book: " << current->title << endl;
        delete current;
    }

    printBooks(head);

    return 0;
}
