// Bitonic Sort — parallel-friendly comparison-based sort
// Measures: bitonic merge network, sequential access patterns
// Workload: N=65536 (power of 2), 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void bitonic_sort(int64_t* arr, int64_t n) {
    for (int64_t k = 2; k <= n; k *= 2) {
        for (int64_t j = k / 2; j > 0; j /= 2) {
            for (int64_t i = 0; i < n; i++) {
                int64_t l = i ^ j;
                if (l > i) {
                    if ((i & k) == 0) {
                        if (arr[i] > arr[l]) {
                            int64_t tmp = arr[i];
                            arr[i] = arr[l];
                            arr[l] = tmp;
                        }
                    } else {
                        if (arr[i] < arr[l]) {
                            int64_t tmp = arr[i];
                            arr[i] = arr[l];
                            arr[l] = tmp;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int64_t N = 65536;
    int64_t ITERS = 100;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        bitonic_sort(arr, N);
        checksum += arr[0] + arr[N/2] + arr[N-1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
