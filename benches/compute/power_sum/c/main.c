// Power Sum — compute sum of i^k for large arrays
// Measures: integer multiplication, modular arithmetic, loop
// Workload: N=2M elements, k=7, 20 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t power_mod(int64_t base, int64_t exp, int64_t modulus) {
    int64_t result = 1;
    int64_t b = base % modulus;
    int64_t e = exp;
    while (e > 0) {
        if (e & 1) result = (result * b) % modulus;
        e >>= 1;
        b = (b * b) % modulus;
    }
    return result;
}

int main() {
    int64_t N = 2000000;
    int64_t K = 7;
    int64_t modulus = 1000000007;
    int64_t ITERS = 20;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t total = 0;
        for (int64_t i = 1; i <= N; i++) {
            total = (total + power_mod(i + iter, K, modulus)) % modulus;
        }
        checksum = (checksum + total) % modulus;
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}