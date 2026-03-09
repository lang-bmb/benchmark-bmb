// LU Decomposition benchmark (Doolittle's method, no pivoting)
// Measures: triple nested loop, 2D array access, integer division
// Workload: N=200 matrix, 100 iterations, scaled integers (x1000)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t lu_decompose(int64_t* mat, int64_t* l_mat, int64_t* u_mat, int64_t n) {
    // Initialize L to identity (diagonal = 1000 = scaled 1.0), U to zero
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            u_mat[i * n + j] = 0;
            l_mat[i * n + j] = (i == j) ? 1000 : 0;
        }
    }

    // Doolittle's algorithm
    for (int64_t k = 0; k < n; k++) {
        // Compute U[k][j] for j = k..n
        for (int64_t j = k; j < n; j++) {
            int64_t sum_u = 0;
            for (int64_t s = 0; s < k; s++) {
                sum_u += l_mat[k * n + s] * u_mat[s * n + j] / 1000;
            }
            u_mat[k * n + j] = mat[k * n + j] - sum_u;
        }

        // Compute L[i][k] for i = k+1..n
        int64_t ukk = u_mat[k * n + k];
        for (int64_t i = k + 1; i < n; i++) {
            int64_t sum_l = 0;
            for (int64_t s = 0; s < k; s++) {
                sum_l += l_mat[i * n + s] * u_mat[s * n + k] / 1000;
            }
            l_mat[i * n + k] = (mat[i * n + k] - sum_l) * 1000 / ukk;
        }
    }

    // Checksum: sum diagonal of U
    int64_t cksum = 0;
    for (int64_t i = 0; i < n; i++) {
        cksum += u_mat[i * n + i];
    }
    return cksum;
}

int main() {
    int64_t n = 200;
    int64_t iters = 100;
    int64_t* mat = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* l_mat = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* u_mat = (int64_t*)malloc(n * n * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        // Generate random NxN matrix using LCG, values scaled by 1000
        int64_t seed = 123456789 + iter * 7;
        for (int64_t i = 0; i < n; i++) {
            for (int64_t j = 0; j < n; j++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                // Values in range [1000..10000] to keep diagonal dominant
                int64_t val;
                if (i == j) {
                    val = (seed % 9001) + 10000;
                } else {
                    val = (seed % 2001) + 100;
                }
                mat[i * n + j] = val;
            }
        }

        checksum += lu_decompose(mat, l_mat, u_mat, n);
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    free(l_mat);
    free(u_mat);
    return 0;
}
