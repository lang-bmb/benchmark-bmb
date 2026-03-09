// Catalan Numbers — DP computation with modular arithmetic
// Measures: nested loop DP, modular multiplication, sequential access
// Workload: C(0)..C(5000) via DP, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t catalan_dp(int64_t* cat, int64_t n, int64_t mod) {
    cat[0] = 1;
    cat[1] = 1;
    for (int64_t i = 2; i <= n; i++) {
        cat[i] = 0;
        for (int64_t j = 0; j < i; j++) {
            int64_t prod = (cat[j] * cat[i - 1 - j]) % mod;
            cat[i] = (cat[i] + prod) % mod;
        }
    }
    return cat[n];
}

int main() {
    int64_t N = 5000;
    int64_t ITERS = 100;
    int64_t MOD = 1000000007;
    int64_t* cat = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t result = catalan_dp(cat, N, MOD);
        checksum = (checksum + result) % MOD;
        // Perturb: add iter-dependent offset to C(1) for next iteration
        cat[1] = (1 + iter) % MOD;
    }

    printf("%lld\n", (long long)checksum);
    free(cat);
    return 0;
}
