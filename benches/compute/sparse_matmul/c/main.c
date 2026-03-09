// Sparse Matrix-Vector Multiply — CSR format
// Measures: indirect indexing, sparse access patterns
// Workload: 5000x5000 sparse matrix, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 5000
#define NNZ_PER_ROW 10
#define ITERS 3000

int main() {
    int64_t total_nnz = (int64_t)N * NNZ_PER_ROW;

    // CSR arrays
    int64_t* values  = (int64_t*)malloc(total_nnz * sizeof(int64_t));
    int64_t* col_idx = (int64_t*)malloc(total_nnz * sizeof(int64_t));
    int64_t* row_ptr = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    // Dense vector (all 1s)
    int64_t* x = (int64_t*)malloc(N * sizeof(int64_t));
    for (int64_t i = 0; i < N; i++) {
        x[i] = 1;
    }

    // Result vector
    int64_t* y = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate random sparse matrix using LCG
        int64_t seed = 12345 + iter;
        int64_t nnz = 0;
        row_ptr[0] = 0;

        for (int64_t row = 0; row < N; row++) {
            for (int64_t k = 0; k < NNZ_PER_ROW; k++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                col_idx[nnz] = seed % N;
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                values[nnz] = seed % 100;
                nnz++;
            }
            row_ptr[row + 1] = nnz;
        }

        // SpMV: y = A * x
        for (int64_t row = 0; row < N; row++) {
            int64_t sum = 0;
            for (int64_t j = row_ptr[row]; j < row_ptr[row + 1]; j++) {
                sum += values[j] * x[col_idx[j]];
            }
            y[row] = sum;
        }

        // Sum result vector into checksum
        for (int64_t i = 0; i < N; i++) {
            checksum += y[i];
        }
    }

    printf("%lld\n", (long long)checksum);

    free(values);
    free(col_idx);
    free(row_ptr);
    free(x);
    free(y);
    return 0;
}
