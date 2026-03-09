// Radix sort benchmark — counting sort + bit extraction
// Measures: array traversal, counting, memory write patterns
// Workload: 500K elements, 8-byte keys, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 500000
#define RADIX 256
#define ITERS 200

static void radix_sort(int64_t* arr, int64_t* tmp, int64_t n) {
    int64_t count[RADIX];
    // Sort by each byte (8 bytes = 8 passes for full sort, use 4 passes for benchmark)
    for (int64_t pass = 0; pass < 4; pass++) {
        int64_t shift = pass * 8;
        for (int64_t i = 0; i < RADIX; i++) count[i] = 0;
        for (int64_t i = 0; i < n; i++) {
            int64_t byte_val = (arr[i] >> shift) & 0xFF;
            count[byte_val]++;
        }
        // Prefix sum
        for (int64_t i = 1; i < RADIX; i++) count[i] += count[i - 1];
        // Scatter (stable, reverse order)
        for (int64_t i = n - 1; i >= 0; i--) {
            int64_t byte_val = (arr[i] >> shift) & 0xFF;
            count[byte_val]--;
            tmp[count[byte_val]] = arr[i];
        }
        // Copy back
        for (int64_t i = 0; i < n; i++) arr[i] = tmp[i];
    }
}

int main() {
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* tmp = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate pseudo-random data
        int64_t seed = 54321 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        radix_sort(arr, tmp, N);
        // Checksum: sum of first, middle, last elements
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(tmp);
    return 0;
}
