// Max Gap Sorted — find max gap between consecutive elements in sorted array
// Measures: register-carry (prev), sequential scan on sorted data
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate sorted array
        int64_t val = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 10;
            arr[i] = val;
        }
        int64_t max_gap = 0;
        for (int64_t i = 1; i < N; i++) {
            int64_t gap = arr[i] - arr[i-1];
            if (gap > max_gap) max_gap = gap;
        }
        checksum += max_gap;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
