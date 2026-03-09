// Max Product Subarray — Kadane-like DP for products
// Measures: sequential scan, min/max tracking, multiplication
// Workload: N=100000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t max_product(const int64_t* arr, int64_t n) {
    int64_t max_prod = arr[0];
    int64_t min_prod = arr[0];
    int64_t result = arr[0];

    for (int64_t i = 1; i < n; i++) {
        int64_t val = arr[i];
        int64_t a = max_prod * val;
        int64_t b = min_prod * val;

        // max of (a, b, val)
        int64_t new_max = a;
        if (b > new_max) new_max = b;
        if (val > new_max) new_max = val;

        // min of (a, b, val)
        int64_t new_min = a;
        if (b < new_min) new_min = b;
        if (val < new_min) new_min = val;

        max_prod = new_max;
        min_prod = new_min;
        if (max_prod > result) result = max_prod;
    }
    return result;
}

int main() {
    int64_t N = 100000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 5) - 2;  // values -2 to 2
        }
        checksum += max_product(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
