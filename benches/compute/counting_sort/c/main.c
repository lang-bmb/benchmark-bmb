// Counting sort benchmark — O(n+k) non-comparison sort
// Measures: sequential memory access, counting, prefix sum, scatter
// Workload: 500K elements, range 0-9999, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static void counting_sort(int64_t* arr, int64_t* out, int64_t n, int64_t k) {
    int64_t* count = (int64_t*)calloc(k, sizeof(int64_t));
    // Count occurrences
    for (int64_t i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    // Prefix sum
    for (int64_t i = 1; i < k; i++) {
        count[i] += count[i - 1];
    }
    // Scatter (reverse for stability)
    for (int64_t i = n - 1; i >= 0; i--) {
        int64_t val = arr[i];
        count[val]--;
        out[count[val]] = val;
    }
    free(count);
}

int main() {
    int64_t N = 500000;
    int64_t K = 10000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* out = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 54321 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % K;
        }
        counting_sort(arr, out, N, K);
        checksum += out[0] + out[N / 2] + out[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(out);
    return 0;
}
