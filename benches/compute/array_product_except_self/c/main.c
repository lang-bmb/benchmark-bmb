// Array Product Except Self — product of all elements except current
// Measures: prefix/suffix product, sequential scan
// Workload: N=500000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* out = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = (seed % 5) + 1;  // Small values to avoid overflow
        }

        // Left prefix product
        out[0] = 1;
        for (int64_t i = 1; i < N; i++) {
            out[i] = out[i - 1] * arr[i - 1];
        }

        // Right suffix product and multiply
        int64_t right = 1;
        for (int64_t i = N - 1; i >= 0; i--) {
            out[i] *= right;
            right *= arr[i];
        }

        checksum += out[0] + out[N / 2] + out[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(out);
    return 0;
}
