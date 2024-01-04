#include <iostream>
#include <random>

using namespace std;

struct NumberWithSign {
    int number;
    char sign;
};

const int N = 3;

int main() {
    NumberWithSign Z[N];

    for (int i = 0; i < N; i++) {
        cout << "Number (" << i + 1 << "): ";
        cin >> Z[i].number;
        cout << "Sign (" << i + 1 << "): ";
        cin >> Z[i].sign;
    }

    auto printNumberWithSignArray = [](NumberWithSign *arr, const int arrSize, const string &prompt) -> void {
        cout << prompt << endl;
        for (int i = 0; i < arrSize; i++) {
            cout << "Record (" << i + 1 << "):" << endl;
            cout << "Number: " << arr[i].number << endl;
            cout << "Sign: " << arr[i].sign << endl;
        }
    };

    printNumberWithSignArray(Z, N, "Z array:");

    int a = 8, b = 10;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(a, b);

    int randNumber = dis(gen);
    cout << "Random number: " << randNumber << endl;

    int filteredRecordsArraySize = 0;
    int remainingRecordsArraySize = 0;
    auto checkIsEligible = [randNumber](NumberWithSign record) -> bool {
        return islower(record.sign) && record.number > randNumber;
    };

    for (auto record: Z) {
        if (checkIsEligible(record))
            filteredRecordsArraySize++;
        else
            remainingRecordsArraySize++;
    }

    auto *filteredRecordsArray = new NumberWithSign[filteredRecordsArraySize];
    auto *remainingRecordsArray = new NumberWithSign[remainingRecordsArraySize];

    int filteredIndex = 0;
    int remainingIndex = 0;
    for (auto record: Z) {
        if (checkIsEligible(record)) {
            filteredRecordsArray[filteredIndex] = record;
            filteredIndex++;
        } else {
            remainingRecordsArray[remainingIndex] = record;
            remainingIndex++;
        }
    }

    printNumberWithSignArray(filteredRecordsArray, filteredRecordsArraySize, "Filtered records array:");
    printNumberWithSignArray(remainingRecordsArray, remainingRecordsArraySize, "Remaining records array:");

    delete[] filteredRecordsArray;
    delete[] remainingRecordsArray;

    return 0;
}