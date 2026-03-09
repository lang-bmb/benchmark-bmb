// Array Pair Sum Closest to Target — two-pointer on sorted
// Measures: two-pointer convergence, register carry
// Workload: N=200000, 500 iterations (includes insertion sort)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 200000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate sorted array
        int64_t val = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 5 + 1;
            arr[i] = val;
        }

        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t target = val / 2 + (seed % 1000) - 500;

        // Two-pointer closest pair sum
        int64_t left = 0, right = N - 1;
        int64_t best_diff = 0x7FFFFFFFFFFFFFFF;
        int64_t best_sum = 0;

        while (left < right) {
            int64_t sum = arr[left] + arr[right];
            int64_t diff = sum - target;
            if (diff < 0) diff = -diff;
            if (diff < best_diff) {
                best_diff = diff;
                best_sum = sum;
            }
            if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            } else {
                break;
            }
        }
        checksum += best_sum;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
