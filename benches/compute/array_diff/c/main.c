// Array Diff — compute first differences of array
// Measures: sequential read, subtraction, write
// Workload: N=1000000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* diff = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed % 10000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        diff[0] = arr[0];
        for (int64_t i = 1; i < N; i++) {
            diff[i] = arr[i] - arr[i - 1];
        }
        checksum += diff[0] + diff[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(diff);
    return 0;
}
