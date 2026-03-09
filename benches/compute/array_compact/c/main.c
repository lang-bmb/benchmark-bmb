// Array Compact — remove zeros from array in-place
// Measures: conditional copy, sequential scan, write pointer
// Workload: N=500000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t compact(int64_t* arr, int64_t n) {
    int64_t write = 0;
    for (int64_t i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[write++] = arr[i];
        }
    }
    return write;
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
            arr[i] = seed % 5;
        }
        checksum += compact(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
