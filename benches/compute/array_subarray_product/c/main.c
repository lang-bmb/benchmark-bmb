// array_subarray_product — Count subarrays with product < K
// Measures: sliding window with register-carried product tracking
// Workload: N=500000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t count_subarrays(const int64_t* arr, int64_t n, int64_t k) {
    if (k <= 1) return 0;
    int64_t count = 0;
    int64_t product = 1;
    int64_t left = 0;
    for (int64_t right = 0; right < n; right++) {
        product *= arr[right];
        while (product >= k && left <= right) {
            product /= arr[left];
            left++;
        }
        count += (right - left + 1);
    }
    return count;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t K = 100000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 10) + 1;  // values 1..10
        }
        checksum += count_subarrays(arr, N, K);
        seed = (seed + iter) & 0x7FFFFFFF;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
