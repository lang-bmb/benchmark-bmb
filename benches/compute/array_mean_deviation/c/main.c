// Mean Deviation — compute mean absolute deviation
// Measures: two-pass scan (sum then deviation), accumulator
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        int64_t sum = 0;
        for (int64_t i = 0; i < N; i++) sum += arr[i];
        int64_t mean = sum / N;
        int64_t dev = 0;
        for (int64_t i = 0; i < N; i++) {
            int64_t d = arr[i] - mean;
            if (d < 0) d = -d;
            dev += d;
        }
        checksum += dev / N;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
