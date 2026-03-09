// Bitcount benchmark — population count (Hamming weight)
// Measures: bitwise operations, loop performance, branch prediction
// Workload: count bits in 10M numbers, 30 iterations

#include <stdio.h>
#include <stdint.h>

// Brian Kernighan's bit counting (no __builtin_popcount — fair comparison)
static int64_t popcount_manual(int64_t x) {
    int64_t count = 0;
    // Work with unsigned representation
    uint64_t u = (uint64_t)x;
    while (u) {
        u &= u - 1;
        count++;
    }
    return count;
}

int main() {
    int64_t N = 10000000;
    int64_t ITERS = 30;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 54321 + iter;
        int64_t sum = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            sum += popcount_manual(seed);
        }
        checksum += sum;
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
