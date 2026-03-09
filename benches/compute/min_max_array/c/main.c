// Min Max Array — find min and max in single pass
// Measures: conditional branches, sequential scan, comparison
// Workload: N=500000 array, 10000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t minmax(const int64_t* arr, int64_t n) {
    int64_t mn = arr[0], mx = arr[0];
    for (int64_t i = 1; i < n; i++) {
        if (arr[i] < mn) mn = arr[i];
        if (arr[i] > mx) mx = arr[i];
    }
    return mn + mx;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        checksum += minmax(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
