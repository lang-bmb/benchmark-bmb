// Array Peaks — count elements greater than both neighbors
// Measures: sequential scan with neighbor comparison
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
            arr[i] = seed % 10000;
        }

        int64_t peaks = 0;
        for (int64_t i = 1; i < N - 1; i++) {
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
                peaks++;
            }
        }
        checksum += peaks;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
