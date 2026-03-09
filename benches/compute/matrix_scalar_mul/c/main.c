// Matrix Scalar Multiply — multiply all elements by a scalar
// Measures: sequential access, multiply, bandwidth
// Workload: 1000x1000 matrix, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000;
    int64_t SZ = N * N;
    int64_t ITERS = 3000;
    int64_t* mat = (int64_t*)malloc(SZ * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < SZ; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        mat[i] = seed % 1000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t scalar = iter + 2;
        for (int64_t i = 0; i < SZ; i++) {
            mat[i] *= scalar;
        }
        checksum += mat[0] + mat[SZ - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    return 0;
}
