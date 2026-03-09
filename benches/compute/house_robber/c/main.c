// House Robber — DP with register carry (prev/prev2)
// Measures: register-carry optimization pattern
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* nums = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            nums[i] = seed % 100;
        }

        // DP: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
        // Use register carry: prev1 = dp[i-1], prev2 = dp[i-2]
        int64_t prev2 = 0;
        int64_t prev1 = nums[0];

        for (int64_t i = 1; i < N; i++) {
            int64_t take = prev2 + nums[i];
            int64_t skip = prev1;
            int64_t cur = (take > skip) ? take : skip;
            prev2 = prev1;
            prev1 = cur;
        }
        checksum += prev1;
    }
    printf("%lld\n", (long long)checksum);
    free(nums);
    return 0;
}
