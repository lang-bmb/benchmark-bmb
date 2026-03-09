// Min Cost Climbing Stairs — DP with register carry
// Measures: register-carry (prev/prev2), sequential scan
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* cost = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            cost[i] = seed % 1000;
        }

        // dp[i] = cost[i] + min(dp[i-1], dp[i-2])
        int64_t prev2 = cost[0];
        int64_t prev1 = cost[1];

        for (int64_t i = 2; i < N; i++) {
            int64_t cur = cost[i] + ((prev1 < prev2) ? prev1 : prev2);
            prev2 = prev1;
            prev1 = cur;
        }
        int64_t result = (prev1 < prev2) ? prev1 : prev2;
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(cost);
    return 0;
}
