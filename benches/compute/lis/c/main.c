// Longest Increasing Subsequence — O(n^2) DP
// Measures: 1D array access, conditional max, nested loop
// Workload: N=5000 array, 100 iterations, LCG PRNG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t lis(int64_t* arr, int64_t* dp, int64_t n) {
    int64_t best = 1;
    for (int64_t i = 0; i < n; i++) dp[i] = 1;
    for (int64_t i = 1; i < n; i++) {
        for (int64_t j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                int64_t candidate = dp[j] + 1;
                if (candidate > dp[i]) dp[i] = candidate;
            }
        }
        if (dp[i] > best) best = dp[i];
    }
    return best;
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 100;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 42 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        checksum += lis(arr, dp, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(dp);
    return 0;
}