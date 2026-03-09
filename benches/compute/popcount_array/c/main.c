// Popcount Array — count total set bits across an array
// Measures: bitwise ops, loop, shift, branch-free popcount
// Workload: N=1000000, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t popcount(int64_t x) {
    int64_t count = 0;
    while (x != 0) {
        x = x & (x - 1);
        count++;
    }
    return count;
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t total = 0;
        for (int64_t i = 0; i < N; i++) {
            total += popcount(arr[i]);
        }
        checksum += total;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
