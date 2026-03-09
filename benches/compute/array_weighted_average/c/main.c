// Array Weighted Average — weighted sum and weight accumulation
// Measures: dual array sequential scan, two accumulators
// Workload: N=2000000, 500 iterations, two arrays (values, weights)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t weighted_average(int64_t* values, int64_t* weights, int64_t n) {
    int64_t weighted_sum = 0;
    int64_t weight_total = 0;
    for (int64_t i = 0; i < n; i++) {
        weighted_sum += values[i] * weights[i];
        weight_total += weights[i];
    }
    // Return integer division to avoid floating point
    if (weight_total == 0) return 0;
    return weighted_sum / weight_total;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* values = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* weights = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            values[i] = seed % 10000;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            weights[i] = 1 + (seed % 100);
        }
        checksum += weighted_average(values, weights, N);
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(values);
    free(weights);
    return 0;
}
