// Array Dedup — remove consecutive duplicates in-place
// Measures: sequential scan, conditional copy, comparison
// Workload: N=500000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t dedup(int64_t* arr, int64_t n) {
    if (n <= 1) return n;
    int64_t write = 1;
    for (int64_t i = 1; i < n; i++) {
        if (arr[i] != arr[write - 1]) {
            arr[write] = arr[i];
            write++;
        }
    }
    return write;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 50;
        }
        // Sort first (simple insertion for small range, or use counting)
        // Actually just use the array as-is — dedup removes consecutive dups
        checksum += dedup(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
