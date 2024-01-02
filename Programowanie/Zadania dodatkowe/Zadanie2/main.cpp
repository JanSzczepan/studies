#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

struct UserInputData {
    int maxNegNumber;
    int increasingCount;
    double negTwoDigitAverage;
};

void cleanCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getNumber(const string &prompt) {
    int number;

    while (true) {
        cout << prompt;

        cin >> number;
        if (cin.fail()) {
            cout << "Enter valid number!" << endl;
            cleanCin();
        } else {
            if (cin.peek() != EOF)
                cleanCin();
            break;
        }
    }

    return number;
}

int getConstantD(const string &prompt) {
    while (true) {
        int number = getNumber(prompt);

        if (number == 0)
            cout << "Enter an integer other than zero!" << endl;
        else
            return number;
    }
}

bool isMaxNegNumber(int number, int maxNegNumber) {
    return (number < 0 && number > maxNegNumber);
}

bool isNegTwoDigit(int number) {
    return (number < -9 && number > -100);
}

bool isInputIncreased(int prev, int current) {
    return (current > prev);
}

bool isDivisible(int dividend, int divider) {
    return (dividend % divider == 0);
}

bool isBreakCondition(int number, const int D) {
    return (isDivisible(number, 2) && isDivisible(number, D));
}

double calculateAverage(int sum, int count) {
    if (count == 0)
        return numeric_limits<double>::quiet_NaN();
    return static_cast<double>(sum) / count;
}

void printData(int maxNegNumber, double average, int increasingCount) {
    if (maxNegNumber != INT_MIN)
        cout << "Maximum negative number: " << maxNegNumber << endl;
    else
        cout << "No negative numbers..." << endl;
    if (!isnan(average))
        cout << "Arithmetic mean of negative two-digit numbers: " << average << endl;
    cout << "Number of increasing inputs: " << increasingCount << endl;
}

UserInputData collectUserInputData() {
    const int D = getConstantD("Enter constant D: ");
    int maxNegNumber = INT_MIN;
    int negTwoDigitSum = 0;
    int negTwoDigitCount = 0;
    int previousValue;
    int currentValue = 0;
    int increasingCount = 0;

    while (true) {
        previousValue = currentValue;
        currentValue = getNumber("Enter integer: ");

        if (isMaxNegNumber(currentValue, maxNegNumber))
            maxNegNumber = currentValue;

        if (isNegTwoDigit(currentValue)) {
            negTwoDigitSum += currentValue;
            negTwoDigitCount++;
        }

        if (isInputIncreased(previousValue, currentValue))
            increasingCount++;

        if (isBreakCondition(currentValue, D))
            break;
    }

    return {maxNegNumber, increasingCount, calculateAverage(negTwoDigitSum, negTwoDigitCount)};
}

int main() {
    auto [maxNegNumber, increasingCount, negTwoDigitAverage] = collectUserInputData();
    printData(maxNegNumber, negTwoDigitAverage, increasingCount);

    return 0;
}
