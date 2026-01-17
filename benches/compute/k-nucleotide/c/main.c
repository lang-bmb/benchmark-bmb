// k-nucleotide - DNA sequence pattern counting benchmark
// Benchmarks Game standard algorithm
// Counts k-mer frequencies using hash table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAP 1024
#define HASH_SIZE 65536

// Simple hash table entry
typedef struct Entry {
    char *key;
    int count;
    struct Entry *next;
} Entry;

// Hash table
typedef struct {
    Entry *buckets[HASH_SIZE];
} HashTable;

// Hash function for strings
static unsigned int hash_str(const char *s) {
    unsigned int h = 0;
    while (*s) {
        h = h * 31 + (unsigned char)toupper(*s++);
    }
    return h % HASH_SIZE;
}

static HashTable *hash_new(void) {
    HashTable *ht = calloc(1, sizeof(HashTable));
    return ht;
}

static void hash_increment(HashTable *ht, const char *key) {
    unsigned int h = hash_str(key);
    Entry *e = ht->buckets[h];
    while (e) {
        if (strcasecmp(e->key, key) == 0) {
            e->count++;
            return;
        }
        e = e->next;
    }
    // New entry
    e = malloc(sizeof(Entry));
    e->key = strdup(key);
    e->count = 1;
    e->next = ht->buckets[h];
    ht->buckets[h] = e;
}

static int hash_get(HashTable *ht, const char *key) {
    unsigned int h = hash_str(key);
    Entry *e = ht->buckets[h];
    while (e) {
        if (strcasecmp(e->key, key) == 0) {
            return e->count;
        }
        e = e->next;
    }
    return 0;
}

// Collect all entries for sorting
typedef struct {
    char *key;
    int count;
} KV;

static int kv_count = 0;
static KV *kv_list = NULL;

static void collect_entries(HashTable *ht) {
    kv_count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Entry *e = ht->buckets[i];
        while (e) {
            kv_count++;
            e = e->next;
        }
    }
    kv_list = malloc(kv_count * sizeof(KV));
    int idx = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Entry *e = ht->buckets[i];
        while (e) {
            kv_list[idx].key = e->key;
            kv_list[idx].count = e->count;
            idx++;
            e = e->next;
        }
    }
}

// Comparison for sorting: descending by count, then ascending by key
static int kv_compare(const void *a, const void *b) {
    const KV *ka = a, *kb = b;
    if (ka->count != kb->count) return kb->count - ka->count;
    return strcasecmp(ka->key, kb->key);
}

static void hash_free(HashTable *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Entry *e = ht->buckets[i];
        while (e) {
            Entry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(ht);
}

// Sequence buffer
static char *seq = NULL;
static size_t seq_len = 0;
static size_t seq_cap = 0;

static void seq_append(char c) {
    if (seq_len >= seq_cap) {
        seq_cap = seq_cap == 0 ? INITIAL_CAP : seq_cap * 2;
        seq = realloc(seq, seq_cap + 1);
    }
    seq[seq_len++] = toupper(c);
    seq[seq_len] = '\0';
}

// Count k-mers of length k
static HashTable *count_kmers(int k) {
    HashTable *ht = hash_new();
    char kmer[32];
    for (size_t i = 0; i + k <= seq_len; i++) {
        strncpy(kmer, seq + i, k);
        kmer[k] = '\0';
        hash_increment(ht, kmer);
    }
    return ht;
}

// Print frequency table
static void print_freq(int k) {
    HashTable *ht = count_kmers(k);
    collect_entries(ht);
    qsort(kv_list, kv_count, sizeof(KV), kv_compare);

    int total = seq_len - k + 1;
    for (int i = 0; i < kv_count; i++) {
        double pct = 100.0 * kv_list[i].count / total;
        printf("%s %.3f\n", kv_list[i].key, pct);
    }
    printf("\n");

    free(kv_list);
    hash_free(ht);
}

// Print count for specific pattern
static void print_count(const char *pattern) {
    int k = strlen(pattern);
    HashTable *ht = count_kmers(k);
    int count = hash_get(ht, pattern);
    printf("%d\t%s\n", count, pattern);
    hash_free(ht);
}

int main(void) {
    char line[256];
    int in_three = 0;

    // Find sequence THREE
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (line[0] == '>') {
            if (strstr(line, "THREE") != NULL) {
                in_three = 1;
            } else {
                in_three = 0;
            }
        } else if (in_three && line[0] != ';') {
            for (char *p = line; *p; p++) {
                if (isalpha(*p)) {
                    seq_append(*p);
                }
            }
        }
    }

    // Output frequency tables for k=1 and k=2
    print_freq(1);
    print_freq(2);

    // Output specific pattern counts
    print_count("GGT");
    print_count("GGTA");
    print_count("GGTATT");
    print_count("GGTATTTTAATT");
    print_count("GGTATTTTAATTTATAGT");

    free(seq);
    return 0;
}
