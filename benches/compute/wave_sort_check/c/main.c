// Wave Sort Check — check if array is wave-sorted (a[0]>=a[1]<=a[2]>=...)
// Measures: sequential scan, alternating comparisons
// Workload: N=500000, 10000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t is_wave_sorted(const int64_t* arr, int64_t n) {
    for (int64_t i = 0; i < n - 1; i++) {
        if (i % 2 == 0) {
            if (arr[i] < arr[i + 1]) return 0;
        } else {
            if (arr[i] > arr[i + 1]) return 0;
        }
    }
    return 1;
}

static void wave_sort(int64_t* arr, int64_t n) {
    for (int64_t i = 0; i < n - 1; i++) {
        if (i % 2 == 0) {
            if (arr[i] < arr[i + 1]) {
                int64_t t = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = t;
            }
        } else {
            if (arr[i] > arr[i + 1]) {
                int64_t t = arr[i]; arr[i] = arr[i + 1]; arr[i + 1] = t;
            }
        }
    }
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        wave_sort(arr, N);
        checksum += is_wave_sorted(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
