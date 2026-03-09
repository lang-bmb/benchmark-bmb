// Array Max Sliding Diff — max(arr[i] - min(arr[j])) for j in [i-k..i-1]
// Measures: register carry (running min), sequential scan, branch prediction
// Workload: N=500000 array, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t max_sliding_diff(const int64_t* arr, int64_t n, int64_t k) {
    if (n < 2 || k < 1) return 0;
    int64_t best = arr[1] - arr[0];
    int64_t window_min = arr[0];
    for (int64_t i = 1; i < n; i++) {
        int64_t diff = arr[i] - window_min;
        if (diff > best) best = diff;
        if (arr[i] < window_min) window_min = arr[i];
        // Reset window_min every k elements to simulate sliding window
        if (i % k == 0) window_min = arr[i];
    }
    return best;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t K = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }
        checksum += max_sliding_diff(arr, N, K);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
