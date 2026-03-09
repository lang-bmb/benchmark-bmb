// 1D Median Filter — sliding window of size 5
// Measures: memory access patterns, compare-and-swap, data-dependent branching
// Workload: N=100000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline int64_t min2(int64_t a, int64_t b) {
    return a < b ? a : b;
}

static inline int64_t max2(int64_t a, int64_t b) {
    return a > b ? a : b;
}

// Sorting network for 5 elements — returns median (3rd element)
// Uses optimal 9-comparison network
static inline int64_t median5(int64_t a0, int64_t a1, int64_t a2, int64_t a3, int64_t a4) {
    // Step 1: sort pairs (0,1) and (3,4)
    int64_t lo01 = min2(a0, a1);
    int64_t hi01 = max2(a0, a1);
    int64_t lo34 = min2(a3, a4);
    int64_t hi34 = max2(a3, a4);

    // Step 2: sort (lo01, lo34) to get global min candidate, (hi01, hi34) to get global max candidate
    int64_t lo_lo = min2(lo01, lo34);
    int64_t hi_lo = max2(lo01, lo34);
    int64_t lo_hi = min2(hi01, hi34);
    int64_t hi_hi = max2(hi01, hi34);

    // Step 3: The median is among {hi_lo, lo_hi, a2}
    // We need the median of these 3
    // lo_lo is <= all, hi_hi is >= all, so discard them
    int64_t m0 = hi_lo;
    int64_t m1 = lo_hi;
    int64_t m2 = a2;

    // Median of 3: sort and take middle
    int64_t s01a = min2(m0, m1);
    int64_t s01b = max2(m0, m1);
    int64_t s02a = max2(s01a, m2);
    int64_t result = min2(s01b, s02a);
    return result;
}

int main() {
    int64_t n = 100000;
    int64_t iters = 5000;
    int64_t half_w = 2;

    // Allocate input and output arrays
    int64_t* input_arr = (int64_t*)malloc(n * sizeof(int64_t));
    int64_t* output_arr = (int64_t*)malloc(n * sizeof(int64_t));

    // Generate input using deterministic PRNG
    int64_t seed = 42;
    for (int64_t i = 0; i < n; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        input_arr[i] = seed % 10000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Apply median filter: for positions half_w to n-half_w-1
        int64_t out_len = n - half_w - half_w;
        for (int64_t j = half_w; j < n - half_w; j++) {
            int64_t v0 = input_arr[j - 2];
            int64_t v1 = input_arr[j - 1];
            int64_t v2 = input_arr[j];
            int64_t v3 = input_arr[j + 1];
            int64_t v4 = input_arr[j + 2];
            int64_t med = median5(v0, v1, v2, v3, v4);
            output_arr[j - half_w] = med;
        }

        // Accumulate checksum from output
        for (int64_t k = 0; k < out_len; k++) {
            checksum += output_arr[k];
        }
    }

    printf("%lld\n", (long long)checksum);
    free(input_arr);
    free(output_arr);
    return 0;
}
