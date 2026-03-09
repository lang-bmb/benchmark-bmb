// Matrix Chain Multiplication — O(n^3) DP
// Measures: 2D array access (triangular), triple nested loop, min tracking
// Workload: N=500 matrices, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int64_t matrix_chain(int64_t* dims, int64_t n, int64_t* dp) {
    for (int64_t i = 0; i < n * n; i++) dp[i] = 0;
    for (int64_t l = 2; l <= n; l++) {
        for (int64_t start = 0; start <= n - l; start++) {
            int64_t end = start + l - 1;
            dp[start * n + end] = INT64_MAX;
            for (int64_t k = start; k < end; k++) {
                int64_t cost = dp[start * n + k]
                    + dp[(k + 1) * n + end]
                    + dims[start] * dims[k + 1] * dims[end + 1];
                if (cost < dp[start * n + end]) {
                    dp[start * n + end] = cost;
                }
            }
        }
    }
    return dp[n - 1];
}

int main() {
    int64_t N = 500;
    int64_t ITERS = 100;
    int64_t* dims = (int64_t*)malloc((N + 1) * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc(N * N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 7777 + iter;
        for (int64_t i = 0; i <= N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            dims[i] = (seed % 50) + 1;
        }
        checksum += matrix_chain(dims, N, dp) % 1000000007;
    }

    printf("%lld\n", (long long)checksum);
    free(dims);
    free(dp);
    return 0;
}