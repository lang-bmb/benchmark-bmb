// Rod Cutting — unbounded knapsack DP
// Measures: 1D DP with inner loop, max tracking
// Workload: rod length=5000, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t rod_cutting(int64_t* prices, int64_t* dp, int64_t n) {
    dp[0] = 0;
    for (int64_t i = 1; i <= n; i++) {
        int64_t best = -1;
        for (int64_t j = 1; j <= i; j++) {
            int64_t candidate = prices[j - 1] + dp[i - j];
            if (candidate > best) best = candidate;
        }
        dp[i] = best;
    }
    return dp[n];
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 200;
    int64_t* prices = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 11111 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            prices[i] = (seed % 100) + 1;
        }
        checksum += rod_cutting(prices, dp, N) % 1000000007;
    }

    printf("%lld\n", (long long)checksum);
    free(prices); free(dp);
    return 0;
}