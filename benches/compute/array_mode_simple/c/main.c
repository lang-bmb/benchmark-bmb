// Mode Simple — find most frequent element (small range 0-999)
// Measures: array accumulation, max tracking
// Workload: N=2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 2000000, ITERS = 500, RANGE = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* freq = (int64_t*)malloc(RANGE * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % RANGE;
        }
        memset(freq, 0, RANGE * sizeof(int64_t));
        for (int64_t i = 0; i < N; i++) {
            freq[arr[i]]++;
        }
        int64_t max_freq = 0, mode_val = 0;
        for (int64_t i = 0; i < RANGE; i++) {
            if (freq[i] > max_freq) {
                max_freq = freq[i];
                mode_val = i;
            }
        }
        checksum += mode_val;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(freq);
    return 0;
}
