// Naive string search benchmark — count pattern occurrences in text
// Measures: sequential memory access, character comparison, branch prediction
// Workload: 100000-char text, 10-char patterns, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t naive_search(const int64_t* text, int64_t text_len,
                            const int64_t* pattern, int64_t pat_len) {
    int64_t count = 0;
    int64_t limit = text_len - pat_len + 1;
    for (int64_t i = 0; i < limit; i++) {
        int64_t match = 1;
        for (int64_t j = 0; j < pat_len; j++) {
            if (text[i + j] != pattern[j]) {
                match = 0;
                break;
            }
        }
        if (match) count++;
    }
    return count;
}

int main() {
    int64_t TEXT_LEN = 100000;
    int64_t PAT_LEN = 10;
    int64_t ITERS = 1000;

    int64_t* text = (int64_t*)malloc(TEXT_LEN * sizeof(int64_t));
    int64_t* pattern = (int64_t*)malloc(PAT_LEN * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    // Generate text once using LCG (chars a-z = 0-25)
    for (int64_t i = 0; i < TEXT_LEN; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        text[i] = seed % 26;
    }

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate pattern from text at a pseudo-random position
        // This ensures the pattern exists at least once
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t start = seed % (TEXT_LEN - PAT_LEN);
        for (int64_t j = 0; j < PAT_LEN; j++) {
            pattern[j] = text[start + j];
        }
        checksum += naive_search(text, TEXT_LEN, pattern, PAT_LEN);
    }

    printf("%lld\n", (long long)checksum);
    free(text);
    free(pattern);
    return 0;
}
