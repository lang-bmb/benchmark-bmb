// Kadane 1D — maximum subarray sum (classic Kadane's algorithm)
// Measures: sequential scan, simple DP, branch prediction
// Workload: N=200000 array, 10000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t kadane(const int64_t* arr, int64_t n) {
    int64_t max_sum = arr[0];
    int64_t cur_sum = arr[0];
    for (int64_t i = 1; i < n; i++) {
        cur_sum = arr[i] + ((cur_sum > 0) ? cur_sum : 0);
        if (cur_sum > max_sum) max_sum = cur_sum;
    }
    return max_sum;
}

int main() {
    int64_t N = 200000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 201) - 100;  // -100 to 100
        }
        checksum += kadane(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
