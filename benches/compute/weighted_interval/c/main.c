// Weighted Interval Scheduling — DP with binary search
// Measures: sorting, binary search, DP table fill
// Workload: N=5000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void sort_by_end(int64_t* starts, int64_t* ends, int64_t* weights, int64_t n) {
    for (int64_t i = 1; i < n; i++) {
        int64_t es = starts[i], ee = ends[i], ew = weights[i];
        int64_t j = i - 1;
        while (j >= 0 && ends[j] > ee) {
            starts[j + 1] = starts[j];
            ends[j + 1] = ends[j];
            weights[j + 1] = weights[j];
            j--;
        }
        starts[j + 1] = es;
        ends[j + 1] = ee;
        weights[j + 1] = ew;
    }
}

static int64_t find_prev(const int64_t* ends, int64_t n, int64_t start) {
    int64_t lo = 0, hi = n - 1, result = -1;
    while (lo <= hi) {
        int64_t mid = lo + (hi - lo) / 2;
        if (ends[mid] <= start) {
            result = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return result;
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 500;
    int64_t* starts = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* ends = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* weights = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            starts[i] = seed % 100000;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            ends[i] = starts[i] + 1 + seed % 1000;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            weights[i] = 1 + seed % 100;
        }

        sort_by_end(starts, ends, weights, N);

        dp[0] = weights[0];
        for (int64_t i = 1; i < N; i++) {
            int64_t include = weights[i];
            int64_t p = find_prev(ends, i, starts[i]);
            if (p >= 0) include += dp[p];
            dp[i] = (include > dp[i - 1]) ? include : dp[i - 1];
        }

        checksum += dp[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(starts);
    free(ends);
    free(weights);
    free(dp);
    return 0;
}
