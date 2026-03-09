// Matrix Determinant benchmark — Gaussian elimination with partial pivoting
// Measures: nested loops, array access, branching, integer arithmetic
// Workload: N=200 matrix, 1000 iterations, scaled integer arithmetic (x1000)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t fill_matrix(int64_t* mat, int64_t n, int64_t seed_in) {
    int64_t seed = seed_in;
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t val = (seed % 2001) - 1000;
            mat[i * n + j] = val;
        }
    }
    return seed;
}

static int64_t abs_val(int64_t x) {
    return x < 0 ? -x : x;
}

static int64_t gaussian_det_sign(int64_t* mat, int64_t n) {
    int64_t sign = 1;
    for (int64_t col = 0; col < n; col++) {
        // Find pivot row
        int64_t max_val = abs_val(mat[col * n + col]);
        int64_t max_row = col;
        for (int64_t r = col + 1; r < n; r++) {
            int64_t v = abs_val(mat[r * n + col]);
            if (v > max_val) {
                max_val = v;
                max_row = r;
            }
        }
        // If pivot is zero, determinant is zero
        if (max_val == 0) {
            sign = 0;
        }
        // Swap rows if needed
        if (max_row != col) {
            for (int64_t k = 0; k < n; k++) {
                int64_t tmp = mat[col * n + k];
                mat[col * n + k] = mat[max_row * n + k];
                mat[max_row * n + k] = tmp;
            }
            sign = -sign;
        }
        // Eliminate below
        int64_t pivot = mat[col * n + col];
        if (pivot != 0) {
            for (int64_t row = col + 1; row < n; row++) {
                int64_t factor = mat[row * n + col];
                for (int64_t c = col; c < n; c++) {
                    int64_t cur = mat[row * n + c];
                    int64_t above = mat[col * n + c];
                    mat[row * n + c] = cur * pivot - factor * above;
                }
            }
        }
    }
    // Check sign of diagonal product
    if (sign != 0) {
        int64_t neg_count = 0;
        for (int64_t d = 0; d < n; d++) {
            if (mat[d * n + d] < 0) {
                neg_count++;
            }
        }
        if (neg_count % 2 != 0) {
            sign = -sign;
        }
    }
    return sign;
}

int main() {
    int64_t n = 200;
    int64_t iters = 1000;
    int64_t* mat = (int64_t*)malloc(n * n * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        fill_matrix(mat, n, 42 + iter * 7);
        int64_t s = gaussian_det_sign(mat, n);
        checksum += s;
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    return 0;
}
