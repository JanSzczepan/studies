#include <iostream>
#include <cstring>

using namespace std;

// best case: O(n)
// worst case: O(m*(n-m+1))
int naiveAlgorithmSearch(const char *pat, const char *txt) {
    auto M = strlen(pat);
    auto N = strlen(txt);

    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;
        if (j == M)
            return i;
    }
    return -1;
}

void computeLPSArray(const char *pat, const size_t M, int *lps) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[len] == pat[i]) {
            len++;
            lps[i] = len;
            i++;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i] = 0;
            i++;
        }

    }
}

int kmpAlgorithmSearch(const char *pat, const char *txt) {
    auto M = strlen(pat);
    auto N = strlen(txt);

    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0, j = 0;

    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M)
            return i - j;
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return -1;
}

int main() {
    cout << kmpAlgorithmSearch("BC", "aABCA");

    return 0;
}
