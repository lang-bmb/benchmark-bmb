// Array Shift — left-shift all elements by one position
// Measures: sequential memory copy, cache performance
// Workload: N=1000000 array, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t first = arr[0];
        for (int64_t i = 0; i < N - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[N - 1] = first;
        checksum += arr[0] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
