// Array Mode — find most frequent element using counting
// Measures: counting array access, conditional max tracking
// Workload: N=500000, range=10000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 500000;
    int64_t RANGE = 10000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* counts = (int64_t*)malloc(RANGE * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % RANGE;
        }

        memset(counts, 0, RANGE * sizeof(int64_t));
        for (int64_t i = 0; i < N; i++) {
            counts[arr[i]]++;
        }

        int64_t mode = 0;
        int64_t max_count = 0;
        for (int64_t i = 0; i < RANGE; i++) {
            if (counts[i] > max_count) {
                max_count = counts[i];
                mode = i;
            }
        }
        checksum += mode + max_count;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(counts);
    return 0;
}
