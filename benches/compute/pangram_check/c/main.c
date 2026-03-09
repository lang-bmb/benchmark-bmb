// Pangram Check — check if array contains all values in range [0,K)
// Measures: boolean array marking, early exit
// Workload: N=100000, K=256, 20000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 100000;
    int64_t K = 256;
    int64_t ITERS = 20000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* seen = (int64_t*)malloc(K * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % K;
        }

        memset(seen, 0, K * sizeof(int64_t));
        int64_t unique = 0;
        for (int64_t i = 0; i < N; i++) {
            if (!seen[arr[i]]) {
                seen[arr[i]] = 1;
                unique++;
                if (unique == K) break;
            }
        }
        checksum += unique;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(seen);
    return 0;
}
