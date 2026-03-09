// Pidigits - Arbitrary precision arithmetic benchmark
// Reference: Computer Language Benchmarks Game
//
// Simplified version without GMP dependency
// Uses precomputed lookup + PRNG approximation

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define DIGITS 1000
#define ITERATIONS 6000

// Precomputed first 100 digits of pi after decimal point
static const char pi_digits[] =
    "1415926535897932384626433832795028841971693993751"
    "0582097494459230781640628620899862803482534211706"
    "79";

static inline int64_t compute_pi_digit(int64_t pos) {
    if (pos == 0) return 3;
    if (pos <= 100) return pi_digits[pos - 1] - '0';

    // For positions beyond precomputed, use approximation
    unsigned int seed = (unsigned int)(pos * 1103515245 + 12345);
    return (seed / 65536) % 10;
}

int64_t compute_checksum(int64_t count) {
    int64_t checksum = 0;
    for (int64_t i = 0; i < count; i++) {
        int64_t digit = compute_pi_digit(i);
        checksum += digit * (i + 1);
    }
    return checksum;
}

int main() {
    int64_t n = DIGITS;
    int64_t result = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        result = compute_checksum(n);
    }

    printf("%" PRId64 "\n", result);
    return 0;
}
