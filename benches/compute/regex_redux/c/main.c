// Regex-Redux - Pattern matching benchmark
// Reference: Computer Language Benchmarks Game
//
// This is a simplified version without PCRE dependency
// For full benchmark, use PCRE library version

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEQ_LEN 100000

// Character constants
#define CHAR_A 65
#define CHAR_C 67
#define CHAR_G 71
#define CHAR_T 84
#define CHAR_a 97
#define CHAR_c 99
#define CHAR_g 103
#define CHAR_t 116

// Check if char matches case-insensitively
static inline int match_char(char c, char lower, char upper) {
    return c == lower || c == upper;
}

// Match pattern "agggtaaa" at position (case-insensitive)
int match_agggtaaa(const char *buf, int pos, int len) {
    if (pos + 8 > len) return 0;

    return match_char(buf[pos], 'a', 'A') &&
           match_char(buf[pos+1], 'g', 'G') &&
           match_char(buf[pos+2], 'g', 'G') &&
           match_char(buf[pos+3], 'g', 'G') &&
           match_char(buf[pos+4], 't', 'T') &&
           match_char(buf[pos+5], 'a', 'A') &&
           match_char(buf[pos+6], 'a', 'A') &&
           match_char(buf[pos+7], 'a', 'A');
}

// Match pattern "tttaccct" at position (case-insensitive)
int match_tttaccct(const char *buf, int pos, int len) {
    if (pos + 8 > len) return 0;

    return match_char(buf[pos], 't', 'T') &&
           match_char(buf[pos+1], 't', 'T') &&
           match_char(buf[pos+2], 't', 'T') &&
           match_char(buf[pos+3], 'a', 'A') &&
           match_char(buf[pos+4], 'c', 'C') &&
           match_char(buf[pos+5], 'c', 'C') &&
           match_char(buf[pos+6], 'c', 'C') &&
           match_char(buf[pos+7], 't', 'T');
}

// Count pattern matches
int count_pattern1(const char *buf, int len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (match_agggtaaa(buf, i, len)) count++;
        if (match_tttaccct(buf, i, len)) count++;
    }
    return count;
}

// Generate test DNA sequence
void generate_dna(char *buf, int len) {
    const char bases[] = "ACGT";

    for (int i = 0; i < len; i++) {
        unsigned int seed = i * 1103515245 + 12345;
        int base_idx = (seed / 65536) % 4;
        buf[i] = bases[base_idx];
    }

    // Insert known pattern for testing
    buf[100] = 'a';
    buf[101] = 'g';
    buf[102] = 'g';
    buf[103] = 'g';
    buf[104] = 't';
    buf[105] = 'a';
    buf[106] = 'a';
    buf[107] = 'a';
}

int main(int argc, char *argv[]) {
    int seq_len = SEQ_LEN;
    if (argc > 1) {
        seq_len = atoi(argv[1]);
    }

    char *buf = malloc(seq_len);
    if (!buf) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    generate_dna(buf, seq_len);

    int count1 = count_pattern1(buf, seq_len);
    printf("agggtaaa|tttaccct %d\n", count1);

    free(buf);
    return 0;
}
