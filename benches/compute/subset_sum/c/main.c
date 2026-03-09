// Subset Sum — boolean DP
// Measures: 1D boolean DP, reverse iteration, bitwise-like patterns
// Workload: N=200 items, target=5000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t subset_sum(int64_t* items, int64_t n, int64_t target, int64_t* dp) {
    for (int64_t i = 0; i <= target; i++) dp[i] = 0;
    dp[0] = 1;
    for (int64_t i = 0; i < n; i++) {
        int64_t w = items[i];
        for (int64_t j = target; j >= w; j--) {
            if (dp[j - w] == 1) dp[j] = 1;
        }
    }
    int64_t count = 0;
    for (int64_t i = 1; i <= target; i++) {
        count += dp[i];
    }
    return count;
}

int main() {
    int64_t N = 200;
    int64_t TARGET = 5000;
    int64_t ITERS = 500;
    int64_t* items = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc((TARGET + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 22222 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            items[i] = (seed % 50) + 1;
        }
        checksum += subset_sum(items, N, TARGET, dp);
    }

    printf("%lld\n", (long long)checksum);
    free(items); free(dp);
    return 0;
}