// Array Kth Smallest — quickselect algorithm
// Measures: partitioning, recursive selection
// Workload: N=500000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t partition(int64_t* arr, int64_t lo, int64_t hi) {
    int64_t pivot = arr[hi];
    int64_t i = lo - 1;
    for (int64_t j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i++;
            int64_t t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        }
    }
    i++;
    int64_t t = arr[i]; arr[i] = arr[hi]; arr[hi] = t;
    return i;
}

static int64_t quickselect(int64_t* arr, int64_t lo, int64_t hi, int64_t k) {
    while (lo < hi) {
        int64_t p = partition(arr, lo, hi);
        if (p == k) return arr[p];
        if (p < k) lo = p + 1;
        else hi = p - 1;
    }
    return arr[lo];
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
            arr[i] = seed % 1000000;
        }
        int64_t k = N / 2;  // median
        checksum += quickselect(arr, 0, N - 1, k);
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
