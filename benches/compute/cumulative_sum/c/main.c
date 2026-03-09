// Cumulative Sum (Prefix Sum) — compute running totals
// Measures: sequential access, addition, memory write
// Workload: N=500000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t cumsum(int64_t* arr, int64_t n) {
    for (int64_t i = 1; i < n; i++) {
        arr[i] += arr[i - 1];
    }
    return arr[n - 1];
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100;
        }
        checksum += cumsum(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
