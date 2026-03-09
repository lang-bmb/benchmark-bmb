// Sliding Window Maximum — deque-based O(n) algorithm
// Measures: deque operations, sequential access, branch prediction
// Workload: N=200000 array, window=100, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t sliding_window_max_sum(const int64_t* arr, int64_t n, int64_t k,
                                       int64_t* deq) {
    int64_t front = 0, back = 0;  // deque indices
    int64_t sum = 0;

    for (int64_t i = 0; i < n; i++) {
        // Remove elements outside window
        while (front < back && deq[front] <= i - k) front++;
        // Remove smaller elements from back
        while (front < back && arr[deq[back - 1]] <= arr[i]) back--;
        deq[back++] = i;
        if (i >= k - 1) {
            sum += arr[deq[front]];
        }
    }
    return sum;
}

int main() {
    int64_t N = 200000;
    int64_t K = 100;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* deq = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000000;
        }
        checksum += sliding_window_max_sum(arr, N, K, deq);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(deq);
    return 0;
}
