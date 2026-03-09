// Moving Average — sliding window sum with register-carry
// Measures: register-carry (window sum), sequential scan
// Workload: N=2000000, 2000 iterations, window=8

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000, K = 8;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        // Compute initial window
        int64_t window_sum = 0;
        for (int64_t i = 0; i < K; i++) window_sum += arr[i];
        int64_t max_avg = window_sum;
        // Slide window
        for (int64_t i = K; i < N; i++) {
            window_sum += arr[i] - arr[i - K];
            if (window_sum > max_avg) max_avg = window_sum;
        }
        checksum += max_avg;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
