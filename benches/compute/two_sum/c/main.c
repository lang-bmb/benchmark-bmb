// Two Sum — brute force O(n²) pair finding
// Measures: nested loop, sequential access, comparison
// Workload: N=5000 array, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t two_sum_count(const int64_t* arr, int64_t n, int64_t target) {
    int64_t count = 0;
    for (int64_t i = 0; i < n - 1; i++) {
        for (int64_t j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) count++;
        }
    }
    return count;
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100;
        }
        int64_t target = 50 + (iter % 100);
        checksum += two_sum_count(arr, N, target);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
