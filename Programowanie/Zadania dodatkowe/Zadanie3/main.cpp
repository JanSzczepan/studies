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

int getConst(const int min, const int max) {
    int number;

    do number = getNumber<int>("Enter integer between " + to_string(min) + " and " + to_string(max) + ": ", true);
    while (!(number > min && number < max));

    return number;
}

int countStringsStartingWithCapital(int stringCount) {
    int upperCaseStartCount = 0;
    string str;

    for (int i = 0; i < stringCount; i++) {
        cout << "Enter string (" << i + 1 << "/" << stringCount << "): ";
        cin >> str;
        if (isupper(str[0]))
            upperCaseStartCount++;
    }

    return upperCaseStartCount;
}

void printCountOfStringsStartingWithCapital() {
    const int K = getConst(getNumber<int>("Const D: ", true), getNumber<int>("Const G: ", true));
    int upperCaseStartCount = countStringsStartingWithCapital(K);
    cout << "Number of strings starting with a capital letter: " << upperCaseStartCount << endl;
}

double calculateAverage(vector<double> &numbers) {
    double sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        auto number = getNumber<double>("Enter number (" + to_string(i + 1) + "/" + to_string(numbers.size()) + "): ");
        numbers[i] = number;
        sum += number;
    }
    return (sum / static_cast<double>(numbers.size()));
}

int calculateCountAboveAverage(vector<double> &numbers, double average) {
    int aboveAverageCount = 0;
    for (auto number: numbers)
        if (number > average)
            aboveAverageCount++;
    return aboveAverageCount;
}

void printAverageAndCountAboveAverage() {
    const int N = getNumber<int>("Const N: ", true);
    vector<double> numbers(N);

    auto average = calculateAverage(numbers);

    cout << "Average: " << average << endl;
    cout << "Number of numbers above average: " << calculateCountAboveAverage(numbers, average) << endl;
}

int main() {
    printCountOfStringsStartingWithCapital();
    printAverageAndCountAboveAverage();

    return 0;
}
