// Two Pointer Sum — find pairs summing to target in sorted array
// Measures: two-pointer technique, branch prediction
// Workload: N=500000 sorted array, 1000 iterations with different targets

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t count_pairs(const int64_t* arr, int64_t n, int64_t target) {
    int64_t count = 0;
    int64_t lo = 0, hi = n - 1;
    while (lo < hi) {
        int64_t s = arr[lo] + arr[hi];
        if (s == target) {
            count++;
            lo++;
            hi--;
        } else if (s < target) {
            lo++;
        } else {
            hi--;
        }
    }
    return count;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    int64_t prev = 0;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        prev += (seed % 5) + 1;
        arr[i] = prev;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t target = arr[seed % N] + arr[(seed + 1) % N];
        checksum += count_pairs(arr, N, target);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
