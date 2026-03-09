// Array Equilibrium — find index where left sum equals right sum
// Measures: prefix sum, sequential scan
// Workload: N=1000000, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 201) - 100;  // [-100, 100]
        }

        int64_t total = 0;
        for (int64_t i = 0; i < N; i++) total += arr[i];

        int64_t left_sum = 0;
        int64_t eq_idx = -1;
        for (int64_t i = 0; i < N; i++) {
            int64_t right_sum = total - left_sum - arr[i];
            if (left_sum == right_sum) {
                eq_idx = i;
                break;
            }
            left_sum += arr[i];
        }
        checksum += eq_idx;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
