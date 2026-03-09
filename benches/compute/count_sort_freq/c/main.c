// Count Sort Frequency — count occurrences of each value
// Measures: random access writes (histogram), sequential scan
// Workload: N=1000000 array, range 0-999, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t RANGE = 1000;
    int64_t ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* freq = (int64_t*)malloc(RANGE * sizeof(int64_t));

    int64_t seed = 42;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % RANGE;
        }
        for (int64_t i = 0; i < RANGE; i++) freq[i] = 0;
        for (int64_t i = 0; i < N; i++) {
            freq[arr[i]]++;
        }
        int64_t mx = 0;
        for (int64_t i = 0; i < RANGE; i++) {
            if (freq[i] > mx) mx = freq[i];
        }
        checksum += mx;
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(freq);
    return 0;
}
