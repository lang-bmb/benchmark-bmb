// array_max_diff_pair — Max arr[j]-arr[i] where j>i
// Measures: register-carried min tracking, sequential scan
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t max_diff_pair(const int64_t* arr, int64_t n) {
    int64_t min_so_far = arr[0];
    int64_t max_diff = arr[1] - arr[0];
    for (int64_t i = 1; i < n; i++) {
        int64_t diff = arr[i] - min_so_far;
        if (diff > max_diff) max_diff = diff;
        if (arr[i] < min_so_far) min_so_far = arr[i];
    }
    return max_diff;
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
            arr[i] = (seed % 201) - 100;
        }
        checksum += max_diff_pair(arr, N);
        seed = (seed + iter) & 0x7FFFFFFF;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
