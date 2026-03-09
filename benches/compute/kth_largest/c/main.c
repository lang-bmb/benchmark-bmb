// Kth largest element — iterative Quickselect with Lomuto partition
// Measures: partitioning, branch prediction, random access patterns
// Workload: N=100000 array, 1000 iterations, find median (k=50000), LCG PRNG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t quickselect(int64_t* arr, int64_t left, int64_t right, int64_t k) {
    int64_t lo = left;
    int64_t hi = right;
    while (lo < hi) {
        // Lomuto partition around arr[hi]
        int64_t pivot = arr[hi];
        int64_t i = lo;
        for (int64_t j = lo; j < hi; j++) {
            if (arr[j] < pivot) {
                int64_t tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
            }
        }
        // swap arr[i] and arr[hi]
        int64_t tmp = arr[i];
        arr[i] = arr[hi];
        arr[hi] = tmp;
        if (i == k) {
            lo = k;
            hi = k;
        } else if (i < k) {
            lo = i + 1;
        } else {
            hi = i - 1;
        }
    }
    return arr[k];
}

int main() {
    int64_t N = 100000;
    int64_t ITERS = 1000;
    int64_t K = 50000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill with LCG pseudo-random
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        int64_t result = quickselect(arr, 0, N - 1, K);
        checksum += result;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
