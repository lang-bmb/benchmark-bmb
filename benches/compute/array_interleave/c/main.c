// Array Interleave — interleave two arrays into one
// Measures: alternating writes, sequential reads, stride access
// Workload: N=500000 per array, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 3000;
    int64_t* a = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* out = (int64_t*)malloc(2 * N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        a[i] = seed;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        b[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            out[2 * i] = a[i];
            out[2 * i + 1] = b[i];
        }
        checksum += out[0] + out[2 * N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    free(out);
    return 0;
}
