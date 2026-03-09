// First Missing Positive — in-place swap to position
// Measures: swap-to-place, sequential scan
// Workload: N=1000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % (N + 10)) - 5; // some negatives, some > N
        }

        // Place each number at its correct position
        for (int64_t i = 0; i < N; i++) {
            while (arr[i] > 0 && arr[i] <= N && arr[arr[i]-1] != arr[i]) {
                int64_t pos = arr[i] - 1;
                int64_t t = arr[i]; arr[i] = arr[pos]; arr[pos] = t;
            }
        }

        // Find first missing positive
        int64_t result = N + 1;
        for (int64_t i = 0; i < N; i++) {
            if (arr[i] != i + 1) {
                result = i + 1;
                break;
            }
        }
        checksum += result;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
