// Array Local Minima Count — count elements smaller than neighbors
// Measures: register carry (prev, cur, next), sequential scan
// Workload: N=2000000, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }

        int64_t count = 0;
        int64_t prev = arr[0];
        int64_t cur = arr[1];

        for (int64_t i = 2; i < N; i++) {
            int64_t next = arr[i];
            if (cur < prev && cur < next) {
                count++;
            }
            prev = cur;
            cur = next;
        }
        checksum += count;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
