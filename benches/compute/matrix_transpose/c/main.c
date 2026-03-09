// Matrix Transpose — in-place square matrix transpose
// Measures: cache performance, strided memory access
// Workload: 1000x1000 matrix, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 1000
#define ITERS 500

int main(void) {
    int64_t *mat = (int64_t *)malloc(N * N * sizeof(int64_t));
    if (!mat) return 1;

    // Initialize: mat[i*N+j] = i*N + j
    for (int64_t i = 0; i < N; i++) {
        for (int64_t j = 0; j < N; j++) {
            mat[i * N + j] = i * N + j;
        }
    }

    // Transpose in-place ITERS times
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            for (int64_t j = i + 1; j < N; j++) {
                int64_t tmp = mat[i * N + j];
                mat[i * N + j] = mat[j * N + i];
                mat[j * N + i] = tmp;
            }
        }
    }

    // Checksum: sum of first 100 elements
    int64_t checksum = 0;
    for (int64_t k = 0; k < 100; k++) {
        checksum += mat[k];
    }

    printf("%lld\n", checksum);

    free(mat);
    return 0;
}
