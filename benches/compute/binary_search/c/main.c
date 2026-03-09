// Binary search benchmark — O(log n) search on sorted array
// Measures: branch prediction, cache access patterns, integer comparison
// Workload: 1M elements, 5M lookups per iteration, 20 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t binary_search(int64_t* arr, int64_t n, int64_t target) {
    int64_t lo = 0, hi = n - 1;
    while (lo <= hi) {
        int64_t mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    int64_t N = 1000000;
    int64_t LOOKUPS = 5000000;
    int64_t ITERS = 20;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    // Fill sorted array: arr[i] = i * 3
    for (int64_t i = 0; i < N; i++) {
        arr[i] = i * 3;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 42 + iter;
        for (int64_t lk = 0; lk < LOOKUPS; lk++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t target = (seed % N) * 3;
            int64_t idx = binary_search(arr, N, target);
            checksum += idx;
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
