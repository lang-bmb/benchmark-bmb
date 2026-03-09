// Rabin-Karp string matching — rolling hash
// Measures: modular arithmetic, sliding window hash, branch-heavy search
// Workload: 100K text, 8-char patterns, 200 iterations x 10 patterns each

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEXT_LEN 100000
#define PAT_LEN 8
#define ITERS 200
#define NUM_PATS 10
#define BASE 31
#define MOD 1000000007LL

int main() {
    uint8_t* text = (uint8_t*)malloc(TEXT_LEN);
    uint8_t* pat  = (uint8_t*)malloc(PAT_LEN);

    int64_t checksum = 0;

    // Precompute BASE^PAT_LEN % MOD
    int64_t base_pow = 1;
    for (int64_t i = 0; i < PAT_LEN; i++) {
        base_pow = (base_pow * BASE) % MOD;
    }

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate text with PRNG
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < TEXT_LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            text[i] = (uint8_t)(seed % 26);
        }

        // Search for NUM_PATS different patterns per iteration
        for (int64_t p = 0; p < NUM_PATS; p++) {
            // Generate pattern with PRNG
            seed = 77777 + iter * 100 + p;
            for (int64_t i = 0; i < PAT_LEN; i++) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                pat[i] = (uint8_t)(seed % 26);
            }

            // Compute pattern hash
            int64_t pat_hash = 0;
            for (int64_t i = 0; i < PAT_LEN; i++) {
                pat_hash = (pat_hash * BASE + pat[i]) % MOD;
            }

            // Compute initial window hash
            int64_t win_hash = 0;
            for (int64_t i = 0; i < PAT_LEN; i++) {
                win_hash = (win_hash * BASE + text[i]) % MOD;
            }

            // Slide window
            int64_t count = 0;
            for (int64_t i = 0; i <= TEXT_LEN - PAT_LEN; i++) {
                if (win_hash == pat_hash) {
                    // Verify match
                    int64_t matched = 1;
                    for (int64_t j = 0; j < PAT_LEN; j++) {
                        if (text[i + j] != pat[j]) {
                            matched = 0;
                            break;
                        }
                    }
                    count += matched;
                }
                // Roll hash forward
                if (i < TEXT_LEN - PAT_LEN) {
                    win_hash = ((win_hash * BASE - (int64_t)text[i] * base_pow % MOD + MOD) % MOD + text[i + PAT_LEN]) % MOD;
                }
            }
            checksum += count;
        }
    }

    printf("%lld\n", (long long)checksum);
    free(text);
    free(pat);
    return 0;
}
