// fasta - DNA sequence generation benchmark
// Benchmarks Game standard algorithm with LCG random

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IM 139968
#define IA 3877
#define IC 29573
#define LINE_WIDTH 60

static int seed = 42;

static inline double random_num(double max) {
    seed = (seed * IA + IC) % IM;
    return max * seed / IM;
}

// Nucleotide frequencies for random sequences
struct AminoAcid {
    char c;
    double p;
};

static struct AminoAcid iub[] = {
    {'a', 0.27}, {'c', 0.12}, {'g', 0.12}, {'t', 0.27},
    {'B', 0.02}, {'D', 0.02}, {'H', 0.02}, {'K', 0.02},
    {'M', 0.02}, {'N', 0.02}, {'R', 0.02}, {'S', 0.02},
    {'V', 0.02}, {'W', 0.02}, {'Y', 0.02}
};
#define IUB_LEN 15

static struct AminoAcid homosapiens[] = {
    {'a', 0.3029549426680}, {'c', 0.1979883004921},
    {'g', 0.1975473066391}, {'t', 0.3015094502008}
};
#define HOMO_LEN 4

static void make_cumulative(struct AminoAcid *table, int len) {
    double cp = 0.0;
    for (int i = 0; i < len; i++) {
        cp += table[i].p;
        table[i].p = cp;
    }
}

static char select_random(struct AminoAcid *table, int len) {
    double r = random_num(1.0);
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

    make_cumulative(iub, IUB_LEN);
    make_cumulative(homosapiens, HOMO_LEN);

    make_repeat_fasta("ONE", "Homo sapiens alu", alu, n * 2);
    make_random_fasta("TWO", "IUB ambiguity codes", iub, IUB_LEN, n * 3);
    make_random_fasta("THREE", "Homo sapiens frequency", homosapiens, HOMO_LEN, n * 5);

    return 0;
}
