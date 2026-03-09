// Array Leaders — find elements greater than all elements to their right
// Measures: right-to-left scan, conditional tracking
// Workload: N=1000000, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }

        int64_t max_from_right = arr[N - 1];
        int64_t leader_count = 1;  // Last element is always a leader
        for (int64_t i = N - 2; i >= 0; i--) {
            if (arr[i] > max_from_right) {
                leader_count++;
                max_from_right = arr[i];
            }
        }
        checksum += leader_count + max_from_right;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
