// Count Bits Range — popcount over array of integers
// Measures: bit manipulation, loop performance, branch-free code
// Workload: N=500000 array, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t popcount(int64_t x) {
    int64_t count = 0;
    while (x != 0) {
        x = x & (x - 1);
        count++;
    }
    return count;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        int64_t total = 0;
        for (int64_t j = 0; j < N; j++) {
            total += popcount(arr[j]);
        }
        checksum += total;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
