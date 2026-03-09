// 0/1 Knapsack benchmark — 1D DP array access
// Measures: 1D array access, conditional updates, loop performance
// Workload: 2000 items, capacity 5000, 50 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t knapsack(int64_t n, int64_t capacity, const int64_t* weights, const int64_t* values, int64_t* dp) {
    for (int64_t j = 0; j <= capacity; j++) dp[j] = 0;

    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = capacity; j >= weights[i]; j--) {
            int64_t take = dp[j - weights[i]] + values[i];
            if (take > dp[j]) dp[j] = take;
        }
    }
    return dp[capacity];
}

int main() {
    int64_t N = 2000;
    int64_t CAP = 5000;
    int64_t ITERS = 50;

    int64_t* weights = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* values = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc((CAP + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 777 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            weights[i] = (seed % 50) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            values[i] = (seed % 100) + 1;
        }
        checksum += knapsack(N, CAP, weights, values, dp);
    }

    printf("%lld\n", (long long)checksum);
    free(weights);
    free(values);
    free(dp);
    return 0;
}
