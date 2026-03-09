// Matrix Inverse — Gauss-Jordan elimination
// Measures: pivot selection, row operations, division
// Workload: N=200, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Using fixed-point arithmetic (scale = 1000) to avoid floating point
static void matrix_inverse(int64_t* a, int64_t* inv, int64_t n) {
    // Initialize inv as identity * 1000
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            inv[i * n + j] = (i == j) ? 1000 : 0;
        }
    }

    for (int64_t col = 0; col < n; col++) {
        // Find pivot (largest absolute value in column)
        int64_t pivot_row = col;
        int64_t max_val = a[col * n + col];
        if (max_val < 0) max_val = -max_val;
        for (int64_t i = col + 1; i < n; i++) {
            int64_t v = a[i * n + col];
            if (v < 0) v = -v;
            if (v > max_val) {
                max_val = v;
                pivot_row = i;
            }
        }

        // Swap rows
        if (pivot_row != col) {
            for (int64_t j = 0; j < n; j++) {
                int64_t tmp = a[col * n + j];
                a[col * n + j] = a[pivot_row * n + j];
                a[pivot_row * n + j] = tmp;
                tmp = inv[col * n + j];
                inv[col * n + j] = inv[pivot_row * n + j];
                inv[pivot_row * n + j] = tmp;
            }
        }

        int64_t pivot = a[col * n + col];
        if (pivot == 0) continue;

        // Scale pivot row
        for (int64_t j = 0; j < n; j++) {
            a[col * n + j] = a[col * n + j] * 1000 / pivot;
            inv[col * n + j] = inv[col * n + j] * 1000 / pivot;
        }

        // Eliminate column in other rows
        for (int64_t i = 0; i < n; i++) {
            if (i != col) {
                int64_t factor = a[i * n + col];
                for (int64_t j = 0; j < n; j++) {
                    a[i * n + j] -= factor * a[col * n + j] / 1000;
                    inv[i * n + j] -= factor * inv[col * n + j] / 1000;
                }
            }
        }
    }
}

int main() {
    int64_t N = 200;
    int64_t ITERS = 100;
    int64_t* a = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t* inv = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate diagonally dominant matrix (for invertibility)
        for (int64_t i = 0; i < N; i++) {
            int64_t row_sum = 0;
            for (int64_t j = 0; j < N; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                int64_t val = (seed % 201) - 100;  // [-100, 100]
                a[i * N + j] = val;
                if (i != j) {
                    row_sum += (val < 0) ? -val : val;
                }
            }
            a[i * N + i] = row_sum + 100;  // Diagonally dominant
        }
        matrix_inverse(a, inv, N);
        checksum += inv[0] + inv[N * N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(a);
    free(inv);
    return 0;
}
