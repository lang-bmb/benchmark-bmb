// Levenshtein edit distance benchmark — 2D DP array access
// Measures: 2D array access patterns, min operations, loop performance
// Workload: 500-char strings, 200 iterations
// DP array pre-allocated once outside loop (measures pure computation)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t levenshtein(const int64_t* s, int64_t slen, const int64_t* t, int64_t tlen, int64_t* dp) {
    int64_t cols = tlen + 1;

    for (int64_t i = 0; i <= slen; i++) dp[i * cols + 0] = i;
    for (int64_t j = 0; j <= tlen; j++) dp[0 * cols + j] = j;

    for (int64_t i = 1; i <= slen; i++) {
        for (int64_t j = 1; j <= tlen; j++) {
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
    return dp[slen * cols + tlen];
}

int main() {
    int64_t LEN = 500;
    int64_t ITERS = 200;

    int64_t* s = (int64_t*)malloc(LEN * sizeof(int64_t));
    int64_t* t = (int64_t*)malloc(LEN * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc((LEN + 1) * (LEN + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 42 + iter;
        for (int64_t i = 0; i < LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            s[i] = seed % 26;
        }
        for (int64_t i = 0; i < LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            t[i] = seed % 26;
        }
        checksum += levenshtein(s, LEN, t, LEN, dp);
    }

    printf("%lld\n", (long long)checksum);
    free(s);
    free(t);
    free(dp);
    return 0;
}
