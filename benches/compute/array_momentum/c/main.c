// Momentum — compute momentum (difference between current and N-back)
// Measures: register-carry, sequential scan with lookback
// Workload: N=2000000, 2000 iterations, lookback=4

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000, BACK = 4;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        int64_t max_momentum = 0;
        int64_t sum_momentum = 0;
        for (int64_t i = BACK; i < N; i++) {
            int64_t m = arr[i] - arr[i - BACK];
            sum_momentum += m;
            if (m > max_momentum) max_momentum = m;
        }
        checksum += max_momentum + sum_momentum % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
