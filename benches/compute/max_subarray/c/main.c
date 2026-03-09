// Max Subarray — Kadane's algorithm
// Measures: linear scan, conditional max tracking
// Workload: N=100K elements, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 100000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 2001 - 1000;
        }
        // Kadane's algorithm
        int64_t max_ending_here = 0;
        int64_t max_so_far = arr[0];
        for (int64_t i = 0; i < N; i++) {
            max_ending_here = max_ending_here + arr[i];
            if (max_ending_here < 0) {
                max_ending_here = 0;
            }
            if (max_ending_here > max_so_far) {
                max_so_far = max_ending_here;
            }
        }
        checksum += max_so_far;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
