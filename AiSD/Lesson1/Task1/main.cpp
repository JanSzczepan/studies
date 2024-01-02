#include <iostream>
#include <vector>

using namespace std;

void cleanCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<typename T>
T getNumber(const string &prompt, bool isPositive = false) {
    T number;

    while (true) {
        cout << prompt;

        cin >> number;
        if (cin.fail() || (isPositive && number < 0)) {
            cout << "Enter valid positive number!" << endl;
            cleanCin();
        } else {
            if (cin.peek() != EOF)
                cleanCin();
            break;
        }
    }

    return number;
}

void readNumberIntoArray(vector<double> &numbers, int i, const int n) {
    if (i < n) {
        numbers[i] = getNumber<double>("Enter number (" + to_string(i + 1) + "): ");
        readNumberIntoArray(numbers, ++i, n);
    }
}

void printNumber(vector<double> &numbers, int i, const int n) {
    if (i < n) {
        cout << numbers[i] << endl;
        printNumber(numbers, ++i, n);
    }
}

int main() {
    const int N = getNumber<int>("Enter const N: ");
    vector<double> numbers(N);
    readNumberIntoArray(numbers, 0, N);
    printNumber(numbers, 0, N);

    return 0;
}