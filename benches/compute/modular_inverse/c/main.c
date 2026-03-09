// Modular Inverse — compute modular multiplicative inverse via extended GCD
// Measures: division, modulo, data-dependent iteration
// Workload: 10000000 iterations

#include <stdio.h>
#include <stdint.h>

int64_t mod_inverse(int64_t a, int64_t m) {
    int64_t old_r = a, r = m;
    int64_t old_s = 1, s = 0;
    while (r != 0) {
        int64_t q = old_r / r;
        int64_t tmp_r = r;
        r = old_r - q * r;
        old_r = tmp_r;
        int64_t tmp_s = s;
        s = old_s - q * s;
        old_s = tmp_s;
    }
    return old_s < 0 ? old_s + m : old_s;
}

int main() {
    int64_t ITERS = 10000000;
    int64_t m = 1000000007;
    int64_t checksum = 0;
    int64_t seed = 42;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t a = (seed % (m - 1)) + 1;
        checksum = (checksum + mod_inverse(a, m)) % m;
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
