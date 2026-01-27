// fasta - DNA sequence generation benchmark
// Benchmarks Game standard algorithm with LCG random
// v0.55: FAIR VERSION - Uses fixed-point arithmetic (1000000 scale) like BMB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define IM 139968
#define IA 3877
#define IC 29573
#define LINE_WIDTH 60
#define SCALE 1000000  // Fixed-point scale factor

static int seed = 42;

// Returns scaled random number (0 to SCALE)
static inline int64_t random_scaled(void) {
    seed = (seed * IA + IC) % IM;
    return (int64_t)seed * SCALE / IM;
}

// Nucleotide with fixed-point cumulative probability
struct AminoAcid {
    char c;
    int64_t p;  // Cumulative probability (scaled)
};

// IUB cumulative probabilities (pre-calculated, scaled by 1000000)
static struct AminoAcid iub[] = {
    {'a', 270000},   // 0.27
    {'c', 390000},   // 0.27 + 0.12
    {'g', 510000},   // 0.39 + 0.12
    {'t', 780000},   // 0.51 + 0.27
    {'B', 800000},   // 0.78 + 0.02
    {'D', 820000},
    {'H', 840000},
    {'K', 860000},
    {'M', 880000},
    {'N', 900000},
    {'R', 920000},
    {'S', 940000},
    {'V', 960000},
    {'W', 980000},
    {'Y', 1000000}
};
#define IUB_LEN 15

// Homo sapiens cumulative probabilities (scaled)
static struct AminoAcid homosapiens[] = {
    {'a', 302955},   // 0.3029549426680
    {'c', 500943},   // cumulative
    {'g', 698491},   // cumulative
    {'t', 1000000}   // cumulative
};
#define HOMO_LEN 4

static char select_random(struct AminoAcid *table, int len) {
    int64_t r = random_scaled();
    for (int i = 0; i < len; i++) {
        if (r < table[i].p) return table[i].c;
    }
    return table[len - 1].c;
}

static void make_random_fasta(const char *id, const char *desc,
                              struct AminoAcid *table, int table_len, int n) {
    printf(">%s %s\n", id, desc);

    char line[LINE_WIDTH + 1];
    int pos = 0;

    for (int i = 0; i < n; i++) {
        line[pos++] = select_random(table, table_len);
        if (pos == LINE_WIDTH) {
            line[pos] = '\0';
            puts(line);
            pos = 0;
        }
    }
    if (pos > 0) {
        line[pos] = '\0';
        puts(line);
    }
}

static void make_repeat_fasta(const char *id, const char *desc,
                              const char *alu, int n) {
    printf(">%s %s\n", id, desc);

    int alu_len = strlen(alu);
    int k = 0;
    char line[LINE_WIDTH + 1];
    int pos = 0;

    for (int i = 0; i < n; i++) {
        line[pos++] = alu[k];
        k = (k + 1) % alu_len;
        if (pos == LINE_WIDTH) {
            line[pos] = '\0';
            puts(line);
            pos = 0;
        }
    }
    if (pos > 0) {
        line[pos] = '\0';
        puts(line);
    }
}

static const char alu[] =
    "GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTG"
    "GGAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGA"
    "GACCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAA"
    "AATACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAAT"
    "CCCAGCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAAC"
    "CCGGGAGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTG"
    "CACTCCAGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";

int main(int argc, char **argv) {
    int n = 250000;  // Increased for measurable timing
    if (argc > 1) n = atoi(argv[1]);

    make_repeat_fasta("ONE", "Homo sapiens alu", alu, n * 2);
    make_random_fasta("TWO", "IUB ambiguity codes", iub, IUB_LEN, n * 3);
    make_random_fasta("THREE", "Homo sapiens frequency", homosapiens, HOMO_LEN, n * 5);

    return 0;
}
