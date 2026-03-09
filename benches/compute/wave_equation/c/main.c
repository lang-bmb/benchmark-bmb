// Wave Equation — 1D finite difference
// Measures: stencil computation, sequential array access
// Workload: N=10000, T=2000, 50 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 10000
#define T 2000
#define ITERS 50
#define C2 250  // c^2 = 0.25 in fixed-point *1000

int main() {
    int64_t* u_prev = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* u_curr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* u_next = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Initialize arrays to zero
        for (int64_t i = 0; i < N; i++) {
            u_prev[i] = 0;
            u_curr[i] = 0;
            u_next[i] = 0;
        }
        // Initial condition: pulse at center
        u_curr[N / 2] = 1000;

        // Time stepping
        for (int64_t t = 0; t < T; t++) {
            // Compute u_next for interior points
            for (int64_t i = 1; i < N - 1; i++) {
                u_next[i] = 2 * u_curr[i] - u_prev[i]
                    + C2 * (u_curr[i + 1] - 2 * u_curr[i] + u_curr[i - 1]) / 1000;
            }
            // Boundary conditions
            u_next[0] = 0;
            u_next[N - 1] = 0;

            // Rotate arrays: prev <- curr, curr <- next
            int64_t* tmp = u_prev;
            u_prev = u_curr;
            u_curr = u_next;
            u_next = tmp;
        }

        // Checksum: sum of abs(u_curr[i])
        for (int64_t i = 0; i < N; i++) {
            int64_t v = u_curr[i];
            checksum += (v < 0) ? -v : v;
        }
    }

    printf("%lld\n", (long long)checksum);

    free(u_prev);
    free(u_curr);
    free(u_next);
    return 0;
}
