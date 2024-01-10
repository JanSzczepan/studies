#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

struct MatrixElement {
    double value;
    int rowIndex;
    int columnIndex;
};

const int N = 5;
const double X = 1.5;
const int M = 1;
const int D = 5;
const int LINE_INTERVAL = 2;
const string OUTPUT_FILE_NAME = "coDrugi.txt";

void getDivider() {
    cout << "-------------------------------" << endl;
}

void printData(vector<vector<double>> &A) {
    getDivider();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << fixed << setprecision(M) << setw(D) << A[i][j] << " ";
        cout << endl;
    }
    getDivider();
}

string getFileName() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    return fileName;
}

ifstream openFile() {
    string fileName = getFileName();

    ifstream file(fileName);

    while (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        fileName = getFileName();
        file.open(fileName);
    }

    return file;
}

void readDataFromFile(vector<vector<double>> &A, ifstream &file) {
    int i = 0;
    string line;
    while (getline(file, line) && i < N) {
        istringstream iss(line);
        int j = 0;
        string temp;
        while (iss >> temp && j < N) {
            A[i][j] = stod(temp);
            j++;
        }
        i++;
    }
}

MatrixElement findMaxValue(vector<vector<double>> &A) {
    double maxValue = numeric_limits<double>::lowest();;
    int rowIndex, columnIndex;
    int i = 0, j = 0;
    while (i < N && j < N) {
        if (A[i][j] > maxValue) {
            maxValue = A[i][j];
            rowIndex = i;
            columnIndex = j;
        }
        i++;
        j++;
    }
    return {maxValue, rowIndex, columnIndex};
}

double findMinValue(vector<vector<double>> &A) {
    double minValue = numeric_limits<double>::max();;
    int i2 = 0, j2 = N - 1;
    while (i2 < N && j2 < N) {
        if (A[i2][j2] < minValue)
            minValue = A[i2][j2];
        i2++;
        j2--;
    }
    return minValue;
}

void fillRowAndColumn(vector<vector<double>> &A, MatrixElement &maxValueElement) {
    auto [maxValue, maxValueRowIndex, maxValueColumnIndex] = maxValueElement;

    for (int i = 0; i < N; i++) {
        A[maxValueRowIndex][i] = maxValue;
        A[i][maxValueColumnIndex] = maxValue;
    }
}

void writeDataToFile(vector<vector<double>> &A, const string &fileName, int interval) {
    ofstream file(fileName);

    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return;
    }

    for (int i = 0; i < N; i += interval) {
        for (int j = 0; j < N; ++j)
            file << A[i][j] << " ";
        file << "\n";
    }
    file.close();

    cout << "Data written to file successfully" << endl;
}

int main() {
    auto file = openFile();

    vector<vector<double>> A(N, vector<double>(N, X));

    readDataFromFile(A, file);

    file.close();

    printData(A);

    auto maxValueElement = findMaxValue(A);
    auto minValue = findMinValue(A);

    fillRowAndColumn(A, maxValueElement);
    A[maxValueElement.rowIndex][maxValueElement.columnIndex] = minValue;

    printData(A);

    writeDataToFile(A, OUTPUT_FILE_NAME, LINE_INTERVAL);

    return 0;
}
