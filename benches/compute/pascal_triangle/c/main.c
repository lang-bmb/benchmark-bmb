// Pascal's Triangle row computation benchmark — modular arithmetic
// Measures: sequential array access, modular addition, pointer swapping
// Workload: N=2000 rows, 200 iterations, sum all entries mod 10^9+7

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 2000
#define ITERS 200
#define MOD 1000000007LL

static int64_t pascal(int64_t n, int64_t* prev, int64_t* curr) {
    int64_t checksum = 1;
    prev[0] = 1;
    for (int64_t row = 1; row <= n; row++) {
        curr[0] = 1;
        for (int64_t j = 1; j < row; j++) {
            curr[j] = (prev[j - 1] + prev[j]) % MOD;
        }
        curr[row] = 1;
        // Sum all entries in curr row
        for (int64_t k = 0; k <= row; k++) {
            checksum = (checksum + curr[k]) % MOD;
        }
        // Swap prev and curr by copying curr into prev
        for (int64_t c = 0; c <= row; c++) {
            prev[c] = curr[c];
        }
    }
    return checksum;
}

int main() {
    int64_t* prev = (int64_t*)malloc((N + 1) * sizeof(int64_t));
    int64_t* curr = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    int64_t total = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        total = (total + pascal(N, prev, curr)) % MOD;
    }
    printf("%lld\n", (long long)total);
    free(prev);
    free(curr);
    return 0;
}
