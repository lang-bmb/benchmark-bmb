// Edit Distance — Wagner-Fischer full matrix
// Measures: 2D DP, min computation, sequential fill
// Workload: 2000x2000 strings, 50 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t edit_distance(const int64_t* s, int64_t m, const int64_t* t, int64_t n, int64_t* dp) {
    int64_t cols = n + 1;

    for (int64_t i = 0; i <= m; i++) dp[i * cols + 0] = i;
    for (int64_t j = 0; j <= n; j++) dp[0 * cols + j] = j;

    for (int64_t i = 1; i <= m; i++) {
        for (int64_t j = 1; j <= n; j++) {
            int64_t cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            int64_t del = dp[(i - 1) * cols + j] + 1;
            int64_t ins = dp[i * cols + (j - 1)] + 1;
            int64_t sub = dp[(i - 1) * cols + (j - 1)] + cost;
            int64_t m = del;
            if (ins < m) m = ins;
            if (sub < m) m = sub;
            dp[i * cols + j] = m;
        }
    }
    return dp[m * cols + n];
}

int main() {
    int64_t M = 2000;
    int64_t N = 2000;
    int64_t ITERS = 50;

    int64_t* s = (int64_t*)malloc(M * sizeof(int64_t));
    int64_t* t = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc((M + 1) * (N + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < M; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            s[i] = seed % 26;
        }
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            t[i] = seed % 26;
        }
        checksum += edit_distance(s, M, t, N, dp);
    }

    printf("%lld\n", (long long)checksum);
    free(s);
    free(t);
    free(dp);
    return 0;
}
