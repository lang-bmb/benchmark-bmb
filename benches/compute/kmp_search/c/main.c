// KMP String Search — Knuth-Morris-Pratt pattern matching
// Measures: failure function computation, sequential scan with backtracking
// Workload: text=1000000, pattern=1000, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t TEXT_LEN = 1000000;
    int64_t PAT_LEN = 1000;
    int64_t ITERS = 200;
    int64_t* text = (int64_t*)malloc(TEXT_LEN * sizeof(int64_t));
    int64_t* pat = (int64_t*)malloc(PAT_LEN * sizeof(int64_t));
    int64_t* fail = (int64_t*)malloc(PAT_LEN * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate text
        for (int64_t i = 0; i < TEXT_LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            text[i] = seed % 4; // small alphabet for more matches
        }
        // Generate pattern
        for (int64_t i = 0; i < PAT_LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            pat[i] = seed % 4;
        }

        // Build failure function
        fail[0] = 0;
        int64_t k = 0;
        for (int64_t i = 1; i < PAT_LEN; i++) {
            while (k > 0 && pat[k] != pat[i]) {
                k = fail[k - 1];
            }
            if (pat[k] == pat[i]) k++;
            fail[i] = k;
        }

        // KMP search
        int64_t matches = 0;
        int64_t j = 0;
        for (int64_t i = 0; i < TEXT_LEN; i++) {
            while (j > 0 && pat[j] != text[i]) {
                j = fail[j - 1];
            }
            if (pat[j] == text[i]) j++;
            if (j == PAT_LEN) {
                matches++;
                j = fail[j - 1];
            }
        }
        checksum += matches;
    }
    printf("%lld\n", (long long)checksum);
    free(text);
    free(pat);
    free(fail);
    return 0;
}
