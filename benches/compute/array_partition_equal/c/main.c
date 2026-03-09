// Equal Sum Partition — DP subset sum variant
// Measures: 1D DP boolean array, backward scan
// Workload: N=200, target=5000, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 200;
    int64_t ITERS = 5000;
    int64_t MAX_SUM = 10001;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dp = (int64_t*)malloc(MAX_SUM * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t total = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100 + 1;
            total += arr[i];
        }

        int64_t result = 0;
        if (total % 2 == 0) {
            int64_t target = total / 2;
            if (target < MAX_SUM) {
                memset(dp, 0, MAX_SUM * sizeof(int64_t));
                dp[0] = 1;

                for (int64_t i = 0; i < N; i++) {
                    for (int64_t j = target; j >= arr[i]; j--) {
                        if (dp[j - arr[i]]) dp[j] = 1;
                    }
                }
                result = dp[target];
            }
        }
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(dp);
    return 0;
}
