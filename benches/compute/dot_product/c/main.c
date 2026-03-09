// Dot Product — multiply-accumulate over large integer vectors
// Measures: sequential memory access, multiply-accumulate, SIMD vectorization potential
// Workload: N=1000000 vectors, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t n = 1000000;
    int64_t iters = 500;
    int64_t modp = 1000000007;
    int64_t* a = (int64_t*)malloc(n * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(n * sizeof(int64_t));

    // Generate vectors using deterministic PRNG
    int64_t seed = 42;
    for (int64_t i = 0; i < n; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        a[i] = seed % 1000;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        b[i] = seed % 1000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Compute dot product with modular arithmetic
        int64_t dot = 0;
        for (int64_t j = 0; j < n; j++) {
            dot = (dot + a[j] * b[j]) % modp;
        }
        checksum = (checksum + dot) % modp;
    }

    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    return 0;
}