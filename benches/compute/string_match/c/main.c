// String Match — naive pattern matching
// Measures: sequential comparison, inner loop early exit
// Workload: 100K text, 5-char pattern, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t TEXT_LEN = 100000;
    int64_t PAT_LEN = 5;
    int64_t ITERS = 2000;

    int64_t* text = (int64_t*)malloc(TEXT_LEN * sizeof(int64_t));
    int64_t* pat  = (int64_t*)malloc(PAT_LEN * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate text
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < TEXT_LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            text[i] = seed % 26;
        }
        // Generate pattern
        seed = 99999 + iter;
        for (int64_t i = 0; i < PAT_LEN; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            pat[i] = seed % 26;
        }
        // Naive string matching — count occurrences
        int64_t count = 0;
        for (int64_t i = 0; i <= TEXT_LEN - PAT_LEN; i++) {
            int64_t match = 1;
            for (int64_t j = 0; j < PAT_LEN; j++) {
                if (text[i + j] != pat[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) count++;
        }
        checksum += count;
    }

    printf("%lld\n", (long long)checksum);
    free(text);
    free(pat);
    return 0;
}
