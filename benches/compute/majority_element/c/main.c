// Majority Element — Boyer-Moore voting algorithm
// Measures: sequential scan, branch prediction, simple state
// Workload: N=500000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t majority_element(const int64_t* arr, int64_t n) {
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
    // Verify
    int64_t actual_count = 0;
    for (int64_t i = 0; i < n; i++) {
        if (arr[i] == candidate) actual_count++;
    }
    return (actual_count > n / 2) ? candidate : -1;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill with values 0-9, majority is iter%10
        int64_t maj_val = iter % 10;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            if (seed % 3 == 0) {
                arr[i] = seed % 10;
            } else {
                arr[i] = maj_val;
            }
        }
        checksum += majority_element(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
