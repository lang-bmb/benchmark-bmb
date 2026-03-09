// array_min_jumps — Minimum jumps to reach end (greedy BFS)
// Measures: register-carried cur_end/farthest/jumps tracking
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t min_jumps(const int64_t* arr, int64_t n) {
    if (n <= 1) return 0;
    int64_t jumps = 0;
    int64_t cur_end = 0;
    int64_t farthest = 0;
    for (int64_t i = 0; i < n - 1; i++) {
        int64_t reach = i + arr[i];
        if (reach > farthest) farthest = reach;
        if (i == cur_end) {
            jumps++;
            cur_end = farthest;
            if (cur_end >= n - 1) break;
        }
    }
    return jumps;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 10) + 1;  // jump 1..10
        }
        checksum += min_jumps(arr, N);
        seed = (seed + iter) & 0x7FFFFFFF;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
