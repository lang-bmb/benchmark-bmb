// String Decode — run-length decode simulation
// Measures: sequential scan, accumulator pattern
// Workload: N=1000000 encoded, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 500;
    int64_t* encoded = (int64_t*)malloc(N * sizeof(int64_t)); // pairs: count, value
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate encoded pairs
        for (int64_t i = 0; i < N; i += 2) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            encoded[i] = seed % 5 + 1; // count 1-5
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            encoded[i+1] = seed % 100; // value 0-99
        }

        // Decode and compute sum without allocating decoded array
        int64_t total = 0;
        int64_t decoded_len = 0;
        int64_t max_val = 0;
        int64_t prev_val = -1;
        int64_t transitions = 0;

        for (int64_t i = 0; i < N; i += 2) {
            int64_t count = encoded[i];
            int64_t value = encoded[i+1];
            total += count * value;
            decoded_len += count;
            if (value > max_val) max_val = value;
            if (prev_val != -1 && prev_val != value) transitions++;
            prev_val = value;
        }
        checksum += total + decoded_len + max_val + transitions;
    }
    printf("%lld\n", (long long)checksum);
    free(encoded);
    return 0;
}
