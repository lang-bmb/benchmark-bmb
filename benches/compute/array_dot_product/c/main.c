// Dot Product — sum of element-wise products of two arrays
// Measures: dual-array scan, accumulator
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* a = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            a[i] = seed % 1000;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            b[i] = seed % 1000;
        }
        int64_t dot = 0;
        for (int64_t i = 0; i < N; i++) {
            dot += a[i] * b[i];
        }
        checksum += dot % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    return 0;
}
