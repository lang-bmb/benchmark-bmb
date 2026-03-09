// Quicksort benchmark — Lomuto partition, in-place
// Measures: array read/write in hot loop, recursion, branch prediction
// Workload: N=10000 array, 200 iterations, LCG PRNG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void swap(int64_t* arr, int64_t i, int64_t j) {
    int64_t tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

static int64_t partition(int64_t* arr, int64_t lo, int64_t hi) {
    int64_t pivot = arr[hi];
    int64_t i = lo;
    for (int64_t j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, i, hi);
    return i;
}

static void quicksort(int64_t* arr, int64_t lo, int64_t hi) {
    if (lo < hi) {
        int64_t p = partition(arr, lo, hi);
        if (p > lo) quicksort(arr, lo, p - 1);
        quicksort(arr, p + 1, hi);
    }
}

int main() {
    int64_t N = 10000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill with LCG pseudo-random (same seed each iteration)
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        quicksort(arr, 0, N - 1);
        // Checksum: sum first 10 elements
        for (int64_t i = 0; i < 10; i++) {
            checksum += arr[i];
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
