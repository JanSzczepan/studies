#include <iostream>

using namespace std;

const int N = 10;

// O(n)
int linearSearch(const int numbers[], const int size, const int searchedNumber) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] == searchedNumber) {
            return i;
        }
    }
    return -1;
}

// O(lgn)
int binarySearch(const int numbers[], const int size, const int searchedNumber) {
    int start = 0, end = size - 1;
    while (start <= end) {
        int middle = (start + end) / 2;
        if (numbers[middle] == searchedNumber)
            return middle;
        else if (numbers[middle] < searchedNumber)
            start = middle + 1;
        else
            end = middle - 1;
    }
    return -1;
}

int main() {
    int numbers[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << binarySearch(numbers, N, 6);

    return 0;
}
