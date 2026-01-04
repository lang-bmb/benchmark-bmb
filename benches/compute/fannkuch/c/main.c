// Fannkuch-redux benchmark
// Measures: array manipulation, permutation generation

#include <stdio.h>

#define MAX_N 12

int count[MAX_N];
int perm[MAX_N];
int perm1[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int fannkuch(int n) {
    int maxFlips = 0;
    int checksum = 0;
    int permCount = 0;

    for (int i = 0; i < n; i++) {
        perm1[i] = i;
        count[i] = i + 1;
    }

    while (1) {
        for (int i = 0; i < n; i++) perm[i] = perm1[i];

        int flips = 0;
        int first = perm[0];
        if (first != 0) {
            do {
                int tmp;
                for (int lo = 0, hi = first; lo < hi; lo++, hi--) {
                    tmp = perm[lo];
                    perm[lo] = perm[hi];
                    perm[hi] = tmp;
                }
                flips++;
                first = perm[0];
            } while (first != 0);
            maxFlips = max(maxFlips, flips);
            checksum += (permCount & 1) ? -flips : flips;
        }

        // Generate next permutation
        int i = 1;
        int first_perm = perm1[0];
        while (i < n) {
            int tmp = perm1[i];
            perm1[i] = perm1[i-1];
            perm1[i-1] = tmp;
            count[i]--;
            if (count[i] != 0) break;
            count[i] = i + 1;
            i++;
        }
        if (i >= n) break;
        permCount++;
    }

    printf("Checksum: %d\n", checksum);
    return maxFlips;
}

int main() {
    int n = 10;
    printf("Pfannkuchen(%d) = %d\n", n, fannkuch(n));
    return 0;
}
