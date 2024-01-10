#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

const int W = 3;
const int K = 4;
const int SZ = 6;

template<size_t w, size_t k>
void fillWithRandomGrades(double (&grades)[w][k], const double min, const double max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);

    for (int i = 0; i < w; i++)
        for (int j = 0; j < k; j++)
            grades[i][j] = dis(gen);
}

template<size_t w, size_t k>
void printGrades(double (&grades)[w][k]) {
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < K; j++)
            cout << setw(SZ) << setprecision(1) << fixed << grades[i][j] << " ";
        cout << endl;
    }
}

template<size_t k>
void printAverages(double (&averages)[k]) {
    for (int i = 0; i < K; i++)
        cout << setw(SZ) << setprecision(2) << fixed << averages[i] << " ";
    cout << endl;
}

double getAverage(double sum, int count) {
    return sum / count;
}

template<size_t w, size_t k>
void calculateAverages(double (&grades)[w][k], double (&averages)[k]) {
    double sum = 0;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < W; j++)
            sum += grades[j][i];
        averages[i] = getAverage(sum, W);
        sum = 0;
    }
}

template<size_t w, size_t k>
void moveMaxAverageColumnToEnd(double (&grades)[w][k], double (&averages)[k]) {
    int maxIndex = distance(averages, max_element(averages, averages + k));
    for (int i = 0; i < w; i++) {
        swap(grades[i][maxIndex], grades[i][k - 1]);
    }
    swap(averages[maxIndex], averages[k - 1]);
}

template<size_t w, size_t k>
void printData(double (&grades)[w][k], double (&averages)[k]) {
    printGrades(grades);
    printAverages(averages);
}

int main() {
    double grades[W][K];

    const double MIN_GRADE = 0.0;
    const double MAX_GRADE = 5.0;
    fillWithRandomGrades<W, K>(grades, MIN_GRADE, MAX_GRADE);

    double averages[K];
    calculateAverages(grades, averages);

    printData(grades, averages);

    moveMaxAverageColumnToEnd(grades, averages);

    printData(grades, averages);

    return 0;
}
