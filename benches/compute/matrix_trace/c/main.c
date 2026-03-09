// Matrix Trace — sum of diagonal elements with matrix operations
// Measures: strided access (diagonal), sequential fill, cache behavior
// Workload: 500x500 matrix, 5000 iterations with accumulation

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t matrix_trace(const int64_t* mat, int64_t n) {
    int64_t sum = 0;
    for (int64_t i = 0; i < n; i++) {
        sum += mat[i * n + i];
    }
    return sum;
}

static void matrix_add_scalar(int64_t* mat, int64_t n, int64_t scalar) {
    for (int64_t i = 0; i < n * n; i++) {
        mat[i] += scalar;
    }
}

int main() {
    int64_t N = 500;
    int64_t ITERS = 30000;
    int64_t* mat = (int64_t*)malloc(N * N * sizeof(int64_t));

    // Initialize matrix
    int64_t seed = 42;
    for (int64_t i = 0; i < N * N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        mat[i] = seed % 1000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t tr = matrix_trace(mat, N);
        checksum += tr;
        matrix_add_scalar(mat, N, iter % 7);
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    return 0;
}
