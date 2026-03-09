// Jacobi Iteration — 2D Laplace solver
// Measures: stencil computation, array swapping, convergence loop
// Workload: 300x300 grid, 500 iterations, 10 solves

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 300
#define STEPS 500
#define ITERS 10

static int64_t jacobi_solve(int64_t* u_old, int64_t* u_new) {
    // Initialize: boundary u[0][j] = 1000, others = 0
    for (int64_t i = 0; i < N; i++) {
        for (int64_t j = 0; j < N; j++) {
            u_old[i * N + j] = (i == 0) ? 1000 : 0;
            u_new[i * N + j] = (i == 0) ? 1000 : 0;
        }
    }

    for (int64_t step = 0; step < STEPS; step++) {
        // Update interior points
        for (int64_t i = 1; i < N - 1; i++) {
            for (int64_t j = 1; j < N - 1; j++) {
                int64_t up    = u_old[(i - 1) * N + j];
                int64_t down  = u_old[(i + 1) * N + j];
                int64_t left  = u_old[i * N + (j - 1)];
                int64_t right = u_old[i * N + (j + 1)];
                u_new[i * N + j] = (up + down + left + right) / 4;
            }
        }
        // Fix boundary in u_new
        for (int64_t j = 0; j < N; j++) {
            u_new[j] = 1000;  // row 0
        }
        // Swap: copy u_new into u_old
        for (int64_t i = 0; i < N * N; i++) {
            u_old[i] = u_new[i];
        }
    }

    // Checksum: sum of all interior points
    int64_t sum = 0;
    for (int64_t i = 1; i < N - 1; i++) {
        for (int64_t j = 1; j < N - 1; j++) {
            sum += u_new[i * N + j];
        }
    }
    return sum;
}

int main() {
    int64_t* u_old = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t* u_new = (int64_t*)malloc(N * N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        checksum += jacobi_solve(u_old, u_new);
    }
    printf("%lld\n", (long long)checksum);
    free(u_old);
    free(u_new);
    return 0;
}
