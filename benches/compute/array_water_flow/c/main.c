// array_water_flow — Trapping rain water simulation
// Measures: two-pass sequential scan with register accumulators
// Workload: N=1000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t water_flow(const int64_t* arr, int64_t* left_max, int64_t n) {
    // Forward pass: compute left_max
    int64_t lm = 0;
    for (int64_t i = 0; i < n; i++) {
        if (arr[i] > lm) lm = arr[i];
        left_max[i] = lm;
    }
    // Backward pass: compute right_max and accumulate water
    int64_t rm = 0;
    int64_t water = 0;
    for (int64_t i = n - 1; i >= 0; i--) {
        if (arr[i] > rm) rm = arr[i];
        int64_t bound = (left_max[i] < rm) ? left_max[i] : rm;
        int64_t w = bound - arr[i];
        if (w > 0) water += w;
    }
    return water;
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* left_max = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000;  // heights 0..999
        }
        checksum += water_flow(arr, left_max, N);
        seed = (seed + iter) & 0x7FFFFFFF;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(left_max);
    return 0;
}
