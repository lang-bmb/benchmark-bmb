// Hamming Distance — pairwise XOR + popcount (Kernighan's method)
// Measures: bitwise operations, branch prediction, memory access patterns
// Workload: 50000 pairs, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t popcount(int64_t x) {
    int64_t count = 0;
    int64_t n = x;
    while (n != 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

static int64_t hamming(int64_t a, int64_t b) {
    return popcount(a ^ b);
}

int main() {
    int64_t num_pairs = 50000;
    int64_t num_values = num_pairs * 2;
    int64_t iters = 500;
    int64_t *arr = (int64_t *)malloc(num_values * 8);

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Fill array with PRNG values
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < num_values; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        // Compute pairwise hamming distances for consecutive pairs
        int64_t sum_val = 0;
        for (int64_t p = 0; p < num_pairs; p++) {
            int64_t a = arr[p * 2];
            int64_t b = arr[p * 2 + 1];
            sum_val += hamming(a, b);
        }
        checksum += sum_val;
    }

    free(arr);
    printf("%lld\n", (long long)checksum);
    return 0;
}
