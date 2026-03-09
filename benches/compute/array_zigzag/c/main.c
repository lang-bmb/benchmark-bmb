// Array Zigzag — find longest zigzag subsequence length
// Measures: sequential scan with state tracking
// Workload: N=500000, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }

        // Zigzag: alternating up/down differences
        int64_t up = 1, down = 1;
        for (int64_t i = 1; i < N; i++) {
            if (arr[i] > arr[i - 1]) {
                up = down + 1;
            } else if (arr[i] < arr[i - 1]) {
                down = up + 1;
            }
        }
        int64_t result = up > down ? up : down;
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
