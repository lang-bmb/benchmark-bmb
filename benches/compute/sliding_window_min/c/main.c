// Sliding Window Minimum — deque-based sliding window min
// Measures: deque operations, index arithmetic
// Workload: N=500000, window=1000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t W = 1000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* deque = (int64_t*)malloc(N * sizeof(int64_t));  // monotonic deque of indices
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000000;
        }

        int64_t front = 0, back = 0;  // [front, back)
        int64_t sum = 0;

        for (int64_t i = 0; i < N; i++) {
            // Remove elements outside window
            while (front < back && deque[front] <= i - W) front++;
            // Remove elements larger than arr[i] from back
            while (front < back && arr[deque[back - 1]] >= arr[i]) back--;
            deque[back++] = i;
            // After first window is full, accumulate min
            if (i >= W - 1) {
                sum += arr[deque[front]];
            }
        }
        checksum += sum;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(deque);
    return 0;
}
