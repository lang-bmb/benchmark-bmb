// 2D Prefix Sum — build prefix sum matrix + range sum queries
// Measures: 2D array access, inclusion-exclusion, cache locality
// Workload: 500x500 matrix, 100K queries, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void build_prefix_2d(int64_t* mat, int64_t* ps, int64_t rows, int64_t cols) {
    int64_t w = cols + 1;
    // Zero first row and first column
    for (int64_t j = 0; j <= cols; j++) ps[j] = 0;
    for (int64_t i = 0; i <= rows; i++) ps[i * w] = 0;
    // Fill prefix sum (1-indexed)
    for (int64_t i = 1; i <= rows; i++) {
        for (int64_t j = 1; j <= cols; j++) {
            int64_t val = mat[(i - 1) * cols + (j - 1)];
            ps[i * w + j] = val + ps[(i - 1) * w + j] + ps[i * w + (j - 1)] - ps[(i - 1) * w + (j - 1)];
        }
    }
}

static int64_t query_2d(int64_t* ps, int64_t w, int64_t r1, int64_t c1, int64_t r2, int64_t c2) {
    return ps[r2 * w + c2] - ps[(r1 - 1) * w + c2] - ps[r2 * w + (c1 - 1)] + ps[(r1 - 1) * w + (c1 - 1)];
}

int main() {
    int64_t ROWS = 500;
    int64_t COLS = 500;
    int64_t NQUERIES = 100000;
    int64_t ITERS = 100;
    int64_t* mat = (int64_t*)malloc(ROWS * COLS * sizeof(int64_t));
    int64_t w = COLS + 1;
    int64_t* ps = (int64_t*)malloc((ROWS + 1) * w * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 31415 + iter;
        // Fill matrix
        for (int64_t i = 0; i < ROWS * COLS; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            mat[i] = seed % 100;
        }
        build_prefix_2d(mat, ps, ROWS, COLS);
        // Answer queries
        for (int64_t q = 0; q < NQUERIES; q++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t raw_r1 = (seed % ROWS) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t raw_c1 = (seed % COLS) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t raw_r2 = (seed % ROWS) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t raw_c2 = (seed % COLS) + 1;
            // Ensure r1 <= r2 and c1 <= c2
            int64_t r1 = raw_r1 <= raw_r2 ? raw_r1 : raw_r2;
            int64_t r2 = raw_r1 <= raw_r2 ? raw_r2 : raw_r1;
            int64_t c1 = raw_c1 <= raw_c2 ? raw_c1 : raw_c2;
            int64_t c2 = raw_c1 <= raw_c2 ? raw_c2 : raw_c1;
            checksum += query_2d(ps, w, r1, c1, r2, c2);
        }
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(mat);
    free(ps);
    return 0;
}
