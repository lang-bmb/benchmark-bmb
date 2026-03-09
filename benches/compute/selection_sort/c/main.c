// Selection Sort — in-place, find minimum and swap
// Measures: linear scan, conditional minimum, swap
// Workload: N=5000 array, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void selection_sort(int64_t* arr, int64_t n) {
    for (int64_t i = 0; i < n - 1; i++) {
        int64_t min_idx = i;
        for (int64_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        int64_t tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
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
        selection_sort(arr, N);
        for (int64_t i = 0; i < 10; i++) checksum += arr[i];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}