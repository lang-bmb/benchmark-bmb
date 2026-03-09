// Running Max — compute running maximum of an array
// Measures: sequential read/write, conditional update
// Workload: N=1000000, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 5000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* out = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        out[0] = arr[0];
        for (int64_t i = 1; i < N; i++) {
            out[i] = (arr[i] > out[i - 1]) ? arr[i] : out[i - 1];
        }
        checksum += out[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(out);
    return 0;
}
