// Power Mod Chain — chained modular exponentiation
// Measures: multiplication, modulo, loop iteration
// Workload: 10000000 iterations of chained modpow

#include <stdio.h>
#include <stdint.h>

int64_t powmod(int64_t base, int64_t exp, int64_t modulus) {
    int64_t result = 1;
    base %= modulus;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        exp >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    int64_t iters = 10000000;
    int64_t modulus = 1000000007;
    int64_t val = 3;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        val = powmod(val, 13, modulus);
        checksum += val;
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
