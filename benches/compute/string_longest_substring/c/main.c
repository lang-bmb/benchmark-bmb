// Longest Substring Without Repeating Characters — sliding window
// Measures: hash table operations, window tracking
// Workload: N=500000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t last_seen[256];
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate "string" as array of chars 0-255
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 26; // a-z
        }

        memset(last_seen, -1, sizeof(last_seen));
        int64_t max_len = 0;
        int64_t start = 0;

        for (int64_t i = 0; i < N; i++) {
            int64_t ch = arr[i];
            if (last_seen[ch] >= start) {
                start = last_seen[ch] + 1;
            }
            last_seen[ch] = i;
            int64_t len = i - start + 1;
            if (len > max_len) max_len = len;
        }
        checksum += max_len;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
