// Array Majority Moore — Boyer-Moore majority vote (single pass candidate)
// Measures: register carry (candidate, count), branch prediction
// Workload: N=2000000 array, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t majority_moore(const int64_t* arr, int64_t n) {
    // Phase 1: find candidate
    int64_t candidate = arr[0];
    int64_t count = 1;
    for (int64_t i = 1; i < n; i++) {
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        } else if (arr[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }
    // Phase 2: verify
    int64_t freq = 0;
    for (int64_t i = 0; i < n; i++) {
        if (arr[i] == candidate) freq++;
    }
    return (freq > n / 2) ? candidate : -1;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t maj_val = iter % 7;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            if (seed % 3 == 0) {
                arr[i] = seed % 20;
            } else {
                arr[i] = maj_val;
            }
        }
        checksum += majority_moore(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
