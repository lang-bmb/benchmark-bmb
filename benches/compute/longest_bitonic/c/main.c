// Longest Bitonic Subsequence — two-pass DP (LIS + LDS)
// Measures: sequential DP, register tracking
// Workload: N=5000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 5000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* lis = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* lds = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }

        // LIS: longest increasing subsequence ending at i
        for (int64_t i = 0; i < N; i++) {
            lis[i] = 1;
            for (int64_t j = 0; j < i; j++) {
                if (arr[j] < arr[i] && lis[j] + 1 > lis[i]) {
                    lis[i] = lis[j] + 1;
                }
            }
        }

        // LDS: longest decreasing subsequence starting at i
        for (int64_t i = N - 1; i >= 0; i--) {
            lds[i] = 1;
            for (int64_t j = i + 1; j < N; j++) {
                if (arr[j] < arr[i] && lds[j] + 1 > lds[i]) {
                    lds[i] = lds[j] + 1;
                }
            }
        }

        // Find max bitonic length
        int64_t max_len = 0;
        for (int64_t i = 0; i < N; i++) {
            int64_t len = lis[i] + lds[i] - 1;
            if (len > max_len) max_len = len;
        }
        checksum += max_len;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(lis);
    free(lds);
    return 0;
}
