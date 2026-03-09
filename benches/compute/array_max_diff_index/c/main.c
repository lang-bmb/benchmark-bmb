// Max Diff Index — max (arr[j] - arr[i]) where j > i
// Measures: register-carry (running min), sequential scan
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
            arr[i] = seed % 100000;
        }
        int64_t min_val = arr[0];
        int64_t max_diff = 0;
        for (int64_t i = 1; i < N; i++) {
            int64_t diff = arr[i] - min_val;
            if (diff > max_diff) max_diff = diff;
            if (arr[i] < min_val) min_val = arr[i];
        }
        checksum += max_diff;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
