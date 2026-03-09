// Online Variance — Welford's online algorithm (integer approximation)
// Measures: register-carry (mean, M2), sequential scan
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        // Simplified integer Welford: track sum and sum_sq
        int64_t sum = 0, sum_sq = 0;
        for (int64_t i = 0; i < N; i++) {
            sum += arr[i];
            sum_sq += arr[i] * arr[i];
        }
        // variance * N = sum_sq - sum*sum/N
        int64_t var_n = sum_sq - (sum / N) * sum;
        checksum += var_n % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
