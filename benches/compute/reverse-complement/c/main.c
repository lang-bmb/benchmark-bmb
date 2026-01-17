// reverse-complement - DNA strand complement benchmark
// Benchmarks Game standard algorithm
// Reads FASTA format, outputs reverse complement

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_WIDTH 60
#define INITIAL_CAPACITY 1024

// Complement table for IUPAC codes
static char complement[256];

static void init_complement(void) {
    // Initialize all to self (for unknowns)
    for (int i = 0; i < 256; i++) {
        complement[i] = (char)i;
    }

    // Standard bases
    complement['A'] = 'T'; complement['a'] = 't';
    complement['T'] = 'A'; complement['t'] = 'a';
    complement['G'] = 'C'; complement['g'] = 'c';
    complement['C'] = 'G'; complement['c'] = 'g';
    complement['U'] = 'A'; complement['u'] = 'a';  // RNA

    // IUPAC ambiguity codes
    complement['M'] = 'K'; complement['m'] = 'k';  // A or C -> T or G
    complement['K'] = 'M'; complement['k'] = 'm';  // T or G -> A or C
    complement['R'] = 'Y'; complement['r'] = 'y';  // A or G -> T or C
    complement['Y'] = 'R'; complement['y'] = 'r';  // T or C -> A or G
    complement['S'] = 'S'; complement['s'] = 's';  // G or C (self)
    complement['W'] = 'W'; complement['w'] = 'w';  // A or T (self)
    complement['V'] = 'B'; complement['v'] = 'b';  // A, C, or G -> T, G, or C
    complement['B'] = 'V'; complement['b'] = 'v';  // T, G, or C -> A, C, or G
    complement['H'] = 'D'; complement['h'] = 'd';  // A, C, or T -> T, G, or A
    complement['D'] = 'H'; complement['d'] = 'h';  // A, G, or T -> T, C, or A
    complement['N'] = 'N'; complement['n'] = 'n';  // Any (self)
}

// Buffer for sequence data
static char *seq_buf = NULL;
static size_t seq_len = 0;
static size_t seq_cap = 0;

static void seq_append(char c) {
    if (seq_len >= seq_cap) {
        seq_cap = seq_cap == 0 ? INITIAL_CAPACITY : seq_cap * 2;
        seq_buf = realloc(seq_buf, seq_cap);
    }
    seq_buf[seq_len++] = c;
}

static void seq_clear(void) {
    seq_len = 0;
}

// Reverse complement in place and output
static void output_reverse_complement(void) {
    if (seq_len == 0) return;

    // Reverse and complement in place
    size_t i = 0, j = seq_len - 1;
    while (i < j) {
        char tmp = complement[(unsigned char)seq_buf[i]];
        seq_buf[i] = complement[(unsigned char)seq_buf[j]];
        seq_buf[j] = tmp;
        i++; j--;
    }
    if (i == j) {
        seq_buf[i] = complement[(unsigned char)seq_buf[i]];
    }

    // Output in LINE_WIDTH chunks
    char line[LINE_WIDTH + 1];
    size_t pos = 0;
    while (pos < seq_len) {
        size_t len = seq_len - pos;
        if (len > LINE_WIDTH) len = LINE_WIDTH;
        memcpy(line, seq_buf + pos, len);
        line[len] = '\0';
        puts(line);
        pos += len;
    }
}

int main(void) {
    init_complement();

    char line[256];
    char header[256] = "";

    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);

        // Remove newline
        if (len > 0 && line[len-1] == '\n') {
            line[--len] = '\0';
        }

        if (line[0] == '>') {
            // New sequence - output previous if any
            if (header[0] != '\0') {
                puts(header);
                output_reverse_complement();
            }
            seq_clear();
            strcpy(header, line);
        } else if (line[0] != ';') {
            // Sequence data (skip comments starting with ;)
            for (size_t i = 0; i < len; i++) {
                if (!isspace((unsigned char)line[i])) {
                    seq_append(line[i]);
                }
            }
        }
    }

    // Output last sequence
    if (header[0] != '\0') {
        puts(header);
        output_reverse_complement();
    }

    free(seq_buf);
    return 0;
}
