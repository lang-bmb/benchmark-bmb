// Insertion Sort benchmark — in-place, O(n^2) comparison sort
// Measures: sequential array access, inner loop shifts, branch prediction
// Workload: N=5000 array, 200 iterations, LCG PRNG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void insertion_sort(int64_t* arr, int64_t n) {
    for (int64_t i = 1; i < n; i++) {
        int64_t key = arr[i];
        int64_t j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        insertion_sort(arr, N);
        for (int64_t i = 0; i < 10; i++) {
            checksum += arr[i];
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}