// Bit Manipulation benchmark — popcount, leading zeros, trailing zeros, reverse bits
// Measures: bitwise operations, loop performance
// Workload: 4 operations on 500000 random numbers, 200 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t popcount(int64_t x) {
    int64_t count = 0;
    int64_t u = x;
    while (u != 0) {
        u = u & (u - 1);
        count++;
    }
    return count;
}

static int64_t leading_zeros(int64_t x) {
    if (x == 0) return 64;
    int64_t count = 0;
    // Check from bit 30 down (31-bit LCG values)
    for (int64_t bit = 30; bit >= 0; bit--) {
        int64_t mask = 1LL << bit;
        if ((x & mask) != 0) {
            break;
        }
        count++;
    }
    return count;
}

static int64_t trailing_zeros(int64_t x) {
    if (x == 0) return 64;
    int64_t count = 0;
    int64_t u = x;
    while ((u & 1) == 0) {
        count++;
        u >>= 1;
    }
    return count;
}

static int64_t reverse_bits(int64_t x) {
    // Reverse lower 31 bits
    int64_t result = 0;
    int64_t u = x;
    for (int64_t i = 0; i < 31; i++) {
        result = (result << 1) | (u & 1);
        u >>= 1;
    }
    return result;
}

int main() {
    int64_t n = 500000;
    int64_t iters = 200;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        int64_t seed = 98765 + iter;
        for (int64_t i = 0; i < n; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t pc = popcount(seed);
            int64_t lz = leading_zeros(seed);
            int64_t tz = trailing_zeros(seed);
            int64_t rb = reverse_bits(seed);
            // Sum all results; use modulo on rb to keep values manageable
            checksum += pc + lz + tz + (rb & 255);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
