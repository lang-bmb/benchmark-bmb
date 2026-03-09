// Matrix Addition — element-wise add two matrices
// Measures: sequential memory access, simple arithmetic, bandwidth
// Workload: 1000x1000 matrices, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000;
    int64_t SZ = N * N;
    int64_t ITERS = 2000;
    int64_t* a = (int64_t*)malloc(SZ * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(SZ * sizeof(int64_t));
    int64_t* c = (int64_t*)malloc(SZ * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < SZ; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        a[i] = seed % 1000;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        b[i] = seed % 1000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < SZ; i++) {
            c[i] = a[i] + b[i];
        }
        checksum += c[0] + c[SZ - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    free(c);
    return 0;
}
