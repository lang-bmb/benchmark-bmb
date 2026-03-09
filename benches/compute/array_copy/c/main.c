// Array Copy — copy one array to another
// Measures: sequential read/write, memory bandwidth
// Workload: N=1000000, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 5000;
    int64_t* src = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dst = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        src[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            dst[i] = src[i];
        }
        checksum += dst[0] + dst[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(src);
    free(dst);
    return 0;
}
