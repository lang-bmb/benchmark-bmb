// Array Consecutive Diff — count consecutive pairs where diff > threshold
// Measures: sequential scan, register carry (prev), comparison
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t consecutive_diff_count(int64_t* arr, int64_t n, int64_t threshold) {
    int64_t count = 0;
    int64_t prev = arr[0];
    for (int64_t i = 1; i < n; i++) {
        int64_t diff = arr[i] - prev;
        if (diff < 0) diff = -diff;
        if (diff > threshold) {
            count++;
        }
        prev = arr[i];
    }
    return count;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        int64_t threshold = 5000 + (iter % 1000);
        checksum += consecutive_diff_count(arr, N, threshold);
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(arr);
    return 0;
}
