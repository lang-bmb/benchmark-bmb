// Array Min Max Pairs — find min and max with 3n/2 comparisons
// Measures: register carry (cur_min, cur_max), pair comparison trick
// Workload: N=2000000 array, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t min_max_pairs(const int64_t* arr, int64_t n) {
    if (n == 0) return 0;
    int64_t lo, hi;
    int64_t start;
    if (n % 2 == 0) {
        if (arr[0] < arr[1]) { lo = arr[0]; hi = arr[1]; }
        else { lo = arr[1]; hi = arr[0]; }
        start = 2;
    } else {
        lo = arr[0]; hi = arr[0];
        start = 1;
    }
    for (int64_t i = start; i < n - 1; i += 2) {
        int64_t a = arr[i], b = arr[i + 1];
        int64_t small, big;
        if (a < b) { small = a; big = b; }
        else { small = b; big = a; }
        if (small < lo) lo = small;
        if (big > hi) hi = big;
    }
    return hi - lo;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000000;
        }
        checksum += min_max_pairs(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
