// Longest Common Subsequence benchmark — 2D dynamic programming
// Measures: 2D array access, max operations, string comparison
// Workload: 1000-char strings, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SLEN 1000
#define ITERS 200

static int64_t lcs(const int64_t* s, int64_t slen, const int64_t* t, int64_t tlen, int64_t* dp) {
    int64_t cols = tlen + 1;
    // Initialize first row and column to 0
    for (int64_t i = 0; i <= slen; i++) dp[i * cols] = 0;
    for (int64_t j = 0; j <= tlen; j++) dp[j] = 0;
    // Fill DP table
    for (int64_t i = 1; i <= slen; i++) {
        for (int64_t j = 1; j <= tlen; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i * cols + j] = dp[(i - 1) * cols + (j - 1)] + 1;
            } else {
                int64_t a = dp[(i - 1) * cols + j];
                int64_t b = dp[i * cols + (j - 1)];
                dp[i * cols + j] = (a > b) ? a : b;
            }
        }
    }
    return dp[slen * cols + tlen];
}

int main() {
    int64_t* s = (int64_t*)malloc(SLEN * sizeof(int64_t));
    int64_t* t = (int64_t*)malloc(SLEN * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc((SLEN + 1) * (SLEN + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 65535 + iter;
        for (int64_t i = 0; i < SLEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            s[i] = seed % 26;
        }
        for (int64_t i = 0; i < SLEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            t[i] = seed % 26;
        }
        checksum += lcs(s, SLEN, t, SLEN, dp);
    }
    printf("%lld\n", (long long)checksum);
    free(s); free(t); free(dp);
    return 0;
}
