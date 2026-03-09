// Modular Exponentiation — compute (base^exp) % mod
// Measures: integer multiplication, modular arithmetic, binary exponentiation
// Workload: 500000 computations, 200 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t mod_pow(int64_t base, int64_t exp, int64_t m) {
    int64_t result = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % m;
        exp >>= 1;
        base = (base * base) % m;
    }
    return result;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 200;
    int64_t M = 1000000007;

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t base = (seed % 1000) + 2;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t exp = (seed % 1000000) + 1;
            checksum += mod_pow(base, exp, M);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
