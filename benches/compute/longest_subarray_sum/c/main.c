// Longest Subarray with Sum <= K — sliding window
// Measures: two-pointer technique, conditional logic
// Workload: N=500000, K=5000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t longest_subarray(const int64_t* arr, int64_t n, int64_t k) {
    int64_t left = 0, sum = 0, best = 0;
    for (int64_t right = 0; right < n; right++) {
        sum += arr[right];
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }
        int64_t len = right - left + 1;
        if (len > best) best = len;
    }
    return best;
}

int main() {
    int64_t N = 500000;
    int64_t K = 5000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100;
        }
        checksum += longest_subarray(arr, N, K + iter);
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
