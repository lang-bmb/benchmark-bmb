// Modular Exponentiation — fast power with modulus
// Measures: integer arithmetic, bit operations, loop
// Workload: 10M exponentiation calls

#include <stdio.h>
#include <stdint.h>

static int64_t mod_pow(int64_t base, int64_t exp, int64_t modulus) {
    int64_t result = 1;
    int64_t b = base % modulus;
    int64_t e = exp;
    while (e > 0) {
        if (e & 1) {
            result = (result * b) % modulus;
        }
        e >>= 1;
        b = (b * b) % modulus;
    }
    return result;
}

int main() {
    int64_t N = 10000000;
    int64_t modulus = 1000000007;

    int64_t checksum = 0;
    for (int64_t i = 1; i <= N; i++) {
        checksum = (checksum + mod_pow(i, i % 100 + 1, modulus)) % modulus;
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}