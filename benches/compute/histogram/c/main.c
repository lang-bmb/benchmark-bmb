// Histogram — frequency counting
// Measures: random array access, binning, accumulation
// Workload: N=1M values, 256 bins, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 1000000;
    int64_t BINS = 256;
    int64_t ITERS = 200;
    int64_t* values = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* hist = (int64_t*)malloc(BINS * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            values[i] = seed % BINS;
        }
        // Clear histogram
        memset(hist, 0, BINS * sizeof(int64_t));
        // Build histogram
        for (int64_t i = 0; i < N; i++) {
            hist[values[i]]++;
        }
        // Entropy approximation: sum of count[i] * count[i]
        int64_t entropy = 0;
        for (int64_t i = 0; i < BINS; i++) {
            entropy += hist[i] * hist[i];
        }
        checksum += entropy;
    }

    printf("%lld\n", (long long)checksum);
    free(values);
    free(hist);
    return 0;
}
