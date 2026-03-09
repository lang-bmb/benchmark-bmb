// Decode Ways — DP count decodings (like Leetcode 91)
// Measures: register carry (prev/prev2), sequential scan
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* digits = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            digits[i] = seed % 3 + 1; // 1-3 to avoid 0
        }

        // dp[i] = ways to decode digits[0..i]
        int64_t prev2 = 1; // dp[-1]
        int64_t prev1 = 1; // dp[0] - single digit always valid

        for (int64_t i = 1; i < N; i++) {
            int64_t cur = 0;
            // Single digit decode (always valid for 1-3)
            cur += prev1;
            // Two digit decode (valid if 10-26, our range 11-33 means 11-26 valid)
            int64_t two = digits[i-1] * 10 + digits[i];
            if (two >= 10 && two <= 26) {
                cur += prev2;
            }
            // Prevent overflow
            cur = cur % 1000000007;
            prev2 = prev1;
            prev1 = cur;
        }
        checksum += prev1;
    }
    printf("%lld\n", (long long)checksum);
    free(digits);
    return 0;
}
