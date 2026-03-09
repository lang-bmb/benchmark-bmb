// Bit Reverse — reverse bits of 64-bit integers
// Measures: bit manipulation, shift operations
// Workload: N=1000000 values, 1000 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t reverse_bits(int64_t x) {
    int64_t r = 0;
    for (int i = 0; i < 64; i++) {
        r = (r << 1) | (x & 1);
        x >>= 1;
    }
    return r;
}

int main() {
    int64_t N = 1000000;
    int64_t ITERS = 1000;

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            checksum += reverse_bits(seed);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
