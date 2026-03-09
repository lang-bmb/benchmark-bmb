// Array Swap Pairs — swap adjacent pairs in array
// Measures: sequential read/write, stride-2 access
// Workload: N=1000000, 10000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i + 1 < N; i += 2) {
            int64_t a = arr[i];
            int64_t b = arr[i + 1];
            arr[i] = b;
            arr[i + 1] = a;
        }
        checksum += arr[0] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
