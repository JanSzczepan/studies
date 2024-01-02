#include <iostream>
#include <vector>

using namespace std;

void cleanCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<typename T>
T getNumber(const string &prompt, int min = INT_MIN) {
    T number;

    while (true) {
        cout << prompt;

        cin >> number;
        if (cin.fail() || number < min) {
            cout << (number < min ? ("Enter valid positive number bigger than or equal " + to_string(min) + "!")
                                  : "Enter valid positive number!") << endl;
            cleanCin();
        } else {
            if (cin.peek() != EOF)
                cleanCin();
            break;
        }
    }

    return number;
}

void readNumberIntoArray(vector<double> &arr, int i, const int n) {
    if (i < n) {
        arr[i] = getNumber<double>("Enter number (" + to_string(i + 1) + "): ");
        readNumberIntoArray(arr, ++i, n);
    }
}

void printNumber(vector<double> &numbers, int i, const int n) {
    if (i < n) {
        cout << "(" << i + 1 << "): " << numbers[i] << endl;
        printNumber(numbers, ++i, n);
    }
}

void reverse(vector<double> &arr, int start, int end) {
    if (start < end) {
        double temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        reverse(arr, ++start, --end);
    }
}

int main() {
    const int N = getNumber<int>("Enter const N: ", 3);
    vector<double> A(N);
    vector<double> B(N);

    cout << "A:" << endl;
    readNumberIntoArray(A, 0, N);
    cout << "B:" << endl;
    readNumberIntoArray(B, 0, N);

    reverse(A, 0, N - 1);
    reverse(B, 2, N - 1);

    cout << "A:" << endl;
    printNumber(A, 0, N);
    cout << "B:" << endl;
    printNumber(B, 0, N);

    return 0;
}
